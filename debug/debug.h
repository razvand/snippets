/*
 * debugging macros
 *    heavily inspired by previous work and Internet resources
 *
 * uses C99 variadic macros
 * uses non-standard usage of the token-paste operator (##) for
 *   removing the comma symbol (,) when not followed by a token
 * uses non-standard __FUNCTION__ macro (MSVC doesn't support __func__)
 * tested on gcc 4.4.5 and Visual Studio 2008 (9.0), compiler version 15.00
 *
 * 2011, Razvan Deaconescu, razvan.deaconescu@cs.pub.ro
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

/*
 * define DEBUG macro as a compiler option:
 *    -DDEBUG for GCC
 *    /DDEBUG for MSVC
 */

#if defined DEBUG
#define dprintf(format, ...)					\
	fprintf(stderr, " [%s(), %s:%u] " format,		\
			__FUNCTION__, __FILE__, __LINE__,	\
			##__VA_ARGS__)
#else
#define dprintf(format, ...)					\
	do {							\
	} while (0)
#endif

#endif
