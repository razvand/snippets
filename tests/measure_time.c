#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#define SEC_TO_USEC(s)		((s) * 1000 * 1000)
#define NSEC_TO_USEC(s)		((s) / 1000)

typedef struct timespec TIMETYPE;

static TIMETYPE start_time;
static TIMETYPE stop_time;

static void get_time(TIMETYPE *time_ptr)
{
	if (clock_gettime(CLOCK_REALTIME, time_ptr) < 0) {
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
}

static unsigned long us_time(TIMETYPE *time_ptr)
{
	return SEC_TO_USEC(time_ptr->tv_sec) + NSEC_TO_USEC(time_ptr->tv_nsec);
}

static void do_measure1(void)
{
	get_time(&start_time);

	{
		/* TODO: do action 1 */
		sleep(1);	/* just an example */
	}

	get_time(&stop_time);

	printf(" * Duration in microseconds (no 1): %0lu\n",
			us_time(&stop_time) - us_time(&start_time));
}

static void do_measure2(void)
{
	get_time(&start_time);

	{
		/* TODO: do action 2 */
		sleep(2);	/* just an example */
	}

	get_time(&stop_time);

	printf(" * Duration in microseconds (no 2): %0lu\n",
			us_time(&stop_time) - us_time(&start_time));
}

int main(void)
{
	do_measure1();
	do_measure2();

	return 0;
}
