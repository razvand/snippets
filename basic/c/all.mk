CFLAGS = -Wall -fstack-protector -fPIC
CFLAGS_32 = -Wall -m32 -fstack-protector -fPIC
CFLAGS_NOPIC = -Wall -fstack-protector -fno-PIC
CFLAGS_32_NOPIC = -Wall -m32 -fstack-protector -fno-PIC
CFLAGS_NOSSP = -Wall -fno-stack-protector
CFLAGS_32_NOSSP = -Wall -m32 -fno-stack-protector
CFLAGS_NOSSP_NOPIC = -Wall -fno-stack-protector -fno-PIC
CFLAGS_32_NOSSP_NOPIC = -Wall -m32 -fno-stack-protector -fno-PIC
LDFLAGS = -pie -dynamic
LDFLAGS_32 = -m32 -pie -dynamic
LDFLAGS_NOPIE = -no-pie -dynamic
LDFLAGS_32_NOPIE = -m32 -no-pie -dynamic
LDFLAGS_STATIC = -no-pie -static
LDFLAGS_32_STATIC = -m32 -no-pie -static

OBJS = $(SRCS:.c=.o) \
	$(SRCS:.c=_32.o) \
	$(SRCS:.c=_nopie.o) \
	$(SRCS:.c=_32_nopie.o) \
	$(SRCS:.c=_nossp.o) \
	$(SRCS:.c=_32_nossp.o) \
	$(SRCS:.c=_nossp_nopie.o) \
	$(SRCS:.c=_32_nossp_nopie.o) \
	$(SRCS:.c=_static.o) \
	$(SRCS:.c=_32_static.o) \
	$(SRCS:.c=_nossp_static.o) \
	$(SRCS:.c=_32_nossp_static.o) \

BINS = $(OBJS:.o=)


.PHONY: all clean

all: $(BINS)

%_32_nossp_static: %_32_nossp_static.o
	$(CC) $(LDFLAGS_32_STATIC) -o $@ $^

%_32_nossp_static.o: %.c
	$(CC) $(CFLAGS_32_NOSSP_NOPIC) -c -o $@ $<

%_nossp_static: %_nossp_static.o
	$(CC) $(LDFLAGS_STATIC) -o $@ $^

%_nossp_static.o: %.c
	$(CC) $(CFLAGS_NOSSP_NOPIC) -c -o $@ $<

%_32_static: %_32_static.o
	$(CC) $(LDFLAGS_32_STATIC) -o $@ $^

%_32_static.o: %.c
	$(CC) $(CFLAGS_32_NOPIC) -c -o $@ $<

%_static: %_static.o
	$(CC) $(LDFLAGS_STATIC) -o $@ $^

%_static.o: %.c
	$(CC) $(CFLAGS_NOPIC) -c -o $@ $<

%_32_nossp_nopie: %_32_nossp_nopie.o
	$(CC) $(LDFLAGS_32_NOPIE) -o $@ $^

%_32_nossp_nopie.o: %.c
	$(CC) $(CFLAGS_32_NOSSP_NOPIC) -c -o $@ $<

%_nossp_nopie: %_nossp_nopie.o
	$(CC) $(LDFLAGS_NOPIE) -o $@ $^

%_nossp_nopie.o: %.c
	$(CC) $(CFLAGS_NOSSP_NOPIC) -c -o $@ $<

%_32_nopie: %_32_nopie.o
	$(CC) $(LDFLAGS_32_NOPIE) -o $@ $^

%_32_nopie.o: %.c
	$(CC) $(CFLAGS_32_NOPIC) -c -o $@ $<

%_nopie: %_nopie.o
	$(CC) $(LDFLAGS_NOPIE) -o $@ $^

%_nopie.o: %.c
	$(CC) $(CFLAGS_NOPIC) -c -o $@ $<

%_32_nossp: %_32_nossp.o
	$(CC) $(LDFLAGS_32) -o $@ $^

%_32_nossp.o: %.c
	$(CC) $(CFLAGS_32_NOSSP) -c -o $@ $<

%_nossp: %_nossp.o
	$(CC) $(LDFLAGS) -o $@ $^

%_nossp.o: %.c
	$(CC) $(CFLAGS_NOSSP) -c -o $@ $<

%_32: %_32.o
	$(CC) $(LDFLAGS_32) -o $@ $^

%_32.o: %.c
	$(CC) $(CFLAGS_32) -c -o $@ $<

$(SRCS:.c=): %: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f $(BINS)
	-rm -f $(OBJS)
