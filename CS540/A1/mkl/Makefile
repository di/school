PAPI = /site/local/papi_64-4.1.4
LIB_DIR = $(PAPI)/lib
INCLUDE_DIR = $(PAPI)/include
PCFLAGS = -I$(INCLUDE_DIR)
PLDFLAGS = -L$(LIB_DIR) -static -lpapi -lm

MKLROOT = /site/local/intel-math-kernel-library-10.3.2.137/mkl
CFLAGS = -m64 -g -I$(MKLROOT)/include
CXXFLAGS = -O3
LDFLAGS = -L$(MKLROOT)/lib/intel64 -Wl,--start-group -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -Wl,--end-group -lm -lpthread
mkl: matrix.o mkl.o timemklmm.o
	g++ -g $(CXXFLAGS) matrix.o mkl.o $(CFLAGS) $(LDFLAGS) timemklmm.o $(PCFLAGS) $(PLDFLAGS) -o mkl 
matrix.o: matrix.c
	gcc -c matrix.c 

#	export LD_LIBRARY_PATH=:/site/local/intel-math-kernel-library-10.3.2.137/mkl/lib/intel64:/site/local/cilk/lib:/usr/local/cuda/lib64:/usr/local/cuda/computeprof/bin
mkl.o: mkl.cc
	g++ $(CFLAGS) $(LDFLAGS) -c mkl.cc
timemklmm.o: timemklmm.c
	gcc $(CFLAGS) $(LDFLAGS) $(PCFLAGS) $(PLDFLAGS) -c timemklmm.c

clean:
	rm -f *.o *.exe a.out mkl 
