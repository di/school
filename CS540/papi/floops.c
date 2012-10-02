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
     float rtime, ptime, mflops;
     long long flpops; 


     printf("Enter vector size:  ");
     scanf("%d",&n);

     for (i=0;i<n;i++) {
       a[i] = i;
       b[i] = n-i;
     }

     PAPI_flops(&rtime, &ptime, &flpops, &mflops);
     loop(c,a,b,n);
     PAPI_flops(&rtime, &ptime, &flpops, &mflops);


     printf("Number of floatinig point operations = %lld\n",flpops);
     printf("mflops = %f\n",mflops);
     return 0;

}
