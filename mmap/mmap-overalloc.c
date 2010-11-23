#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(void)
{
	void *a;

	a = mmap(NULL, (size_t) 3*1024*1024*1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (a == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	return 0;
}
