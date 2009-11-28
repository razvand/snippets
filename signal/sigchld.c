/*
 * sigchld.c: test the behavior of waitpid(2) when parent process
 * 	ignores (SIG_IGN) the SIGCHLD signal
 *
 * Disclaimer: SIGCHLD is delivered to a parent process when a child process
 * 	terminates; it is tipically ignored. However, explictly using
 * 	SIG_IGN as a signal handler has certain consequences.
 *
 * Useful links:
 *     http://www.win.tue.nl/~aeb/linux/lk/lk-5.html#ss5.5
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>


#define CHILD_SLEEP_TIME	5
#define PARENT_SLEEP_TIME	2


int main(void)
{
	struct sigaction act;
	pid_t pid;
	int exitcode;

	memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;

	/* SIGCHLD is ignored (SIG_IGN) */
	sigaction(SIGCHLD, &act, NULL);

	printf("Child process sleep time is %d seconds.\n", CHILD_SLEEP_TIME);
	printf("Parent process sleep time is %d seconds.\n\n", PARENT_SLEEP_TIME);

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		perror("fork");
		exit(EXIT_FAILURE);

	case 0:		/* child process */
		printf("Child process prepares to sleep for %d seconds.\n", CHILD_SLEEP_TIME);
		sleep(CHILD_SLEEP_TIME);
		printf("Child process has slept for %d seconds. Will now exit.\n", CHILD_SLEEP_TIME);
		exit(EXIT_SUCCESS);

	default:	/* parent process */
		break;
	}

	printf("Parent process prepares to sleep for %d seconds.\n", PARENT_SLEEP_TIME);
	sleep(PARENT_SLEEP_TIME);
	printf("Parent process has slept for %d seconds. Will now wait for child.\n", PARENT_SLEEP_TIME);

	/*
	 * parent waits for child; is there any circumstance when waitpid
	 * return 0? seems not
	 */

again:
	if (waitpid(pid, &exitcode, 0) < 0) {
		switch (errno) {
		case EINTR:
			printf("waitpid interrupted. Retry ...\n");
			goto again;

		case ECHILD:
			printf("Parent process has waited for child process to end.\n");
			break;
		}
	}
	else
		printf("waitpid returned 0.\n");

	return 0;
}
