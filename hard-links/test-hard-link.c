#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define INITIAL_LINK	"initial.txt"
#define HARD_LINK_1	"hard-link-1.txt"
#define HARD_LINK_2	"hard-link-2.txt"

int main(void)
{
	struct stat sbuf;
	int rc;

	creat(INITIAL_LINK, 0644);
	link(INITIAL_LINK, HARD_LINK_1);
	link(INITIAL_LINK, HARD_LINK_2);

	/* Get number of links. */
	rc = stat(INITIAL_LINK, &sbuf);
	if (rc < 0)
		perror("stat");
	else
		printf("Number of links is %lu\n", sbuf.st_nlink);

	unlink(INITIAL_LINK);
	unlink(HARD_LINK_1);
	unlink(HARD_LINK_2);

	return 0;
}
