/* https://stackoverflow.com/a/50791866/4804196 */

#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#include "measure.h"

#define KEYFILE			"private.pem"
#define SIGFILE			"signature.dat"
#define ED25519_SIGSIZE		64

static const char private_key_buf[] = "-----BEGIN PRIVATE KEY-----\nMC4CAQAwBQYDK2VwBCIEIA91xb59+0AMsIVI5WB2A07qmk0aUc+CPftTuI1yVDRf\n-----END PRIVATE KEY-----";
static const char public_key_buf[] = "-----BEGIN PUBLIC KEY-----\nMCowBQYDK2VwAyEAC3S5qA2LRbPpxYPZZZzbs+k/9inr0spoP5/G7RexZAc=\n-----END PUBLIC KEY-----";
static const char message_to_sign[] = "loremipsum";
static const char signature_to_check[] = "\x18\x54\x6b\xd2\x0e\x0d\x5e\xc3\x46\xb7\xc1\xc1\x62\xb9\x19\x1b\x51\xa0\xf0\x4a\x06\xfc\xbc\x1b\x7f\x05\x20\x2f\xdf\x54\x3c\xbd\x62\xd9\x79\x97\xff\x8c\xea\x7d\x9a\xdc\x47\x5f\x60\x46\x13\x78\xa6\x5a\xd1\x08\x6e\x6a\xff\x45\x86\x57\xa6\x5e\x16\x23\x24\x07";

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

static EVP_PKEY *read_public_key_from_buffer(const char *buffer)
{
	EVP_PKEY *key = NULL;
	BIO *bufio;
	char err_buf[512];

	bufio = BIO_new_mem_buf(buffer, -1);
	if (bufio == NULL) {
		fprintf(stderr, "BIO_new_mem_buf: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto out;
	}
	key = PEM_read_bio_PUBKEY(bufio, NULL, NULL, NULL);
	if (key == NULL)
		fprintf(stderr, "PEM_read_bio_PUBKEY: %s", ERR_error_string(ERR_get_error(), err_buf));

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
	char err_buf[512];
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
		fprintf(stderr, "EVP_DigestVerifyInit: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto err_digest;
	}

	/* Do the DigestVerify operation. */
	ret = EVP_DigestVerify(mdctx, sig, slen, msg, mlen);
	if (ret != 1) {
		fprintf(stderr, "EVP_DigestVerify: %s\n", ERR_error_string(ERR_get_error(), err_buf));
		goto err_digest;
	}

	/* Success */
	return 1;

err_digest:
	EVP_MD_CTX_destroy(mdctx);
err_md_create:
	return ret;
}

static void sign_wrapper(const char *text, const char *key_buf, unsigned int num_times)
{
	int ret;
	size_t slen = ED25519_SIGSIZE;
	unsigned char msg[512];
	unsigned char sig[ED25519_SIGSIZE];
	size_t i;
	uint64_t cycles_start, cycles_end;
	uint64_t total = 0;

	EVP_PKEY *key = read_secret_key_from_buffer(key_buf);
	if (!key)
		exit(EXIT_FAILURE);

	memset(msg, 0, 512);
	memcpy(msg, text, strlen(text));
	for (i = 0; i < num_times; i++) {
		cycles_start = bench_start();
		ret = do_sign(key, msg, 512, sig, &slen);
		cycles_end = bench_end();
		total += (cycles_end - cycles_start);
		if (ret != 1)
			exit(EXIT_FAILURE);
	}
	printf("Signature: ");
	print_hex(sig, slen);

	printf("Cycles per operation: %lu\n", total/num_times);

	EVP_PKEY_free(key);
}

static void verify_wrapper(const char *text, const char *sig, const char *key_buf, unsigned int num_times)
{
	int ret;
	size_t slen = ED25519_SIGSIZE;
	unsigned char msg[512];
	size_t i;
	uint64_t cycles_start, cycles_end;
	uint64_t total = 0;

	EVP_PKEY *key = read_public_key_from_buffer(key_buf);
	if (!key)
		exit(EXIT_FAILURE);

	memset(msg, 0, 512);
	memcpy(msg, text, strlen(text));
	for (i = 0; i < num_times; i++) {
		cycles_start = bench_start();
		ret = do_verify(key, msg, 512, sig, slen);
		cycles_end = bench_end();
		total += (cycles_end - cycles_start);
		if (ret != 1)
			exit(EXIT_FAILURE);
	}
	printf("Verification sucessful.\n");

	printf("Cycles per operation: %lu\n", total/num_times);

	EVP_PKEY_free(key);
}

enum op_type {
	OP_SIGN = 0,
	OP_VERIFY,
	OP_BOTH
};

int main(int argc, char **argv)
{
	enum op_type op = OP_BOTH;
	const char *text = message_to_sign;
	const char *signature = signature_to_check;
	const char *priv_key = private_key_buf;
	const char *pub_key = public_key_buf;
	unsigned int num_times = 1;

	if (argc >= 5) {
		if (argv[1][0] == 's')
			op = OP_SIGN;
		if (argv[1][0] == 'v')
			op = OP_VERIFY;
	}
	if (op == OP_VERIFY && argc != 6) {
		fprintf(stderr, "Not enough arguments for verification.\n");
		exit(EXIT_FAILURE);
	}
	if (op == OP_VERIFY) {
		text = argv[2];
		pub_key = argv[3];
		signature = argv[4];
		num_times = atoi(argv[5]);
		verify_wrapper(text, signature, pub_key, num_times);
	}
	else if (op == OP_SIGN) {
		text = argv[2];
		priv_key = argv[3];
		num_times = atoi(argv[4]);
		sign_wrapper(text, priv_key, num_times);
	}
	else {
		sign_wrapper(text, priv_key, num_times);
		verify_wrapper(text, signature, pub_key, num_times);
	}

	return 0;
}
