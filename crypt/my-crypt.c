#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _XOPEN_SOURCE
#include <sys/types.h>
#include <unistd.h>

#define PASSWORD "anaaremere"
#define ALG_TYPE "6"
#define SALT	 "abcdef"

int main(void)
{
	char *pass_encrypted;

	pass_encrypted = (char *) crypt(PASSWORD, "$" ALG_TYPE "$" SALT);

	printf("%s encrypts to %s\n", PASSWORD, pass_encrypted);

	return 0;
}
