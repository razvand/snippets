#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int f(int a, int b)
{
	return a + b;
}

void g(void)
{
	printf("ret = %d\n", f(1,2));
}

int main(void)
{
	printf("ret = %d\n", f(1,2));

	return 0;
}
