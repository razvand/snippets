#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DLL_IMPORTS
#include "internal.h"
#undef DLL_EXPORTS

int main(void)
{
	printf("Hello, World!\n");

	internal_fun();

	return 0;
}
