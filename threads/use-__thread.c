#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

static __thread size_t me;
static __thread size_t you;

static void *tf(void *arg)
{
	me = 200;
	printf("in thread (%p): %zu\n", &me, me);

	return NULL;
}

int main(void)
{
	pthread_t new;
	int err;

	me = 100;
	you = 101;
	printf("me before create (%p): %zu\n", &me, me);

	err = pthread_create(&new, NULL, tf, NULL);
	if (err < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	printf("me after create before join: %zu\n", me);
	pthread_join(new, NULL);
	printf("me after join: %zu\n", me);

	return 0;
}
