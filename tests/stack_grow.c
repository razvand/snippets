#include <stdio.h>

static int *p_fcaller;
static int *p_fcalled;

static void f2(void)
{
	int f2_local;

	p_fcalled = &f2_local;

	if (p_fcalled > p_fcaller)
		printf("stack grows up\n");
	else
		printf("stack grows down\n");
}

void f1(void)
{
	int f1_local;

	p_fcaller = &f1_local;
	f2();
}

int main(void)
{
	f1();

	return 0;
}
