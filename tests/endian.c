#include <stdio.h>
#include <endian.h>

#define TEST_VALUE	0x00000001	/* 1 */

static void print_endianess (void)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	printf ("System is little endian.\n");
#elif __BYTE_ORDER == __BIG_ENDIAN
	printf ("System is big endian.\n");
#elif
#error "Unknown endianess"
#endif
}

int main (void)
{
	unsigned int value = TEST_VALUE;
	unsigned char *ptr = (unsigned char *) &value;

	print_endianess ();
	printf ("real: %08x\n", value);
	printf ("in memory: %02x %02x %02x %02x\n", *ptr, *(ptr+1),
			*(ptr+2), *(ptr+3));

	return 0;
}
