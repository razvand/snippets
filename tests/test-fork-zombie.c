#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	pid_t pid1;
	pid_t pid2;

	pid1 = fork();
	switch (pid1) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;

	case 0:
		printf("pid1: %d\n", pid1);
		pid2 = fork();
		switch (pid2) {
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			printf("pid1: %d\n", pid2);
			sleep(5);
			exit(EXIT_SUCCESS);
		default:
			sleep(10);

			exit(EXIT_SUCCESS);
		}
		break;

	default:
		sleep(15);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
