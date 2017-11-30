#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>

static void print_duration(const char *msg, struct timespec *tstart, struct timespec *tend)
{
	long nsec_start;
	long nsec_end;

	nsec_start = 1000*1000*1000*tstart->tv_sec + tstart->tv_nsec;
	nsec_end = 1000*1000*1000*tend->tv_sec + tend->tv_nsec;

	printf("%s (ns): %ld\n", msg, nsec_end-nsec_start);
}

static void create_processes(size_t num)
{
	struct timespec tstart, tend;
	pid_t *pid_array;
	size_t i;

	pid_array = malloc(num * sizeof(pid_t));

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0)
		perror("clock_gettime");
	for (i = 0; i < num; i++) {
		pid_array[i] = fork();
		if (pid_array[i] == 0)
			exit(EXIT_SUCCESS);
	}
	if (clock_gettime(CLOCK_REALTIME, &tend) < 0)
		perror("clock_gettime");

	print_duration("create processes in", &tstart, &tend);
}

static void *do_nothing(void *arg)
{
}

static void create_threads(size_t num)
{
	struct timespec tstart, tend;
	pthread_t *tid_array;
	size_t i;

	tid_array = malloc(num * sizeof(pthread_t));

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0)
		perror("clock_gettime");
	for (i = 0; i < num; i++) {
		pthread_create(&tid_array[i], NULL, do_nothing, NULL);
	}
	if (clock_gettime(CLOCK_REALTIME, &tend) < 0)
		perror("clock_gettime");

	print_duration("create threads in", &tstart, &tend);
}

int main(void)
{
	create_processes(1000);
	create_threads(1000);

	return 0;
}
