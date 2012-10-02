PAPI = /site/local/papi_64-4.1.4
LIB_DIR = $(PAPI)/lib
INCLUDE_DIR = $(PAPI)/include
PCFLAGS = -I$(INCLUDE_DIR)
PLDFLAGS = -L$(LIB_DIR) -static -lpapi -lm

ATLASROOT=/usr/include/atlas
ATLAS_DIR=/usr/lib/atlas-base
CFLAGS= -g -I$(ATLASROOT) -O3
LDFLAGS=-L$(ATLAS_DIR) -static -llapack_atlas -lcblas -latlas

atlas: matrix.o atlas.o timeatlasmm.o
	g++ -g matrix.o atlas.o $(CFLAGS) $(LDFLAGS) timeatlasmm.o $(PCFLAGS) $(PLDFLAGS) -o atlas 
matrix.o: matrix.c
	gcc -c matrix.c 

atlas.o: atlas.cc
	g++ $(CFLAGS) $(LDFLAGS) -c atlas.cc
timeatlasmm.o: timeatlasmm.c
	gcc $(CFLAGS) $(LDFLAGS) $(PCFLAGS) $(PLDFLAGS) -c timeatlasmm.c

clean:
	rm -f *.o *.exe a.out atlas
