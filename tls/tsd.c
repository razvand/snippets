#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

static pthread_key_t me_key;
static pthread_key_t you_key;
static pthread_key_t them_key;

static void *tf(void *arg)
{
	pthread_setspecific(me_key, (const void *) 200);
	printf("me_key in thread (%p): %u, me value in thread: %zu\n", &me_key, me_key, (size_t) pthread_getspecific(me_key));
	printf("you_key in thread (%p): %u, you value in thread: %zu\n", &you_key, you_key, (size_t) pthread_getspecific(you_key));
	printf("them_key in thread (%p): %u, them value in thread: %zu\n", &them_key, them_key, (size_t) pthread_getspecific(them_key));

	return NULL;
}

int main(void)
{
	pthread_t new;
	int err;

	pthread_key_create(&me_key, NULL);
	pthread_key_create(&you_key, NULL);
	pthread_key_create(&them_key, NULL);

	pthread_setspecific(me_key, (const void *) 100);
	pthread_setspecific(you_key, (const void *) 999);
	pthread_setspecific(them_key, (const void *) 3);
	printf("me_key before create (%p): %u, me value before create: %zu\n", &me_key, me_key, (size_t) pthread_getspecific(me_key));
	printf("you_key before create (%p): %u, me value before create: %zu\n", &you_key, you_key, (size_t) pthread_getspecific(you_key));
	printf("them_key before create (%p): %u, me value before create: %zu\n", &them_key, them_key, (size_t) pthread_getspecific(them_key));

	err = pthread_create(&new, NULL, tf, NULL);
	if (err < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	printf("me_key after create before join (%p): %u, me value after create before join: %zu\n", &me_key, me_key, (size_t) pthread_getspecific(me_key));
	printf("you_key after create before join (%p): %u, you value after create before join: %zu\n", &you_key, you_key, (size_t) pthread_getspecific(you_key));
	printf("them_key after create before join (%p): %u, them value beafter create before join: %zu\n", &them_key, them_key, (size_t) pthread_getspecific(them_key));
	pthread_join(new, NULL);
	printf("me_key after join (%p): %u, me value after join: %zu\n", &me_key, me_key, (size_t) pthread_getspecific(me_key));
	printf("you_key after join (%p): %u, you value after join: %zu\n", &you_key, you_key, (size_t) pthread_getspecific(you_key));
	printf("them_key after join (%p): %u, them value after join: %zu\n", &them_key, them_key, (size_t) pthread_getspecific(them_key));

	/* This is really not required, but we call it for API completeness. */
	pthread_key_delete(me_key);
	pthread_key_delete(you_key);
	pthread_key_delete(them_key);

	return 0;
}
