#include <stdio.h>

#define DLL_EXPORTS
#include "internal.h"
#undef DLL_EXPORTS

#define DLL_IMPORTS
#include "external.h"
#undef DLL_IMPORTS

void internal_fun(void)
{
	printf("internal function\n");
	external_fun();
}
