# Makefile for example programs
#	where to find PAPI
#PAPI = /site/local/papi_64-3.7.0
PAPI = /site/local/papi_64-4.1.4
LIB_DIR		= $(PAPI)/lib

#	where to find include files
INCLUDE_DIR	= $(PAPI)/include

CC	= gcc
OPT	= -Os
CFLAGS	= -I$(INCLUDE_DIR)
LDFLAGS	= -L$(LIB_DIR) -static -lpapi -lm


default: timeloop

all: timeloop countloop floops timeloop_opt

clean:
	rm -f *.o *.exe a.out timeloop countloop timeloop_opt

timeloop: timeloop.c
	$(CC) $(CFLAGS) -o timeloop timeloop.c $(LDFLAGS)

timeloop_opt: timeloop.c
	$(CC) $(CFLAGS) $(OPT) -o timeloop_opt timeloop.c $(LDFLAGS)

countloop: countloop.c
	$(CC) $(CFLAGS) -o countloop countloop.c $(LDFLAGS)

floops: floops.c
	$(CC) $(CFLAGS) -o floops floops.c $(LDFLAGS)
