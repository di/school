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

default: code2

all: code0 code1 code2 code3 code4

clean:
	rm -f *.o *.exe a.out code0 code1 code2 code3 code4 

code0: code0.c timemmm.c
	$(CC) code0.c timemmm.c $(CFLAGS) -o code0 $(LDFLAGS)

code1: code1.c timemmm.c
	$(CC) code1.c timemmm.c $(CFLAGS) -o code1 $(LDFLAGS)

code2: code2.c timemmm.c
	$(CC) code2.c timemmm.c $(CFLAGS) -o code2 $(LDFLAGS)

code3: code3.c timemmm.c
	$(CC) code3.c timemmm.c $(CFLAGS) -o code3 $(LDFLAGS)

code4: code4.c timemmm.c
	$(CC) code4.c timemmm.c $(CFLAGS) -o code4 $(LDFLAGS)
