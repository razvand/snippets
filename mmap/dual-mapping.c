#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	int *ptr1, *ptr2;
	int i;

	fd = open("a.dat", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	ftruncate(fd, getpagesize());

	ptr1 = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, 0);
	if (ptr1 == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	ptr2 = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, 0);
	if (ptr2 == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	printf("ptr1 = %p, ptr2 = %p\n");
	memset(ptr1, 0, sizeof(int));
	memset(ptr2, 0, sizeof(int));

	for (i = 0; i < 10; i++) {
		*ptr1 = rand();
		printf("*ptr1 = %d; *ptr2 = %d\n", *ptr1, *ptr2);
	}

	return 0;
}
