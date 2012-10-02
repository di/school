#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include "matrix.h"


float **matrix_prod(m1,n1,m2,n2,A,B)
float **A,**B;
int m1,n1,m2,n2;
/*  
* Matrix product.  A is a m1 X n1 matrix with range [1..m1][1..n1]
*  and B is a m2 X n2 matrix with range [1..m2][1..n2].  n1 = m2.
*  C = A * B.
*/
{
int i,j,k;
float **C;

C = zero_matrix(1,m1,1,n2);
for (i=1;i<=m1;i++)
    for (j=1;j<=n2;j++)
        for (k=1;k<=n1;k++)
            C[i][j] = C[i][j] + A[i][k] * B[k][j];
return C;
}
