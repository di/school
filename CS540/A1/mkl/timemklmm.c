#include "matrix.h"
//#include "mkl_cblas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <papi.h>
#include <unistd.h>
#include <math.h>

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
int n,n1,n2;
int i,j;
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

//printf("Enter n1:  ");  scanf("%d",&n1);  printf("n1 = %d\n",n1);
//printf("Enter n2:  ");  scanf("%d",&n2);  printf("n2 = %d\n",n2);

// To conform to the other matrix functions
//n1 = floor(sqrt(n));
//n2 = n1;
//n = n1*n2;
//printf("n = %d X %d = %d\n",n1,n2,n);
//a = matrix(1,n,1,n);
a = ((float *)malloc(n*n*sizeof(float)));
//for (i=1;i<=n;i++) 
for (i=1;i<=n*n;i++) 
    a[i] = i;
    //for (j=1;j<=n;j++) 
        //a[i][j] = i+j;

//b = matrix(1,n,1,n);
b = ((float *)malloc(n*n*sizeof(float)));
//for (i=1;i<=n;i++) 
for (i=1;i<=n*n;i++) 
    b[i] = i;
    //for (j=1;j<=n;j++) 
        //b[i][j] = i-j;

//#ifdef PRINT
//print_matrix(a,1,n,1,n);
//printf("\n"); */
//print_matrix(b,1,n,1,n);
//printf("\n"); */
//#endif

//t0 = get_seconds();
//c = matrix_prod(n,n,n,n,a,b);
//t1 = get_seconds();
//printf("Time for matrix_prod = %f sec\n",t1-t0);

//t0 = get_seconds();
gettimeofday(&t0, NULL);
// Start PAPI
PAPI_start_counters(events, EVENT_COUNT);

if (PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
    ehandler("Problem reading counters.");

//c = block_prod(n1,n1,n1,n2,n2,n2,a,b);
c = mkl_sgemm(a, b, n);

if (PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
    ehandler("Problem reading counters.");

//t1 = get_seconds();
//printf("Time for block_prod = %f sec\n",t1-t0);
gettimeofday(&t1, NULL);
seconds = t1.tv_sec - t0.tv_sec;
useconds = t1.tv_usec - t0.tv_usec;
mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
//printf("Time for matrix_prod = %f sec\n",t1-t0);
printf("%d\t%lld\t%lld\t%lld\t%ld\n", n, values[0], values[1],
    values[2], mtime);
}

//#ifdef PRINT
//print_matrix(c,1,n,1,n);
//printf("\n");
//#endif
//}
