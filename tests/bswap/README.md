This code snippet shows a difference in compiler behavior between GCC and Clang/LLVM. Clang will complain if you use a name for a macro and then reuse that name for a function; GCC doesnt't complain.

In the `bswap.c` source code file, the `__bswap16`, `__bswap32` and `__bswap64` are first defined and macros and then as (inline) functions. Compiling it with GCC works:
```
$ CC=gcc make
gcc -Wall -nostdinc   -c -o bswap.o bswap.c
bswap.c: In function ‘main’:
bswap.c:42:16: warning: variable ‘g’ set but not used [-Wunused-but-set-variable]
  unsigned long g;
                ^
bswap.c:40:15: warning: variable ‘e’ set but not used [-Wunused-but-set-variable]
  unsigned int e;
               ^
bswap.c:38:17: warning: variable ‘c’ set but not used [-Wunused-but-set-variable]
  unsigned short c;
                 ^
gcc -static -nostdlib -nodefaultlibs -Wl,-emain  bswap.o   -o bswap
```

But compiling it with Clang fails:
```
$ CC=clang make
clang -Wall -nostdinc   -c -o bswap.o bswap.c
bswap.c:10:1: error: definition of builtin function '__builtin_bswap16'
__bswap16(__uint16_t _x)
^
bswap.c:1:23: note: expanded from macro '__bswap16'
#define __bswap16(_x)   __builtin_bswap16(_x)
                        ^
bswap.c:17:1: error: definition of builtin function '__builtin_bswap32'
__bswap32(__uint32_t _x)
^
bswap.c:2:23: note: expanded from macro '__bswap32'
#define __bswap32(_x)   __builtin_bswap32(_x)
                        ^
bswap.c:25:1: error: definition of builtin function '__builtin_bswap64'
__bswap64(__uint64_t _x)
^
bswap.c:3:23: note: expanded from macro '__bswap64'
#define __bswap64(_x)   __builtin_bswap64(_x)
                        ^
3 errors generated.
<builtin>: recipe for target 'bswap.o' failed
make: *** [bswap.o] Error 1
```
