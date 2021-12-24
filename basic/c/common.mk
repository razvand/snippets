CFLAGS ?= -Wall
OBJS = $(SRCS:.c=.o)
BINS = $(OBJS:.o=)

.PHONY: all clean

all: $(BINS)

$(BINS): %: %.o

$(OBJS): %.o: %.c

clean:
	-rm -f *~
	-rm -f $(BINS) $(OBJS)
