#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

#define DEBUG 0
#define MAX 100000


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
   int i,n,j,m;
   long long before, after, before1, after1;

   if (PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT))
      ehandler("PAPI_library_init error.");

   printf("Enter max m: ");
   scanf("%d",&m);

   for (j=0; j < m; j+=100) {
   n = j;
   for (i=0; i < n; i++) {
      a[i] = i;
      b[i] = n - i;
   } 

   vsum1(n);
   before = PAPI_get_real_cyc();
   vsum1(n);
   after = PAPI_get_real_cyc();
  
   //printf("cycles for vsum1 = %lld\n",after-before);

   before1 = PAPI_get_real_cyc();
   vsum2(n);
   after1 = PAPI_get_real_cyc();
  
   //printf("cycles for vsum2 = %lld\n",after1-before1);

   printf("%d\t%lld\t%lld\n", j, after-before, after1-before1);
   
   if (DEBUG) {
     for (i=0;i<n;i++)
       printf("c[%d] = %d\n",i,c[i]);
   }
   }
}
