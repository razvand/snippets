#include <stdio.h>

int main(void)
{
	int n = 2;

	n += (++n);
	printf("new n is %d\n", n);

	return 0;
}
