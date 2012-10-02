#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

#define MAX 1000
#define DEBUG 0


int a[MAX], b[MAX], c[MAX];

void ehandler(char *s)
{
     fprintf(stderr, "%s\n", s);
     exit(1);
}

void vsum1(int n)
{
     int i;

     for (i = 0; i < n; i++)
       c[i] = a[i] + b[i];
}

void vsum2(int n)
{
     int i;

     for (i = 0; i < n; i+=2) {
       c[i] = a[i] + b[i];
       c[i+1] = a[i+1] + b[i+1];
     }
}

int main(int argc, char * argv[])
{
   int i,n,m,j;
   long long before, after, before1, after1;

   if (PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT))
      ehandler("PAPI_library_init error.");

    const size_t EVENT_MAX = PAPI_num_counters();
        printf("# Max counters = %zd\n", EVENT_MAX);

     if (PAPI_OK != PAPI_query_event(PAPI_TOT_INS))
	        ehandler("Cannot count PAPI_TOT_INS.");

     size_t EVENT_COUNT = 1;
     int events[] = { PAPI_TOT_INS };
     long long values[EVENT_COUNT];


   printf("Enter max m: ");
   scanf("%d",&m);

   for (j=0; j < m; j+=100) {
   n = j;
   for (i=0; i < n; i++) {
      a[i] = i;
      b[i] = n - i;
   } 

   vsum1(n);

   PAPI_start_counters(events, EVENT_COUNT);

   if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
             ehandler("Problem reading counters.");
   vsum1(n);

   if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
             ehandler("Problem reading counters.");

   printf("Number of instructions (vsum1) = %lld\n",values[0]);
  

   PAPI_start_counters(events, EVENT_COUNT);

   if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
             ehandler("Problem reading counters.");
   vsum2(n);
  
   if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
             ehandler("Problem reading counters.");

   printf("Number of instructions (vsum2) = %lld\n",values[0]);
  

   if (DEBUG) {
     for (i=0;i<n;i++)
       printf("c[%d] = %d\n",i,c[i]);
   }
   }
}
