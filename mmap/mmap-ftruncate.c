/*
 * See what happens whan mapping a non-truncated file and what happens
 * when doing private mapping on a file.
 *
 * 2011, Razvan Deaconescu, razvan.deaconescu@cs.pub.ro
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

/* Turn to MAP_PRIVATE for private mapping. */
#define MAPPING_TYPE		MAP_SHARED

/* Uncomment to enable file truncation (ftruncate(2)). */
/*#define TRUNCATE_FILE		1*/

#define FILENAME		"test.map"
#define MAPPING_SIZE		(getpagesize())

int main(void)
{
	int fd;
	char *addr;

	/* For testing purpose, remove file from filesystem. */
	unlink(FILENAME);

	fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

#if TRUNCATE_FILE == 1
	if (ftruncate(fd, MAPPING_SIZE) < 0) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
#endif

	addr = mmap(NULL, MAPPING_SIZE, PROT_READ | PROT_WRITE, MAPPING_TYPE, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	/*
	 * Do access.
	 * In case of shared-mapping on non-truncated file, this results
	 * in the delivery of SIGBUS.
	 */
	*addr = 'a';

	munmap(addr, MAPPING_SIZE);
	close(fd);

	return 0;
}
