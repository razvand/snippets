#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DO_READ		0
#define DO_WRITE	1
#define MY_MAP_TYPE	DO_WRITE

int main(void)
{
	int fd;
	char *p;
	char buffer[8];

	fd = open("a.test", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	ftruncate(fd, 4096);

#if MY_MAP_TYPE == DO_READ
	p = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
#elif MY_MAP_TYPE == DO_WRITE
	p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#else
#error "Unknown map type macro"
#endif
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	printf("p[0] = %02x, p[1] = %02x, p[2] = %02x\n", p[0], p[1], p[2]);
#if MY_MAP_TYPE == DO_WRITE
	sprintf(buffer, "%d", getpid());
	memcpy(p, buffer, strlen(buffer));
#endif

	sleep(100);

	return 0;
}
