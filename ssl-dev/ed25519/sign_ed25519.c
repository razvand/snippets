/* https://stackoverflow.com/a/50791866/4804196 */

#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define KEYFILE			"private.pem"
#define SIGFILE			"signature.dat"
#define ED25519_SIGSIZE		64

static const char private_key_buf[] = "-----BEGIN PRIVATE KEY-----\nMC4CAQAwBQYDK2VwBCIEIA91xb59+0AMsIVI5WB2A07qmk0aUc+CPftTuI1yVDRf\n-----END PRIVATE KEY-----";
static const char message_to_sign[] = "loremipsum";

static EVP_PKEY *read_secret_key_from_file(const char *fname)
{
	EVP_PKEY *key = NULL;
	FILE *fp;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return NULL;
	}

	key = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
	fclose(fp);

	return key;
}

static EVP_PKEY *read_secret_key_from_buffer(const char *buffer)
{
	EVP_PKEY *key = NULL;
	BIO *bufio;
	char err_buf[512];

	bufio = BIO_new_mem_buf(buffer, -1);
	if (bufio == NULL) {
		fprintf(stderr, "BIO_new_mem_buf: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto out;
	}
	key = PEM_read_bio_PrivateKey(bufio, NULL, NULL, NULL);
	if (key == NULL)
		fprintf(stderr, "PEM_read_bio_PrivateKey: %s", ERR_error_string(ERR_get_error(), err_buf));

	BIO_free(bufio);
out:
	return key;
}

static void print_hex(const void *buffer, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		printf("\\x%02x", *((unsigned char *) buffer + i));
	printf("\n");
}

static int write_signature_to_file(const char *fname, unsigned char *sig, size_t slen)
{
	FILE *fp;

	fp = fopen(fname, "w");
	if (fp == NULL) {
		perror("fopen");
		return 0;
	}
	fwrite(sig, 1, slen, fp);
	fclose(fp);

	return 1;
}

static int do_sign(EVP_PKEY *key, const unsigned char *msg, const size_t mlen,
		unsigned char *sig, size_t *slen)
{
	EVP_MD_CTX *mdctx = NULL;
	char err_buf[512];
	int ret = 0;

	/* Create the Message Digest Context. */
	mdctx = EVP_MD_CTX_create();
	if (mdctx == NULL) {
		perror("EVP_MD_CTX_create");
		goto err_md_create;
	}

	/*
	 * Initialize the DigestSign operation.
	 * No message digest algorithm and no engine for ed25519.
	 */
	ret = EVP_DigestSignInit(mdctx, NULL, NULL, NULL, key);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestSignInit: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto err_digest;
	}

	/* Do the DigestSign operation. */
	ret = EVP_DigestSign(mdctx, sig, slen, msg, mlen);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestSign: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto err_digest;
	}

	/* Success */
	return 1;

err_digest:
	EVP_MD_CTX_destroy(mdctx);
err_md_create:
	return ret;
}

int main(void)
{
	int ret;
	size_t slen = ED25519_SIGSIZE;
	unsigned char msg[512];
	unsigned char sig[ED25519_SIGSIZE];

	EVP_PKEY *key = read_secret_key_from_buffer(private_key_buf);
	if (!key)
		exit(EXIT_FAILURE);

	memset(msg, 0, 512);
	memcpy(msg, message_to_sign, sizeof(message_to_sign));
	ret = do_sign(key, msg, 512, sig, &slen);
	if (ret != 1)
		exit(EXIT_FAILURE);
	printf("Signature: ");
	print_hex(sig, slen);

	EVP_PKEY_free(key);

	return 0;
}
