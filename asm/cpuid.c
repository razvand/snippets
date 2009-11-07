/*
 * cpuid.c: C program using inline assembly for using cpuid instruction
 *
 * 2006 Razvan Deaconescu <razvan@anaconda.cs.pub.ro>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	unsigned int eax, ebx, ecx, edx;
	char buf[32];

	__asm__ __volatile__ (
			"movl	$0,	%%eax	;\n"
			"cpuid			;\n"
			"movl	%%eax,	%0	;\n"
			"movl	%%ebx,	%1	;\n"
			"movl	%%ecx,	%2	;\n"
			"movl	%%edx,	%3	;\n"
			: "=g" (eax), "=g" (ebx), "=g" (ecx), "=g" (edx)
			:
			: "eax", "ebx", "ecx", "edx"
			);

	memcpy (buf, &ebx, 4);
	memcpy (buf+4, &edx, 4);
	memcpy (buf+8, &ecx, 4);
	buf[12] = '\0';

	printf ("maximum input value for cpuid: %u\n", eax);
	printf ("cpu: %s\n", buf);

	__asm__ __volatile__ (
			"movl	$1,	%%eax	;\n"
			"cpuid			;\n"
			"movl	%%eax,	%0	;\n"
			"movl	%%ebx,	%1	;\n"
			"movl	%%ecx,	%2	;\n"
			"movl	%%edx,	%3	;\n"
			: "=g" (eax), "=g" (ebx), "=g" (ecx), "=g" (edx)
			:
			: "eax", "ebx", "ecx", "edx"
			);

	printf ("eax: %08x\tebx: %08x\tecx: %08x\tedx: %08x\n", eax, ebx, ecx, edx);

	return 0;
}

