# tools
CC := gcc
RM := rm -f

# flags
CFLAGS := -ggdb
LDFLAGS :=
LDLIBS :=

# sources
sources := target1.c target2.c target3.c target4.c target5.c \
           target6.c target7.c target-ec tmalloc.c
targets := target1 target2 target3 target4 target5 target6 target7 target-ec

# gmake magic
.PHONY: default all clean

#targets
default: all
all: $(targets)

clean:
	$(RM) $(targets) $(sources:.c=.o)

# special make process for eip target
target3:    CFLAGS += -fomit-frame-pointer -O2

#dependencies
target5: tmalloc.o
tmalloc.o target5.o: tmalloc.h
