#include <stdio.h>
#include <signal.h>
#include <time.h>

void handler(int signal)
{
}

int main(void)
{
	struct sigevent sigev;
	timer_t timerid;
	struct itimerspec its;
	int signal_value;
	sigset_t mask;

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	sigev.sigev_value.sival_ptr = &timerid;

	/* Configure signal. */
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	signal(SIGUSR1, handler);

	timer_create(CLOCK_REALTIME, &sigev, &timerid);

	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 500000000; /* 0.5 seconds */
	its.it_interval.tv_sec = 3;
	its.it_interval.tv_nsec = 500000000; /* 0.5 seconds */

	timer_settime(timerid, 0, &its, NULL);

	while (1) {
		printf("wait for timer\n");
		sigwait(&mask, &signal_value);
		printf("after timer\n");
	}

	return 0;
}
