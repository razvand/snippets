#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static size_t get_free_memory(void)
{
	FILE *f;
	size_t i;
	char buf[256];
	char *p;

	f = fopen("/proc/meminfo", "rt");
	assert(f != NULL);
	/* Second line is 'MemFree: ...' */
	fgets(buf, 256, f);
	fgets(buf, 256, f);
	fclose(f);

	p = NULL;
	for (i = 0; i < 256; i++)
		if (buf[i] == ':') {
			p = buf+i+1;
			break;
		}

	return strtoul(p, NULL, 10);
}

int main(void)
{
	size_t mem_used;

	mem_used = get_free_memory();
	printf("memory used: %zu KB\n", mem_used);

	return 0;
}
