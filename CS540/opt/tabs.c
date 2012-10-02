#include <stdio.h>
#include "counter.h"

#define MAX 1000

inline int absval(int val)
{
     return (val < 0) ? -val : val;
}

int a[MAX];

int main(int argc, char * argv[])
{
   int i,j,n,gen,repeat,t;
   double cycles;

   printf("Enter count: ");
   scanf("%d",&n);
  
   printf("Enter (0=constant, 1 = random:");
   scanf("%d",&gen);

   printf("Enter repeat count:");
   scanf("%d",&repeat);

   switch (gen) {
   case 0 :  
            for (i=0;i<n;i++)
            {
              a[i] = 1;
            }
            break;
   case 1 :  
            for (i=0;i<n;i+=repeat)
            {
              t = (-1) * (lrand48() % 2) ;
              for (j=0;j<repeat;j++)
                 a[i+j] = t;
            }
            for (;i<n;i++)
              a[i] = t;
            break;
  default : printf("illegal case\n");  exit(1);
  }

   start_counter();
   for (i=0;i<n;i++)
   {
     a[i] = absval(a[i]);
   }
   cycles = get_counter();
  
   printf("cycles for absval = %.0f\n",cycles);

}
