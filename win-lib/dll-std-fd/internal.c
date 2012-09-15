#include <stdio.h>

#define DLL_EXPORTS
#include "internal.h"
#undef DLL_EXPORTS

void internal_fun(void)
{
	printf("stdin ptr: %p; stdout ptr: %p; stderr ptr: %p\n",
			stdin, stdout, stderr);
}
