#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	long *ptr;

	ptr = (long *) main;

	printf("*ptr = %x\n", *ptr);
	*ptr = 0x1234;

	return 0;
}
