CFLAGS=-Wall -g

all: mmap file

mmap: mmap.o

dual_mapping: dual_mapping.o

clean:
	rm -f *.o *~ mmap

file:
	truncate -s 100M file
