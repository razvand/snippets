#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *p;
	int i;

	for (i = 0; i < 10; i++) {
		p = strdup("abcdefghij");
		printf("--- %d duplicate\n");
	}

	printf("--- before free\n");
	free(p);
	printf("--- after free\n");

	return 0;
}
