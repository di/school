#include <stdio.h>
#include <stdlib.h>
#include "counter.h"

#define MAX 1000
#define DEBUG 0


int a[MAX], b[MAX], c[MAX];

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
   int i,n;
   double cycles;

   printf("Enter n: ");
   scanf("%d",&n);

   for (i=0; i < n; i++) {
      a[i] = i;
      b[i] = n - i;
   } 

   vsum1(n);
   start_counter();
   vsum1(n);
   cycles = get_counter();
  
   printf("cycles for vsum1 = %.0f\n",cycles);

   start_counter();
   vsum2(n);
   cycles = get_counter();
  
   printf("cycles for vsum2 = %.0f\n",cycles);
   if (DEBUG) {
     for (i=0;i<n;i++)
       printf("c[%d] = %d\n",i,c[i]);
   }
}
