#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_STRING	"aaaaaaaaaaaaaaaaaaaaaaaaa"

int main(void)
{
#ifdef USE_CHAR_ARRAY
	char a[16];
	/*char *a = malloc(16);*/
#else
	unsigned long a[2];
#endif

	printf("sizeof(a) = %lu, length(TEST_STRING) = %lu\n", sizeof(a), strlen(TEST_STRING));
	/*memcpy(a, TEST_STRING, strlen(TEST_STRING));*/

	return 0;
}
