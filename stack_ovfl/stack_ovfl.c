/*
 * stack overflow test case
 *
 * 2009, Razvan Deaconescu <razvan.deaconescu@cs.pub.ro>
 *
 * This program is architecture dependent. It has been tested on x86 and
 * x86_64 architectures, under Debian GNU/Linux, GCC 4.3.4
 */

#include <stdio.h>
#include <string.h>

#define WRAPPER_MESSAGE		"the merging is complete"
#define NEW_CALL_MESSAGE	"break on through"

#define ARRAY_LEN		5

#if defined __x86_64__
  #define get_esp(esp) __asm__("movq %%rsp, %0;":"=&r"(esp))
  #define get_ebp(ebp) __asm__("movq %%rbp, %0;":"=&r"(ebp))
#elif defined __i386__
  #define get_esp(esp) __asm__("movl %%esp, %0;":"=&r"(esp))
  #define get_ebp(ebp) __asm__("movl %%ebp, %0;":"=&r"(ebp))
#endif


/* store ebp (frame pointer) value */
static unsigned long int *ebp;


/*
 * print current stack frame and ccount words of context; that is
 * print the interval [ebp+ccount; ebp-ccount]; ebp (rbp) points to the
 * current stack frame (that is the saved frame pointer)
 *
 * adresses are printed from top to bottom (low addresses grow down)
 * we assume the stack grows down
 *
 * the print output will show
 *
 * [ebp + ccount]      value
 * [ebp + ccount - 1]  value
 * ...
 * [ebp + 1]           return address
 * [ebp]               old ebp (saved frame pointer / sfp)
 * [ebp - 1]           ...
 * ....
 * [ebp - ccount + 1]  local function variables (automatic variables)
 * [ebp - ccount]      local function variables (automatic variables)
 */

static void print_stack_frame(const char *msg, size_t ccount)
{
	int i;

	puts(msg);

	for (i = ccount; i >= 2; i--)
		printf("[%p] %016lx\n", ebp + i, *(ebp + i));

	puts("================");
	printf("[%p] %016lx (return address)\n", ebp + 1, *(ebp + 1));
	printf("[%p] %016lx (saved frame pointer)\n", ebp, *ebp);
	puts("================");

	for (i = 1; i <= ccount; i++)
		printf("[%p] %016lx\n", ebp - i, *(ebp - i));
}

/*
 * function called through return address overwrite
 */

static void new_call(void)
{
	puts(NEW_CALL_MESSAGE);
}

/*
 * standard function call; it defines and local array variable (v[5])
 *
 * standard stack frame is:
 * ---
 * high address: (return address)
 *               (saved frame pointer)
 *               (?????) (some guarding value, probably)
 *               a[4]
 *               a[3]
 *               a[2]
 *               a[1]
 * low adress:   a[0]
 * ---
 *
 * thus, a[7] refers to the return address
 */

/* need function declaration in order to print its address */
static void wrapper(void);

static void standard_call(void)
{
	long a[ARRAY_LEN];
	int i;

	printf("wrapper function (caller) address is %p\n", wrapper);
	printf("new_call function address is %p\n\n", new_call);

	get_ebp(ebp);

	/* init array */
	for (i = 0; i < ARRAY_LEN; i++)
		a[i] = i;

	print_stack_frame("=== before overwrite ===", 8);

	/* ARRAY_LEN + 2 refers the return address */
	a[ARRAY_LEN+2] = (long) new_call;

	puts("\n\n");
	print_stack_frame("=== after overwrite ===", 8);
}

static void wrapper(void)
{
	standard_call();
	puts(WRAPPER_MESSAGE);
}

int main(void)
{
	wrapper();
	return 0;
}
