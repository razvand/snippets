#include <stdio.h>

int main(void)
{
	int a = -1;
	unsigned int b = 200;

	if (a < b) {
		printf("true %d < %u\n", a, b);
	}
	else {
		printf("false %d > %u\n", a, b);
	}

	return 0;
}
