#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

const int TOTAL_SLEEP_MS = 10 * 1000 * 1000;

int main(int argc, char * argv[])
{
	int i;
	char * p;
	if (argc < 3) {
		fprintf(stderr, "usage: %s filename msec_sleep val\n", argv[0]);
		exit(1);
	}
	int first_sleep_ms = atoi(argv[2]);
	int len = 100*1024*1024;

	int fd = open(argv[1], O_RDWR);
	if (fd == -1) { perror("open"); exit(1); }
	
	p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) { perror("mmap"); exit(1); }

	for (i = 0; i < len; i++)
		p[i] = 0;

	printf("[%d] -- sleep %d\n", getpid(), first_sleep_ms);
	usleep(first_sleep_ms);
	printf("[%d] val=%d, making it %d\n", getpid(), *p, atoi(argv[3]));
	*p = atoi(argv[3]);
	usleep(TOTAL_SLEEP_MS - first_sleep_ms);
	printf("[%d] -- done\n", getpid());

	munmap(p, len);
	close(fd);

	return 0;
}
