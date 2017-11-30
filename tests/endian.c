#include <stdio.h>
#include <endian.h>

#define TEST_VALUE	0x00000001	/* 1 (ro. unu, en. one, fr. une, de. einz) */

static void print_endianess (void)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	printf ("System is little endian.\n");
#elif __BYTE_ORDER == __BIG_ENDIAN
	printf ("System is big endian.\n");
#else
#error "Unknown endianess"
#endif
}

int main (void)
{
	unsigned int value = TEST_VALUE;
	unsigned char *ptr = (unsigned char *) &value;

	print_endianess();
	printf("real: 0x%08x\n", value);
	printf("in memory: 0x%02x 0x%02x 0x%02x 0x%02x\n", *ptr, *(ptr+1),
			*(ptr+2), *(ptr+3));

	return 0;
}
