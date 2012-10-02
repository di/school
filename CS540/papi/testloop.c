#define MAXVSIZE 1000
#include <stdio.h>
#include <stdlib.h>

void loop(double c[], double a[], double b[], int n) 
{
     int i;

     for (i=0;i<n;i++)
       c[i] = a[i] + b[i];
}

int main(int argc, char *argv[]) {

     double a[MAXVSIZE], b[MAXVSIZE], c[MAXVSIZE];
     int i,n;


     printf("Enter vector size:  ");
     scanf("%d",&n);

     for (i=0;i<n;i++) {
       a[i] = i;
       b[i] = n-i;
     }

    loop(c,a,b,n);

    for (i=0;i<n;i++)
      printf("c[%d] = %g\n",i,c[i]);
}
