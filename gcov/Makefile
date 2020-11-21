CPPFLAGS = -DTEST
#CPPFLAGS = -DTEST -DCUSTOM_GCOV
CFLAGS = -Wall -m32 -fprofile-arcs -ftest-coverage
LDFLAGS = -m32 -fprofile-arcs -ftest-coverage

.PHONY: all clean

all: idea

idea: idea.o

idea.o: idea.c idea.h

clean:
	-rm -f idea idea.o
	-rm -f idea.gcno idea.gcda idea.c.gcov
	-rm -f *~
