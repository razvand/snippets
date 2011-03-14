CFLAGS = /I. /DDEBUG /W3
#CFLAGS = /I. /W3

all: test-debug.exe

test-debug.exe: test-debug.obj
	$(CC) /nologo /Fe$@ $**

test-debug.obj: test-debug.c debug.h
	$(CC) /nologo /c $(CFLAGS) /Fo$@ test-debug.c

clean:
	del /Q /S *.obj test-debug.exe
