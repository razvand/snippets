#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

static __thread size_t me;
static __thread size_t you;
static __thread size_t them = 543;

static void *tf(void *arg)
{
	unsigned long id = (unsigned long) arg;
	static __thread size_t us = 13;

	me = 200 + id;
	us += id*id;
	printf("me in thread (%p): %zu\n", &me, me);
	printf("you in thread (%p): %zu\n", &you, you);
	printf("you in thread (%p): %zu\n", &them, them);
	printf("us in thread (%p): %zu\n", &us, us);
	printf("errno in thread (%p): %d\n", &errno, errno);

	return NULL;
}

int main(void)
{
	pthread_t new;
	int err;

	me = 100;
	you = 999;
	them = 3;
	printf("me before create (%p): %zu\n", &me, me);
	printf("you before create (%p): %zu\n", &you, you);
	printf("them before create (%p): %zu\n", &them, them);
	printf("errno before create (%p): %d\n", &errno, errno);

	err = pthread_create(&new, NULL, tf, (void *) 1);
	if (err < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	err = pthread_create(&new, NULL, tf, (void *) 2);
	if (err < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	printf("me after create before join (%p): %zu\n", &me, me);
	printf("you after create before join (%p): %zu\n", &you, you);
	printf("them after create before join (%p): %zu\n", &them, them);
	printf("errno after create before join (%p): %d\n", &errno, errno);
	pthread_join(new, NULL);
	printf("me after join (%p): %zu\n", &me, me);
	printf("you after join (%p): %zu\n", &you, you);
	printf("them after join (%p): %zu\n", &them, them);
	printf("errno after join (%p): %d\n", &errno, errno);

	return 0;
}
