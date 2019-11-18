CFLAGS = -Wall -g -fno-PIC -Wno-unused-function -fno-stack-protector
LDFLAGS = -no-pie

.PHONY: all clean

all: vuln

vuln: vuln.o

vuln.o: vuln.c

clean:
	-rm -f vuln vuln.o
	-rm -f *~
	-rm -f peda-session-* core
