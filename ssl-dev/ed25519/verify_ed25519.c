/* https://stackoverflow.com/a/50791866/4804196 */

#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define KEYFILE			"public.pem"
#define SIGFILE			"signature.dat"
#define ED25519_SIGSIZE		64

static char buffer[512];

static EVP_PKEY *read_public_key_from_file(const char *fname)
{
	EVP_PKEY *key = NULL;
	FILE *fp;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return NULL;
	}

	key = PEM_read_PUBKEY(fp, NULL, NULL, NULL);
	fclose(fp);

	return key;
}

static int read_signature_from_file(const char *fname, unsigned char *sig, size_t slen)
{
	FILE *fp;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return 0;
	}
	fread(sig, 1, slen, fp);
	fclose(fp);

	return 1;
}

static int do_verify(EVP_PKEY *key, const unsigned char *msg, const size_t mlen,
		const unsigned char *sig, size_t slen)
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
	 * Initialize the DigestVerify operation.
	 * No message digest algorithm and no engine for ed25519.
	 */
	ret = EVP_DigestVerifyInit(mdctx, NULL, NULL, NULL, key);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestVerifyInit: %s\n", ERR_error_string(ERR_get_error(), buffer));
		goto err_digest;
	}

	/* Do the DigestVerify operation. */
	ret = EVP_DigestVerify(mdctx, sig, slen, msg, mlen);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestVerify: %s\n", ERR_error_string(ERR_get_error(), buffer));
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

	EVP_PKEY *key = read_public_key_from_file(KEYFILE);
	if (!key)
		exit(EXIT_FAILURE);

	ret = read_signature_from_file(SIGFILE, sig, slen);
	if (!ret)
		exit(EXIT_FAILURE);

	memset(msg, 'A', 512);
	ret = do_verify(key, msg, 512, sig, slen);
	if (ret != 1)
		exit(EXIT_FAILURE);

	puts("Message successfully verified.");

	EVP_PKEY_free(key);

	return 0;
}
