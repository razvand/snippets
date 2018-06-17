#include <stdio.h>

#define NUM	4

static unsigned int values[NUM];

static void print_values(void)
{
	unsigned int i;

	printf("[ ");
	for (i = 0; i < NUM; i++)
		printf("%d ", values[i]);
	printf("]\n");
}

static void generate_all(size_t until)
{
	unsigned int i;

	for (i = 1; i <= NUM; i++) {
		values[until] = i;
		if (until == 0)
			print_values();
		else
			generate_all(until - 1);
	}
}

int main(void)
{
	generate_all(NUM-1);

	return 0;
}
