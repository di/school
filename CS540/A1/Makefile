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

default: matrix_block 

all: matrix matrix_Os matrix_O1 matrix_O2 matrix_O3 matrix_ikj matrix_kij matrix_kji matrix_jik matrix_jki matrix_block 

clean:
	rm -f *.o *.exe a.out matrix matrix_Os matrix_O1 matrix_O2 matrix_O3 matrix_ikj matrix_kij matrix_kji matrix_jik matrix_jki matrix_block

matrix: matrix.c timemm.c
	$(CC) matrix.c timemm.c $(CFLAGS) -o matrix $(LDFLAGS)

matrix_O1: matrix.c timemm.c
	$(CC) -O1 matrix.c timemm.c $(CFLAGS) -o matrix_O1 $(LDFLAGS)

matrix_O2: matrix.c timemm.c
	$(CC) -O2 matrix.c timemm.c $(CFLAGS) -o matrix_O2 $(LDFLAGS)

matrix_O3: matrix.c timemm.c
	$(CC) -O3 matrix.c timemm.c $(CFLAGS) -o matrix_O3 $(LDFLAGS)

matrix_Os: matrix.c timemm.c
	$(CC) -Os matrix.c timemm.c $(CFLAGS) -o matrix_Os $(LDFLAGS)

matrix_ikj: matrix_ikj.c timemm.c
	$(CC) matrix_ikj.c timemm.c $(CFLAGS) -o matrix_ikj $(LDFLAGS)

matrix_kij: matrix_kij.c timemm.c
	$(CC) matrix_kij.c timemm.c $(CFLAGS) -o matrix_kij $(LDFLAGS)

matrix_kji: matrix_kji.c timemm.c
	$(CC) matrix_kji.c timemm.c $(CFLAGS) -o matrix_kji $(LDFLAGS)

matrix_jik: matrix_jik.c timemm.c
	$(CC) matrix_jik.c timemm.c $(CFLAGS) -o matrix_jik $(LDFLAGS)

matrix_jki: matrix_jki.c timemm.c
	$(CC) matrix_jki.c timemm.c $(CFLAGS) -o matrix_jki $(LDFLAGS)

matrix_block: matrix.c block.c timeblockmm.c
	$(CC) matrix.c block.c timeblockmm.c $(CFLAGS) -o matrix_block $(LDFLAGS) 
