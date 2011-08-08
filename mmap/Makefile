CFLAGS = -Wall -g

all: mmap file dual-mapping mmap-ftruncate

mmap: mmap.o

dual-mapping: dual-mapping.o

file:
	truncate -s 100M file

clean:
	rm -f *.o *~ mmap dual-mapping file mmap-ftruncate

