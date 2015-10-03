#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE	4096
#endif

#define NUM_ALLOCS	1000

static void print_duration(const char *msg, struct timespec *tstart, struct timespec *tend)
{
	long nsec_start;
	long nsec_end;

	nsec_start = 1000*1000*1000*tstart->tv_sec + tstart->tv_nsec;
	nsec_end = 1000*1000*1000*tend->tv_sec + tend->tv_nsec;

	printf("%s (ns): %ld\n", msg, nsec_end-nsec_start);
}

int main(int argc, char * argv[])
{
	size_t i;
	char *p[NUM_ALLOCS];
	struct timespec tstart, tend;

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0) {
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < NUM_ALLOCS; i++) {
		p[i] = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (p[i] == MAP_FAILED) {
			perror("mmap");
			exit(EXIT_FAILURE);
		}
	}
	if (clock_gettime(CLOCK_REALTIME, &tend) < 0) {
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	print_duration("mmap time", &tstart, &tend);

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0) {
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < NUM_ALLOCS; i++) {
		p[i][0] = 'a';
	}
	if (clock_gettime(CLOCK_REALTIME, &tend) < 0) {
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	print_duration("access time", &tstart, &tend);

	return 0;
}
