#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define print_stack(pos)						\
	do {								\
		unsigned long *address = 0;				\
		unsigned long value = 0;				\
		unsigned long *start = (unsigned long *) pos;		\
		int i = 0;						\
									\
		printf("&address = %p\n", &address);			\
		printf("\taddress\t\tvalue\n");				\
		printf("--------------------------------------\n");	\
		for (i = 0; i < 12; i++) {				\
			address = start + i;				\
			value = *address;				\
			printf("\t%p\t\t0x%0lx\n", address, value);	\
		}							\
	} while (0)

#define TEST_STRING	"aaaaaaaaaaaaaaaaaaaaaaaaa"

int main(void)
{
#ifdef USE_CHAR_ARRAY
	char a[24];
#else
	unsigned long a[3];
#endif
	memset(a, 0, sizeof(a));
	memcpy(a, "bbbbbbbb", 8);

	printf("sizeof(a) = %lu, strlen(TEST_STRING) = %lu\n", sizeof(a), strlen(TEST_STRING));
	print_stack(&a[0]);

	memcpy(&a[0], TEST_STRING, strlen(TEST_STRING));

	print_stack(&a[0]);

	return 0;
}
