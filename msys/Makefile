CC = /c/MinGW/bin/gcc.exe
CFLAGS = -Wall -g
GCC_PATH = /c/MinGW/bin

all: hello.exe

hello.exe: hello.c
	PATH=$(GCC_PATH):$$PATH $(CC) $(CFLAGS) -o $@ $^
	
clean:
	-rm -f hello.exe *~
