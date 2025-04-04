# Analysis of GOT in ELF Programs

Addresses of global symbols (global variables and functions) are only known at load time for dynamically linked libraries; the program is built to work with different versions of dynamic libraries; each version uses different symbol addresses.
Moreover, program and library code will be most likely randomly placed in memory (via ASLR - *Address Space Layout Randomization*).
Lastly, [IFUNC (*indirect functions*) support](https://sourceware.org/glibc/wiki/GNU_IFUNC) provides multiple implementations of a given function, the address of which will only be known at runtime.

In ELF programs, GOT (*Global Offset Table*) stores **addresses** that are **unknown until load time**.
The linker creates GOT entries in the resulting program executable; the entries to be populated by the loader in the program memory.

By default, ELF files have two sections storing GOT information:
1. `.got` stores addresses of global variables
1. `.got.plt` stores addresses of functions; it is used in conjunction with the `.plt` section, that stores code to access `.got.plt` entries

Entries in `.got` are accessed directly by the program code, via instructions such as:
```
mov rax, QWORD PTR [got_address]    # Read variable address from .got in RAX register.
mov rbx, [rax]                      # Read actual variable value in RBX register.
```

Entries in `.got.plt` are access indirectly by the program code, via calls to entries in the `.plt` section.
The `.plt` (*Procedure Linkage Table*) section is a trampoline section; it consists of small pieces of code that jump to function addresses stored in `.got.plt` entries.
A sample instruction in `.plt` is
```
jmp QWORD PTR [got_plt_address]     # Jump to function address stored in .got.plt.
```

## Requirements

We require the GNU toolchain (compiler, linker, assembler) and GNU make for building the demo files.
We require `nm`, `objdump` and `readelf` for static analysis.
We require GDB for dynamic analysis.

## Demo Files

There are two source code files (`main.c` and `basket.c`), a header file (`basket.h`) and a `Makefile`.
The `basket.c` file will be compiled into a shared library (`libbasket.so`).
The `main.c` will be compiled and linked against the shared library, resulting in an executable `main`.
We investigate the resulting files: the `main` executable and the `libbasket.so` library.

To limit the amount of unnecessary information (such as additional sections and functions added by the default compilation and the use of the standard C library), we use the `nostdlib/` folder.
When building files in `nostdlib/`, as its name tells, there will be no use of the standard C library, reducing the unnecessary information.
To build and run without standard C library support, we require a small assembly file (`start.s`) that defines the program entry point (`_start`) (using `-e_start` as a linker option) and wraps the call to the `main()` function.

Build the `main` executable and the `libbasket.so` library:
```
$ make
as   -o start.o start.s
cc -fPIC -fno-stack-protector -Wall -Wextra   -c -o main.o main.c
cc -fPIC -fno-stack-protector -Wall -Wextra   -c -o basket.o basket.c
ld -shared -o libbasket.so basket.o
ld -e_start -pie -dynamic-linker=/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 -rpath=. -o main start.o main.o -L. -lbasket
```

Running the program prints nothing, but that's not relevant for our investigation:
```
$ ./main
```

## Source Code Analysis

The two source code files are simplistic.

`basket.c` defines a global variable `basket_size` (initialized at `3`) and a function `flowers()`:
```
$ cat basket.c
unsigned long basket_size = 3;

void flowers(void)
{
	basket_size = 55;
}
```
Both symbols (the global variable `basket_size` and the function `flowers()`) are exported (i.e. not marked `static`).

`main.c` calls the `flowers()` function and writes to the `basket_size` variable:
```
$ cat main.c
#include "basket.h"

int main(void)
{
	flowers();
	basket_size = 99;

	return 0;
}
```
`main.c` references the two symbols through their declarations in `basket.h`:
```
#ifndef BASKET_H_
#define BASKET_H_	1

extern unsigned long basket_size;

void flowers(void);

#endif
```

The `basket_size` and the `flowers` symbols will be part of the `libbasket.so` library.
We expect the `main` program to access these symbols via GOT.
We use static and dynamic analysis to validate our expectation.

## Static Analysis

**Note**: The addresses shown in the analysis will differ from your own.
Different build tools, different environments, different versions of the standard C library, memory randomization will lead to other addresses being used.

We use `objdump` and `readelf` for static binary analysis of the `main` executable file and the `libbasket.so` library file.

We check the symbols in both files:
```
$ nm libbasket.so
0000000000201018 D basket_size
[...]
0000000000000298 T flowers
[...]
$ nm main
                 U basket_size
[...]
                 U flowers
[...]
0000000000000391 T main
[...]
```
`libbasket.so` defines and exports the `basket_size` and the `flowers` symbols.
`main` defines and exports the `main` symbol and uses the `basket_size` and `flowers`, both of which are undefined.
Their addresses will only be known at runtime.

We see that `main` has `.got` and `.got.plt` sections:
```
$ readelf -S main
There are 18 section headers, starting at offset 0x13e0:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
[...]
  [12] .got              PROGBITS         0000000000200ff8  00000ff8
       0000000000000008  0000000000000008  WA       0     0     8
  [13] .got.plt          PROGBITS         0000000000201000  00001000
       0000000000000020  0000000000000008  WA       0     0     8
[...]
```
Both sections are writable and readable (`WA` in the `Flags` column, for *write* and *access*).
`.got` starts at address `0x200ff8`, `.got.plt` starts at address `0x201000`.

We check their contents:
```
$ readelf -x .got main

Hex dump of section `.got`:
  0x00200ff8 00000000 00000000                   ........

$ readelf -x .got.plt main

Hex dump of section `.got.plt`:
 NOTE: This section has relocations against it, but these have NOT been applied to this dump.
  0x00201000 880e2000 00000000 00000000 00000000 .. .............
  0x00201010 00000000 00000000 76030000 00000000 ........v.......
```

The `.got` section contains one entry (8 bytes), while the `.got.plt` section contains four entries (32 bytes).
Both sections are zero-filled (with some exceptions that we won't delve into).
Their useful content (variable and function addresses) is unknown until load time.

We see how the `.got` section is used by the program, in the `.text` section (where the `main()` function resides):
```
$ objdump -d -M intel -j .text main

main:     file format elf64-x86-64


Disassembly of section .text:

0000000000000380 <_start>:
 380:	e8 0c 00 00 00       	call   391 <main>
 385:	48 89 c7             	mov    rdi,rax
 388:	48 c7 c0 3c 00 00 00 	mov    rax,0x3c
 38f:	0f 05                	syscall

0000000000000391 <main>:
 391:	55                   	push   rbp
 392:	48 89 e5             	mov    rbp,rsp
 395:	e8 d6 ff ff ff       	call   370 <flowers@plt>
 39a:	e8 d1 ff ff ff       	call   370 <flowers@plt>
 39f:	48 8b 05 52 0c 20 00 	mov    rax,QWORD PTR [rip+0x200c52]        # 200ff8 <basket_size>
 3a6:	48 c7 00 63 00 00 00 	mov    QWORD PTR [rax],0x63
 3ad:	b8 00 00 00 00       	mov    eax,0x0
 3b2:	5d                   	pop    rbp
 3b3:	c3                   	ret
```

At address `39f` above, the instruction accesses the `200ff8` address, marked as referring the `basket_size` symbol.
The `0x200ff8` is the address of the entry in `.got`.

We see how the `.got.plt` section is used by the trampoline code in the `.plt` section:
```
$ objdump -d -M intel -j .plt main

main:     file format elf64-x86-64


Disassembly of section .plt:

0000000000000360 <.plt>:
 360:	ff 35 a2 0c 20 00    	push   QWORD PTR [rip+0x200ca2]        # 201008 <_GLOBAL_OFFSET_TABLE_+0x8>
 366:	ff 25 a4 0c 20 00    	jmp    QWORD PTR [rip+0x200ca4]        # 201010 <_GLOBAL_OFFSET_TABLE_+0x10>
 36c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000000370 <flowers@plt>:
 370:	ff 25 a2 0c 20 00    	jmp    QWORD PTR [rip+0x200ca2]        # 201018 <flowers>
 376:	68 00 00 00 00       	push   0x0
 37b:	e9 e0 ff ff ff       	jmp    360 <.plt>
```

At address `370` above, the instruction accesses the `201018` address, marked as referring the `flowers` symbol.
`0x201018` is the address of the last (4th) entry in the `.got.plt` section.

With static analysis, we found that:
* The `.got` and `.got.plt` sections are not filled with actual data (with some exceptions in `.got.plt` that we don't delve into).
* The `.got` section is used directly in the main program.
* The `.got.plt` section is used by the trampoline code in the `.plt` section.

## Dynamic Analysis

**Note**: Similarly to the static analysis section, addresses shown as part of the dynamic analysis will differ from your own.

We use GDB for dynamic analysis.
Our goal is to check the contents of the `.got` and `.got.plt` sections at runtime, after being filled with the actual addresses.

Note that `main` is a *position-independent executable* (PIE), so all addresses are randomized at runtime.
We use GDB to find out the in-memory runtime addresses of the `.got` and `.got.plt` section.

We start `main` under GDB and identify the addresses of the `.got` and `.got.plt` sections:
```
$ gdb ./main
Reading symbols from ./main...(no debugging symbols found)...done.
(gdb) start
Temporary breakpoint 1 at 0x395
Starting program: /home/razvan/projects/snippets.git/got-plt/nostdlib/main

Temporary breakpoint 1, 0x0000555555554395 in main ()
(gdb) maint info sections
(gdb) maint info sections ALLOBJ
Exec file:
    `/home/razvan/projects/snippets.git/got-plt/nostdlib/main', file type elf64-x86-64.
  Object file: /home/razvan/projects/snippets.git/got-plt/nostdlib/main
    0x555555554360->0x555555554380 at 0x00000360: .plt ALLOC LOAD READONLY CODE HAS_CONTENTS
    0x555555554380->0x5555555543b4 at 0x00000380: .text ALLOC LOAD READONLY CODE HAS_CONTENTS
    [...]
    0x555555754ff8->0x555555755000 at 0x00000ff8: .got ALLOC LOAD DATA HAS_CONTENTS
    0x555555755000->0x555555755020 at 0x00001000: .got.plt ALLOC LOAD DATA HAS_CONTENTS
    [...]
```
The runtime address is `0x555555754ff8` for the `.got` section, and `0x555555755000` for the `.got.plt` section.
Note that, because `main` is a position-independent executable, these addresses differ from the ones found when doing static analysis: `0x200ff8` and `0x201000`.
Even so, their relative placement and page address (the last 3 hex digits) are identical.

### .got

We disassemble the code of the `main()` function to validate its use of the `.got` section entry:
```
(gdb) set disassembly-flavor intel
(gdb) disass main
Dump of assembler code for function main:
   0x0000555555554391 <+0>:	push   rbp
   0x0000555555554392 <+1>:	mov    rbp,rsp
=> 0x0000555555554395 <+4>:	call   0x555555554370 <flowers@plt>
   0x000055555555439a <+9>:	call   0x555555554370 <flowers@plt>
   0x000055555555439f <+14>:	mov    rax,QWORD PTR [rip+0x200c52]        # 0x555555754ff8
   0x00005555555543a6 <+21>:	mov    QWORD PTR [rax],0x63
   0x00005555555543ad <+28>:	mov    eax,0x0
   0x00005555555543b2 <+33>:	pop    rbp
   0x00005555555543b3 <+34>:	ret
End of assembler dump.
```

The 5th instruction in the assembler code dump uses address `0x555555754ff8`.
This is the address of the `.got` section, belonging to the `basket_size` symbol.

We now check the contents of the `.got` section entry for the `basket_size` symbol:
```
(gdb) x/gx 0x555555754ff8
0x555555754ff8:	0x00007ffff7dd2018
```
The `.got` entry is no longer zero-filled.
It stores the address `0x00007ffff7dd2018`, the actual address of the `basket_size` variable.
After loading the `libbasket.so` library in memory, the loader was able to determine the address of the `basket_size` variable and place it the corresponding `.got` memory entry.

We validate that the address `0x00007ffff7dd2018` is indeed the address of the `basket_size` variable by using GDB print and checking its contents:
```
(gdb) p &basket_size
$1 = (<data variable, no debug info> *) 0x7ffff7dd2018 <basket_size>
(gdb) x/gd 0x00007ffff7dd2018
0x7ffff7dd2018 <basket_size>:	3
```
The value `3` is the initial value of the `basket_size` variable.

As expected, the `basket_size` variable (at address `0x7ffff7dd2018`) is part of the `.data` section (for global data) of the `libbasket.so` shared library.
Use the `Enter`/`Return` key in the `maint info sections ALLOBJ` command below to reach the listing of sections in the `libbasket.so` object:
```
(gdb) maint info sections ALLOBJ
    [...]
  Object file: ./libbasket.so
    [...]
    0x7ffff7dd2018->0x7ffff7dd2020 at 0x00001018: .data ALLOC LOAD DATA HAS_CONTENTS
    [...]
```

### .got.plt

We disassemble the code of the `.plt` section to validate its use of the `.got.plt` section.
We use the address from the output of the `maint info sections ALLOBJ`:
```
(gdb) x/6i 0x555555554360
   0x555555554360:	push   QWORD PTR [rip+0x200ca2]        # 0x555555755008
   0x555555554366:	jmp    QWORD PTR [rip+0x200ca4]        # 0x555555755010
   0x55555555436c:	nop    DWORD PTR [rax+0x0]
   0x555555554370 <flowers@plt>:	jmp    QWORD PTR [rip+0x200ca2]        # 0x555555755018
   0x555555554376 <flowers@plt+6>:	push   0x0
   0x55555555437b <flowers@plt+11>:	jmp    0x555555554360
```

The 4th instruction in the assembler code dump (marked as `flowers@plt`) uses address `0x555555755018`.
This is an address in the `.got.plt` section, belonging to the `flowers` symbol.
The `flowers@plt` address (`0x555555554370`) is used in the `main()` function to call the `flowers()` function, as shown in the `main` assembler code dump.

We check the contents of the `.got.plt` entry belonging to the `flowers` symbol:
```
(gdb) x/gx 0x555555755018
0x555555755018:	0x0000555555554376
```
The `.got.plt` entry is no longer zero-filled.
It stores the address `0x0000555555554376`, which is a trampoline address:
```
(gdb) x/2i 0x0000555555554376
   0x555555554376 <flowers@plt+6>:	push   0x0
   0x55555555437b <flowers@plt+11>:	jmp    0x555555554360
```
The address now stored in the `.got.plt` entry is the address of the next instruction in `.plt` (`0x555555554376`).
It basically said: *Get back where you came from!*
This is a feature of the loader, called [lazy binding](https://docs.oracle.com/cd/E23824_01/html/819-0690/chapter3-7.html).
The actual function address is not determined at load time, but the first time the function is called.
So the program has to do a first call to the function for the corresponding `.got.plt` entry to be filled with the actual address.

We do a first call to the `flowers()` function by going to the next instruction in the debugged `main()` function:
```
(gdb) ni
0x000055555555439a in main ()
(gdb) disass
Dump of assembler code for function main:
   0x0000555555554391 <+0>:	push   rbp
   0x0000555555554392 <+1>:	mov    rbp,rsp
   0x0000555555554395 <+4>:	call   0x555555554370 <flowers@plt>
=> 0x000055555555439a <+9>:	call   0x555555554370 <flowers@plt>
   0x000055555555439f <+14>:	mov    rax,QWORD PTR [rip+0x200c52]        # 0x555555754ff8
   0x00005555555543a6 <+21>:	mov    QWORD PTR [rax],0x63
   0x00005555555543ad <+28>:	mov    eax,0x0
   0x00005555555543b2 <+33>:	pop    rbp
   0x00005555555543b3 <+34>:	ret
End of assembler dump.
```
We now did an initial call to the `flowers()` function via the `.plt` there-and-back trampoline.
The trampoline invoked the dynamic loader that filled the `.got.plt` entry.
We validate this by rechecking the content of the corresponding `.got.plt` entry:
```
(gdb) x/gx 0x555555755018
0x555555755018:	0x00007ffff7bd1298
```
The content is now updated to the address `0x00007ffff7bd1298`.
We expect this to be the actual address of the `flowers` function, determined by the dynamic loader from the `libbasket.so` library:
```
(gdb) p flowers
$2 = {<text variable, no debug info>} 0x7ffff7bd1298 <flowers>
(gdb) x/3i 0x00007ffff7bd1298
   0x7ffff7bd1298 <flowers>:	push   rbp
   0x7ffff7bd1299 <flowers+1>:	mov    rbp,rsp
   0x7ffff7bd129c <flowers+4>:	mov    rax,QWORD PTR [rip+0x200d55]        # 0x7ffff7dd1ff8
```
Indeed, the value stored in the `.got.plt` entry is the actual address of the `flowers` function.

As expected, the `flowers` symbol (at address `0x00007ffff7bd1298`) is part of the `.text` section (for code) of the `libbasket.so` shared library:
```
(gdb) maint info sections ALLOBJ
    [...]
  Object file: ./libbasket.so
    [...]
    0x7ffff7bd1298->0x7ffff7bd12ad at 0x00000298: .text ALLOC LOAD READONLY CODE HAS_CONTENTS
    [...]
```

### Nice to Know

The lazy binding feature of the loader can be disabled by using the `-z now` linker option.
In that case, function addresses will be resolved at load time, and the `.got.plt` entries will be populated from the start with the actual addresses.
The downside of using `-z now` is the time overhead during program startup.
The benefit is the ability to now mark the `.got.plt` section as read-only at program startup, after the function address resolution.
This approach, called *Relocation Read-Only* (RELRO), adds [security benefits](https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro).
When using the `-z relro` linker option, but without the `-z now` option, only the `.got` section is marked as read-only; this is called *partial RELRO*.
When using the `-z relro` **and** the `-z now` linker options, both the `.got` and `.got.plt` sections are marked as read-only; this is called *full RELRO*.

## Summary

GOT (*Global Offset Table*) is used by ELF programs, in conjunction with PLT (*Procedure Linkage Table*), to store symbol addresses that are unknown until load time.
We used a simple dynamic/shared library and a simple program using that library to investigate the use of GOT.
GOT is implemented as two sections in an ELF program:
1. `.got` stores addresses of global variables
1. `.got.plt` stores addresses of functions; it is used in conjunction with the `.plt` section, that stores code to access `.got.plt` entries

GOT entries are uninitialized in the executable file created by the linker.
Entries are populated at load time.
The loader loads all required files (such as executables and shared libraries), resolves symbols and populates entries in the `.got` and `.got.plt` sections.

We used `nm`, `objdump` and `readelf` for static analysis and GDB for dynamic analysis:
* We found the static (in executable) and dynamic (in memory) addresses of symbols.
* We identified GOT entries for global variables and functions.
* We checked the contents of the GOT entries.
* We saw the use of GOT by disassembling the program code and the `.plt` section.
With this, we saw how and when GOT entries are populated and used by programs.

While GOT and PLT are particular to ELF programs, the feature itself is used by other executable formats.
Microsoft Windows PE (*Portable Executable*) programs use [*Import Address Table* (IAT)](http://sandsprite.com/CodeStuff/Understanding_imports.html).
Apple macOS/iOS Mach-O programs [use](https://www.apriorit.com/dev-blog/225-dynamic-linking-mach-o) the `__TEXT.__stubs`, `__TEXT.__stub_helpers` and `__DATA.__la_symbol_ptr` sections.
