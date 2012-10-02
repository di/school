#include "matrix.h"

float 
**block_prod(int m1,int p1,int n1,int m2,int p2,int n2, float **A,float **B)
{
int i1,j1,k1,i2,j2,k2;
float **C;

C = zero_matrix(1,m1*m2,1,n1*n2);
for (i1=1;i1<m1*m2;i1 = i1+m2)
  for (j1=1;j1<n1*n2;j1 = j1+n2) 
    for (k1=1;k1<p1*p2;k1 = k1+p2)
      /* C_i1,j1 = C_i1,j1 + A_i1,k1 * B_k1,j1 */
      for (i2=i1;i2<i1+m2;i2++)
        for (j2=j1;j2<j1+n2;j2++)
          for (k2=k1;k2<k1+p2;k2++)
            C[i2][j2] = C[i2][j2] + A[i2][k2] * B[k2][j2];
return C;
}
