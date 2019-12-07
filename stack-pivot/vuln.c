#include <stdio.h>

/* global test variable */
static size_t g = 0x42424242;
static char g_array[256];

static void warcraft(void)
{
	puts("chieftain");
}

static void diablo(size_t a, size_t b)
{
	if (a == 0x12345678 && b == 0xaabbccdd)
		puts("worldstone");
}

static void starcraft(void)
{
	if (g == 0xc001face)
		puts("koprulu");
}

static void reader(void)
{
	char buffer[64];

	printf("gimme initial message: ");
	fgets(g_array, 256, stdin);

	printf("gimme message: ");
	fgets(buffer, 90, stdin);
	printf("hello, %s\n", buffer);
}

int main(void)
{
	puts("hello, blizzard!");

	reader();

	return 0;
}
