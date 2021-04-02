CPPFLAGS = -DTEST
#CPPFLAGS = -DTEST -DCUSTOM_GCOV
CFLAGS = -Wall -m32 -fprofile-arcs -ftest-coverage
LDFLAGS = -m32 -fprofile-arcs -ftest-coverage

.PHONY: all clean

all: idea sum_test

idea: idea.o

idea.o: idea.c idea.h

sum_test: sum_test.o

sum_test.o: sum_test.c

clean:
	-rm -f idea idea.o
	-rm -f idea.gcno idea.gcda idea.c.gcov
	-rm -f sum_test sum_test.o
	-rm -f sum_test.gcno sum_test.gcda sum_test.c.gcov
	-rm -f *~
