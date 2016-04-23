CC = /Applications/Xcode.app/Contents/Developer/usr/bin/gcc
SDK = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
ARCH = armv7

.PHONY: all clean

all: hello

hello: hello.c
	$(CC) -arch $(ARCH) -isysroot $(SDK) $^ -o $@

clean:
	-rm -f *.o
	-rm -f hello
