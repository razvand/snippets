#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SLEEP_TIME_SECONDS	10

static void *print_and_wait(void *arg)
{
	printf("New thread sleeps for %u seconds\n", SLEEP_TIME_SECONDS);
	sleep(SLEEP_TIME_SECONDS);
	printf("New thread ends execution.\n");

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int rc;

	printf("Main thread sleeps for %u seconds before creating new thread.\n", SLEEP_TIME_SECONDS);
	sleep(SLEEP_TIME_SECONDS);

	rc = pthread_create(&tid, NULL, print_and_wait, NULL);
	if (rc < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	rc = pthread_join(tid, NULL);
	if (rc < 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	printf("Main thread sleeps for %u seconds after join and before exiting.\n", SLEEP_TIME_SECONDS);
	sleep(SLEEP_TIME_SECONDS);

	return 0;
}
