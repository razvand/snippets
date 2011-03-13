#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int fd = 5042;
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
