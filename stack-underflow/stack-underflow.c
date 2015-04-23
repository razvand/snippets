#include <stdio.h>

/*
 * Underflow value is determined by the check the Linux kernel does for stack
 * access.
 * See: http://lxr.free-electrons.com/source/arch/x86/mm/fault.c?v=3.13#L1171
 *
 * If using UNDERFLOW_ALMOST_FAULT the program will be OK.
 * If using UNDERFLOW_WILL_FAULT the program will crash due to invalid memory
 * access (it gets a SIGSEGV).
 */
#define UNDERFLOW_ALMOST_FAULT	(64 * 1024 + 32 * sizeof(unsigned long) - 1024)
#define UNDERFLOW_WILL_FAULT	(64 * 1024 + 32 * sizeof(unsigned long) + 1024)


static int my_func(void)
{
	/*
	 * Allocate a large buffer on the stack to increase its size past the
	 * initial stack allocation size.
	 */
	unsigned char buf[256*1024];

	/*
	 * Change to #if 1 if you want to use the stack pointer directly,
	 * instead of the buffer address.
	 */
#if 0
	unsigned char *esp;
	asm("movl %%esp, %0\n" :"=r"(esp));

	* (esp - UNDERFLOW_ALMOST_FAULT) = 0x41;
#else
	* (buf - UNDERFLOW_ALMOST_FAULT) = 0x41;
#endif

	/* dumb return statement */
	return * (buf - 5);
}

int main(void)
{
	/* dumb function call */
	printf ("%d\n", my_func());

	return 0;
}
