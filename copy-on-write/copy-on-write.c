#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define MMAP_SIZE	(1024 * 4096)
#define TIMEOUT		10

int main(void)
{
	pid_t pid;
	char *a;
	size_t i;

	/* allocate virtual pages - demand paging */
	a = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (a == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	printf(" [initial] pid = %d\n", getpid());

	printf(" [initial] Force demand paging. Waiting %d seconds.\n", TIMEOUT);
	sleep(TIMEOUT);

	/* allocate physical pages */
	for (i = 0; i < 1024; i++)
		a[i*4096] = i;
	printf(" [initial] Done demand paging. Waiting %d seconds.\n", TIMEOUT);
	sleep(TIMEOUT);

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		perror("fork");
		exit(EXIT_FAILURE);


	case 0:		/* child process */
		printf(" [child] Doing copy on write. Waiting %d seconds.\n", TIMEOUT);
		sleep(TIMEOUT);

		/* force copy on write */
		for (i = 0; i < 1024; i++)
			a[i*4096] = 1024-i;

		printf(" [child] Done copy on write. Waiting %d seconds.\n", TIMEOUT);
		sleep(TIMEOUT);

		exit(EXIT_SUCCESS);

	default:	/* parent process */
		break;
	}

	/* parent process */
	printf(" [parent] Waiting for child.\n");
	wait(NULL);

	printf(" [parent] Doing copy on write.  Waiting %d seconds.\n", TIMEOUT);
	sleep(TIMEOUT);

	/* force copy on write */
	for (i = 0; i < 1024; i++)
		a[i*4096] = 1024-i;

	printf(" [parent] Done copy on write. Waiting %d seconds.\n", TIMEOUT);
	sleep(TIMEOUT);

	return 0;
}
