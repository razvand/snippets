#
# tests Makefile
#

CFLAGS = -Wall -g
LDLIBS = -lpthread

.PHONY: all clean

all: thread-vs-process

thread-vs-process: thread-vs-process.o

clean:
	-rm -f thread-vs-process *~ *.o
