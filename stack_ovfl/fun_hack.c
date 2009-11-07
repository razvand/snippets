/*
 * fun_hack.c: simple buffer overflow program
 *
 * 2006 Razvan Deaconescu
 */

#include <stdio.h>

void fun_hack (void)
{
	__asm__ ("movl %%edx, 4(%%ebp);"
			:
			:
			: "%edx");

	printf ("hacked\n");
}

void fun_orig (void)
{
	int old_ret;
	int *ret;

	old_ret = * ((int *) &old_ret + 2);
	ret = (int *) &old_ret + 2;
	*ret = (int) fun_hack;

	printf ("original\n");

	__asm__ ("movl %0, %%edx;"
			:
			: "g" (old_ret)
			: "%edx"
			);
}

int main (void)
{
	printf ("main before original\n");

	fun_orig ();

	printf ("main after original\n");

	return 0;
}
