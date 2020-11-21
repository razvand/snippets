# gcov Demo

[gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) is a tool for coverage testing, i.e. showing whether a given line in a program was called and how many times.
It's used to profile the program and let you know what are the hot areas in the program that could be made more efficient.

This is a demo of using gcov on an implementation of the [IDEA encryption algorithm](https://en.wikipedia.org/wiki/International_Data_Encryption_Algorithm).
The original source code is [here](https://github.com/bgreenlee/PassKeeper).
Minor updates were added to fix compiling errors and warnings. A `Makefile` was added.

To test gcov, run `make` to build the program into the `idea` executable file:

```
$ make
cc -Wall -m32 -fprofile-arcs -ftest-coverage -DTEST  -c -o idea.o idea.c
cc -m32 -fprofile-arcs -ftest-coverage  idea.o   -o idea
$ ls
idea  idea.c  idea.gcno  idea.h  idea.o  Makefile  README.md
```

An `idea.gcno` file is also generated (gcov notes).
As told in the [official documentation](https://gcc.gnu.org/onlinedocs/gcc/Gcov-Data-Files.html), the `.gcno file` is a platform-independent static representation of the program, i.e. the control flow graph: basic blocks and arcs between basic blocks.

Running the program provides the runtime information in the `idea.gcda` file:

```
$ ./idea
[...]
$ ls
idea  idea.c  idea.gcda  idea.gcno  idea.h  idea.o  Makefile  README.md
```

The `.gcda` file is a platform-independent representation of the runtime profiling information, i.e. arc transition counts between basic blocks.

gcov then provides a human-readable view of the profiling information based on the two files (`.gcno` and `.gcda`), resulting in a `.gcov` file.

```
razvan@yggdrasil:~/projects/snippets.git/gcov$ gcov idea.c
File 'idea.c'
Lines executed:97.32% of 149
Creating 'idea.c.gcov'

razvan@yggdrasil:~/projects/snippets.git/gcov$ ls
idea  idea.c  idea.c.gcov  idea.gcda  idea.gcno  idea.h  idea.o  Makefile  README.md
razvan@yggdrasil:~/projects/snippets.git/gcov$ less idea.c.gcov
```

The `idea.c.gcov` file lists the program source code together with the number of times each line was called.

Additional information is provided by using certain options to the `gcov` command:

```
razvan@yggdrasil:~/projects/snippets.git/gcov$ gcov -acf idea.c
Function 'main'
Lines executed:96.00% of 50

Function 'ideaCipher'
Lines executed:100.00% of 38

Function 'ideaInvertKey'
Lines executed:100.00% of 33

Function 'ideaExpandKey'
Lines executed:100.00% of 10

Function 'mulInv'
Lines executed:88.89% of 18

File 'idea.c'
Lines executed:97.32% of 149
Creating 'idea.c.gcov'
```

[gcovr](https://github.com/gcovr/gcovr) can be used to present coverage information in different formats.

## Custom Coverage

It may be the case that coverage / profile information for only certain functions is of interest.
gcov offers an API to reset and dump the coverage information (as told in the [official documentation](https://gcc.gnu.org/onlinedocs/gcc/Gcov-and-Optimization.html#Gcov-and-Optimization), thereby restricting colected information to the program sequence between `__gcov_reset()` and `__gcov_dump()` function calls.

Update the `CPPFLAGS` variabile in the `Makefile` to use the `-DCUSTOM_GCOV` flag, i.e. the first two lines of the `Makefile` should be:

```
#CPPFLAGS = -DTEST
CPPFLAGS = -DTEST -DCUSTOM_GCOV
```

The `CUSTOM_GCOV` flag will restrict the coverage information to the following program sequence:

```
   340	#ifdef CUSTOM_GCOV
   341		__gcov_reset();
   342	#endif
   343		for (l = 0; l < BLOCKS; l++)
   344			ideaCipher(YY, YY, EK);	/* repeated encryption */
   345	#ifdef CUSTOM_GCOV
   346		__gcov_dump();
   347	#endif
```

Now rebuild and rerun the program:
```
$ make clean
$ make
$ ./idea
```

The coverage information will now be limited to the calls of the `ideaCipher()` function in the loop in lines `343` and `344`.

## Internals

The `.gcda` file is by default created at runtime in the current working directory.
This can be changed by using the `-fprofile-dir` command line option to `gcc`.

The `.gcno` file is created by the compiler when using the `-ftest-coverage` command line option to `gcc`.
It is technically not required for coverage information, as is the case with the `.gcda` file; the `.gcno` file is used as a support file by `gcov` to provide a human-readable view of the profiling information.
PGO (*Profile Guided Optimization*) uses only `.gcda` files.

The format of the `.gcda` and `.gcno` files is documented in the [gcov-io.h file](http://src.gnu-darwin.org/src/contrib/gcc/gcov-io.h.html) and parsed and used in the [gcov-io.c file](http://src.gnu-darwin.org/src/contrib/gcc/gcov-io.c.html).
