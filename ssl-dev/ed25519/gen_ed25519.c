#include <openssl/evp.h>
#include <openssl/pem.h>

#define PRIVATE_KEYFILE		"private.pem"
#define PUBLIC_KEYFILE		"public.pem"

static int write_private_key_to_file(const char *fname, EVP_PKEY *pkey)
{
	FILE *fp;

	fp = fopen(fname, "w");
	if (fp == NULL) {
		perror("fopen");
		return 0;
	}
	PEM_write_PrivateKey(fp, pkey, NULL, NULL, 0, NULL, NULL);
	fclose(fp);

	return 1;
}

static int write_public_key_to_file(const char *fname, EVP_PKEY *pkey)
{
	FILE *fp;

	fp = fopen(fname, "w");
	if (fp == NULL) {
		perror("fopen");
		return 0;
	}
	PEM_write_PUBKEY(fp, pkey);
	fclose(fp);

	return 1;
}

int main(void)
{
	EVP_PKEY *pkey = NULL;
	EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, NULL);
	EVP_PKEY_keygen_init(pctx);
	EVP_PKEY_keygen(pctx, &pkey);
	EVP_PKEY_CTX_free(pctx);

	write_private_key_to_file(PRIVATE_KEYFILE, pkey);
	write_public_key_to_file(PUBLIC_KEYFILE, pkey);

	return 0;
}
