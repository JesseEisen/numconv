CC  ?= gcc

BINS = nc

RM = rm -f

SRC  = $(wildcard src/*.c)
DEPS = $(wildcard deps/*/*.c)
OBJS = $(DEPS:.c=.o)

CFLAGS = -Ideps -Wall -g

all: $(BINS)

$(BINS): $(SRC) $(OBJS)
	$(CC) $(CFLAGS) -o $@ src/$(@).c $(OBJS) 

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	$(foreach c, $(BINS), $(RM) $(c);)
	$(RM) $(OBJS)

.PHONY: all clean
