#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buf[256];

	printf("pid is: %d\n", getpid());

	readlink("/proc/self", buf, 256);
	printf ("/proc/self points to %s\n", buf);

	return 0;
}
