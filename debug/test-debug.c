#include "debug.h"

#define DEFAULT_VALUE	42
#define DEFAULT_MASK	0xF0F0F0F0

int main(void)
{
	int a = DEFAULT_VALUE;
	unsigned int b = DEFAULT_MASK;
	int c;

	/* debug print */
	dprintf("Hello, World!\n");
	dprintf("a = %d, b = %0x\n", a, b);

	c = a & b;
	printf("c = %d\n", c);	/* always print */

	return 0;
}
