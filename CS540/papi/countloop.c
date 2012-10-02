#define MAXVSIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <math.h>

void loop(double c[], double a[], double b[], int n) 
{
     int i;

     for (i=0;i<n;i++)
       c[i] = a[i] + b[i];
}

void ehandler(char *s)
{
     fprintf(stderr, "%s\n", s);
     exit(1);
}


int main(int argc, char *argv[]) {

     double a[MAXVSIZE], b[MAXVSIZE], c[MAXVSIZE];
     int i,n;
     long long before, after;


     if (PAPI_VER_CURRENT != 
		PAPI_library_init(PAPI_VER_CURRENT))
	ehandler("PAPI_library_init error.");

     const size_t EVENT_MAX = PAPI_num_counters();
        printf("# Max counters = %zd\n", EVENT_MAX);

     if (PAPI_OK != PAPI_query_event(PAPI_TOT_INS))
	        ehandler("Cannot count PAPI_TOT_INS.");

     if (PAPI_OK != PAPI_query_event(PAPI_FP_OPS))
	        ehandler("Cannot count PAPI_FP_OPS.");

     size_t EVENT_COUNT = 2;
     int events[] = { PAPI_TOT_INS, PAPI_FP_OPS };
     long long values[EVENT_COUNT];


     printf("Enter vector size:  ");
     scanf("%d",&n);

     for (i=0;i<n;i++) {
       a[i] = i;
       b[i] = n-i;
     }

     PAPI_start_counters(events, EVENT_COUNT);

     if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
               ehandler("Problem reading counters.");

     loop(c,a,b,n);

     if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
               ehandler("Problem reading counters.");

     printf("Number of instructions = %lld\n",values[0]);
     printf("Number of fp operations = %lld\n",values[1]);
     return 0;

}
