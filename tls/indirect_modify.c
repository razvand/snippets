#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Offset is determined by running the program and computing
 * (&age - &placeholder) / sizeof(unsigned int).
 */
#define OFFSET_FROM_LOCAL_TO_TLS	522

/*
 * &age is at fs:0xfffffffffffffffc, i.e. tcb-0x4
 * stack guard is at fs:0x28, i.e. tcb+x028
 * offset is (0x28-(-0x04))/4 = 11
 */
#define OFFSET_FROM_TLS_TO_STACK_GUARD	11

static __thread unsigned int age;

static void *tf(void *arg)
{
	unsigned int placeholder;
	unsigned int *ptr;
	unsigned long *stack_guard_ptr;

	ptr = &placeholder;
	printf("placeholder address: %p\n", &placeholder);

	age = 22;
	printf("age (address: %p): %u\n", &age, age);

	* (ptr + OFFSET_FROM_LOCAL_TO_TLS) = 99;
	printf("age (address: %p): %u\n", &age, age);

	/* Print then overwrite stack guard with some gibberish. */
	stack_guard_ptr = (unsigned long *) (ptr + OFFSET_FROM_LOCAL_TO_TLS + OFFSET_FROM_TLS_TO_STACK_GUARD);
	printf("stack guard / canary (address: %p): 0x%016lx\n", stack_guard_ptr, *stack_guard_ptr);
	* (stack_guard_ptr) = 0xaabbccddeeff0011;

	return NULL;
}

int main(void)
{
	pthread_t new;
	int err;

	err = pthread_create(&new, NULL, tf, (void *) 1);
	if (err < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	pthread_join(new, NULL);

	return 0;
}
