#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	unsigned long long ull = 0x0000000012345678ULL;
	unsigned int ui = ull;

	printf("ull: %llu, ull (as unsigned int): %u\n", ull, ull);
	printf("ui: %u\n", ui);

	return 0;
}
