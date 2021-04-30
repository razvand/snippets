/* https://stackoverflow.com/a/50791866/4804196 */

#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define KEYFILE			"private.pem"
#define SIGFILE			"signature.dat"
#define ED25519_SIGSIZE		64

static char buffer[512];

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
		fprintf(stderr, "EVP_DigestSignInit: %s\n", ERR_error_string(ERR_get_error(), buffer));
		goto err_digest;
	}

	/* Do the DigestSign operation. */
	ret = EVP_DigestSign(mdctx, sig, slen, msg, mlen);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestSign: %s\n", ERR_error_string(ERR_get_error(), buffer));
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

	EVP_PKEY *key = read_secret_key_from_file(KEYFILE);
	if (!key)
		exit(EXIT_FAILURE);

	memset(msg, 'A', 512);
	ret = do_sign(key, msg, 512, sig, &slen);
	if (ret != 1)
		exit(EXIT_FAILURE);
	write_signature_to_file(SIGFILE, sig, slen);

	EVP_PKEY_free(key);

	return 0;
}
