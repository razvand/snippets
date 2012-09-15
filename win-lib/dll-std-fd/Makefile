CC = cl
L = link
CFLAGS = /nologo /W3

all: main.exe

main.exe: main.obj external.obj test.lib
	$(L) /nologo /out:$@ $**

test.lib: test.dll

test.dll: internal.obj
	$(L) /nologo /dll /out:$@ /implib:test.lib $**

main.obj: main.c
	$(CC) $(CFLAGS) /c $**

internal.obj: internal.c
	$(CC) $(CFLAGS) /c $**

external.obj: external.c
	$(CC) $(CFLAGS) /c $**

clean:
	del /Q /F *.obj *.lib *.dll *.exe  *.exp
