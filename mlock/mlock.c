#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ...\n"); fflush(stdout);
	fgets(buf, 32, stdin);
}

#define NUM_PAGES	8

int main(void)
{
	void *addr;
	size_t map_len = NUM_PAGES * getpagesize();
	size_t i;
	int rc;
	struct rlimit r;

	rc = getrlimit(RLIMIT_MEMLOCK, &r);
	if (rc < 0) {
		perror("getrlimit");
		exit(EXIT_FAILURE);
	}
	printf("memlock limit: %zu (current), %zu (maximum)\n",
			r.rlim_cur, r.rlim_max);
	printf("map_len: %zu\n", NUM_PAGES * map_len);
	wait_for_input("Call mmap()");
	addr = mmap(NULL, NUM_PAGES * map_len, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	wait_for_input("Access mapped page");
	for (i = 0; i < NUM_PAGES; i++)
		memcpy(addr + i*getpagesize(), "anaaremere", 10);
	wait_for_input("Call mlock()");
	rc = mlock(addr, NUM_PAGES * map_len);
	if (rc < 0) {
		perror("mlock");
		exit(EXIT_FAILURE);
	}
	wait_for_input("mlock() has been called");

	return 0;
}
