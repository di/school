#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <papi.h> 
#include <unistd.h>

double get_seconds() { /* routine to read time */
        clock_t t;
    t = clock();
        return (double) t/ (double) CLOCKS_PER_SEC;
}

void ehandler(char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}

main(int argc, char *argv[])
{
float *a,*b,*c;
int n;
int NB;
int i,j;
int x;
//double t0,t1;
struct timeval t0,t1;
long mtime, seconds, useconds;

// Using PAPI - from countloop.c
if (PAPI_VER_CURRENT !=
    PAPI_library_init(PAPI_VER_CURRENT))
    ehandler("PAPI_library_init error.");

const size_t EVENT_MAX = PAPI_num_counters();
// Suppressing output
//    printf("# Max counters = %zd\n", EVENT_MAX);

if (PAPI_OK != PAPI_query_event(PAPI_TOT_INS))
    ehandler("Cannot count PAPI_TOT_INS.");

if (PAPI_OK != PAPI_query_event(PAPI_FP_OPS))
    ehandler("Cannot count PAPI_FP_OPS.");

if (PAPI_OK != PAPI_query_event(PAPI_L1_DCM))
    ehandler("Cannot count PAPI_L1_DCM.");

size_t EVENT_COUNT = 3;
int events[] = { PAPI_TOT_INS, PAPI_FP_OPS, PAPI_L1_DCM };
long long values[EVENT_COUNT];

// Take size from args, not prompt
// printf("Enter n:  ");  scanf("%d",&n);  printf("n = %d\n",n);
n = atoi(argv[1]);

a = vector(1,n*n);
for (i=0;i<n;i++) 
    for (j=1;j<n;j++) 
        a[n*i+j] = i+j;

b = vector(1,n*n);

for (i=0;i<n;i++) 
    for (j=1;j<n;j++) 
        b[n*i+j] = i-j;

//t0 = get_seconds();
gettimeofday(&t0, NULL);
// Start PAPI
PAPI_start_counters(events, EVENT_COUNT);

if (PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
    ehandler("Problem reading counters.");
for (x=0;x<1000;x++){
    c = vector_prod(a,b,n);
}
if (PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
    ehandler("Problem reading counters.");

//t1 = get_seconds();
gettimeofday(&t1, NULL);
seconds = t1.tv_sec - t0.tv_sec;
useconds = t1.tv_usec - t0.tv_usec;
mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
//printf("Time for matrix_prod = %f sec\n",t1-t0);
printf("%d\t%lld\t%lld\t%lld\t%ld\n", n, values[0], values[1],
    values[2], mtime);

}
