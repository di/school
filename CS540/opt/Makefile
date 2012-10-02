# Makefile for example programs
#	where to find PAPI
#PAPI = /site/local/papi_32-3.7.0
PAPI = /site/local/papi_64-4.1.4
LIB_DIR		= $(PAPI)/lib

#	where to find include files
INCLUDE_DIR	= $(PAPI)/include

CC	= gcc
OPT	= -O3
CFLAGS	= -I$(INCLUDE_DIR)
LDFLAGS	= -L$(LIB_DIR) -static -lpapi -lm


default: timevsum

all: timevsum countvsum 

clean:
	rm -f *.o *.exe a.out timevsum

timevsum: timevsum.c
	$(CC) $(CFLAGS) -o timevsum timevsum.c $(LDFLAGS)

countvsum: countvsum.c
	$(CC) $(CFLAGS) -o countvsum countvsum.c $(LDFLAGS)
