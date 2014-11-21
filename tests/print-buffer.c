#include <stdio.h>

int main(void)
{
	char buffer[128];

	buffer[0] = 'a';
	printf("buffer starts at: %p\n", buffer);

	return 0;
}
