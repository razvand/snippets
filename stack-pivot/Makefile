CFLAGS = -Wall -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=4 -fno-PIC
LDFLAGS = -no-pie

.PHONY: all clean

all: vuln

vuln: vuln.o

vuln.o: vuln.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f vuln.o
	-rm -f vuln
	-rm -f core
	-rm -f peda-session*
