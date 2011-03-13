#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define MY_FD	42

int main(void)
{
	int fd = MY_FD;
	ssize_t nbytes;

	nbytes = write(fd, "hello", 6);
	if (nbytes < 0) {
		perror("write");
		if (errno == EBADF)
			fprintf(stderr, "errno: EBADF\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
