CFLAGS = -Wall
LDLIBS = -lpthread

.PHONY: all clean

all: __thread __thread-static tsd tsd-static indirect_modify

__thread-static: __thread.o
	$(CC) $(LDLFAGS) -static -o $@ $^ $(LDLIBS)

__thread: __thread.o

__thread.o: __thread.c

tsd-static: tsd.o
	$(CC) $(LDLFAGS) -static -o $@ $^ $(LDLIBS)

tsd: tsd.o

tsd.o: tsd.c

indirect_modify: indirect_modify.o

indirect_modify.o: indirect_modify.c
	$(CC) $(CFLAGS) -fstack-protector-strong -c -o $@ $<

clean:
	-rm -f __thread.o __thread __thread-static
	-rm -f tsd.o tsd tsd-static
	-rm -f indirect_modify.o indirect_modify
	-rm -f *~
