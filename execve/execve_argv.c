/*
 * Do an execve call for a command passed as argument to the current command.
 *
 * Sample usage:
 *    ./execve_argv /bin/ls
 *    ./execve_argv /bin/ls -l
 *    ./execve_argv /bin/ls -l /tmp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define USE_TEST_RUN		0

int main(int argc, char **argv)
{
	int rc;

	if (argc == 1) {
		fprintf(stderr, "You need to pass at least one argument.\n");
		fprintf(stderr, "Sample run:\n");
		fprintf(stderr, "\t%s /bin/ls -l\n", argv[0]);
		fprintf(stderr, "\t%s /bin/ping 8.8.8.8\n", argv[0]);
		fprintf(stderr, "\t%s /sbin/ifconfig eth0\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*
	 * We need to call execve on the command passed as the first argument
	 * to our program.
	 *
	 * So, when we do:
	 *     ./execve_argv /bin/ls -l
	 *
	 * we need to call something like
	 *     execve("/bin/ls", { "/bin/ls", "-l", NULL }, NULL);
	 *
	 * First we do a test run and then we use the actual passed arguments.
	 */

#if USE_TEST_RUN == 1

	/* This is just a test run for execve(). */
	char *args[] = { "/bin/ls", "-l", NULL };
	rc = execve("/bin/ls", args, NULL);
	if (rc < 0) {
		perror("execve");
		exit(EXIT_FAILURE);
	}

#else

	/*
	 * We need to use the first argument (argv[1]) as the command to
	 * exec. And all the arguments (argv[1] included) need to be passed
	 * as an array as a second argument for execve().
	 *
	 * The call should be something like:
	 *     execve(argv[1], [ argv[1], argv[2], ..., NULL ], NULL);
	 *
	 * Due to the way arguments are passed to the main function,
	 * the array [ argv[1], argv[2], ..., NULL ] is actually argv+1, a
	 * NULL-terminated array starting from argv[1].
	 *
	 * The execve call is then:
	 *     execve(argv[1], argv+1, NULL);
	 */
	rc = execve(argv[1], argv+1, NULL);
	if (rc < 0) {
		perror("execve");
		exit(EXIT_FAILURE);
	}

#endif

	return 0;
}
