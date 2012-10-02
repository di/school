#include "matrix.h"
#include <stdio.h>
#include <time.h>

double get_seconds() { /* routine to read time */
        clock_t t;
    t = clock();
        return (double) t/ (double) CLOCKS_PER_SEC;
}

main()
{
float **a,**b,**c;
int n,n1,n2;
int i,j;
double t0,t1;

printf("Enter n1:  ");  scanf("%d",&n1);  printf("n1 = %d\n",n1);
printf("Enter n2:  ");  scanf("%d",&n2);  printf("n2 = %d\n",n2);
n = n1*n2;
printf("n = %d X %d = %d\n",n1,n2,n);
a = matrix(1,n,1,n);
for (i=1;i<=n;i++) 
    for (j=1;j<=n;j++) 
        a[i][j] = i+j;

b = matrix(1,n,1,n);
for (i=1;i<=n;i++) 
    for (j=1;j<=n;j++) 
        b[i][j] = i-j;

#ifdef PRINT
print_matrix(a,1,n,1,n);
printf("\n"); */
print_matrix(b,1,n,1,n);
printf("\n"); */
#endif

t0 = get_seconds();
c = matrix_prod(n,n,n,n,a,b);
t1 = get_seconds();
printf("Time for matrix_prod = %f sec\n",t1-t0);

t0 = get_seconds();
c = block_prod(n1,n1,n1,n2,n2,n2,a,b);
t1 = get_seconds();
printf("Time for block_prod = %f sec\n",t1-t0);

#ifdef PRINT
print_matrix(c,1,n,1,n);
printf("\n");
#endif
}
