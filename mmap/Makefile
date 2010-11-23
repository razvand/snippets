CFLAGS = -Wall -g

all: mmap file dual-mapping

mmap: mmap.o

dual-mapping: dual-mapping.o

clean:
	rm -f *.o *~ mmap dual-mapping file

file:
	truncate -s 100M file
