/*
 * power of two alignment macros
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PAGE_BITS_SIZE		12
#define PAGE_ALIGN_MASK		(((unsigned long)(-1L)) << PAGE_BITS_SIZE)
#define PAGE_OFFSET_MASK	(~(PAGE_ALIGN_MASK))

int main(void)
{
	printf("page size: %d\n", PAGE_BITS_SIZE);
	printf("page align mask: 0x%0lx\n", PAGE_ALIGN_MASK);
	printf("page align mask: 0x%0lx\n", PAGE_OFFSET_MASK);

	return 0;
}
