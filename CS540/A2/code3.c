#include <math.h>
#include <malloc.h>
#include <stdio.h>

void nerror(error_text)
char error_text[];
/* Numerical Recipes standard error handler */
{
     void exit();

     fprintf(stderr,"Numerical Recipes run-time error...\n");
     fprintf(stderr,"%s\n",error_text);
     fprintf(stderr,"...now exiting to system...\n");
     exit(1);
}


float *vector(nl,nh)
int nl,nh;
/* Allocates a float vector with range [nl..nh]  */
{
     float *v;

     v = (float *) malloc((unsigned) (nh-nl+1)*sizeof(float));
     if (!v) nerror("allocation failure in vector()");
     return v-nl;
}

float **matrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
/* Allocates a float matrix with range [nrl..nrh][ncl..nch]  */
{
     int i;
     float **m;

/* Allocate pointers to rows  */
m = (float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
if (!m) nerror("allocation failure 1 in matrix()");
m -= nrl;

/* Allocate rows and set pointers to them  */
for (i=nrl;i<=nrh;i++) {
    m[i] = (float *) malloc((unsigned) (nch - ncl + 1)*sizeof(float));
    if (!m[i]) nerror("allocation failure 2 in matrix()");
    m[i] -= ncl;
}
/* return pointer to array of pointers of rows  */
return m;
}

float **zero_matrix(rl,rh,cl,ch)
int rl,rh,cl,ch;
/* Create matrix with range [rl..rh][cl..ch] whose entries are all zero. */
{
float **A;
int i,j;

A = matrix(rl,rh,cl,ch);
for (i=rl;i<=rh;i++)
    for (j=cl;j<=ch;j++)
       A[i][j] = 0.0;
return A;
} 

void print_vector(v,nl,nh)
int nl,nh;
float *v;
/* print a vector*/
{
    int i;

    for (i=nl;i<=nh;i++)
        printf("v[%d] = %f\n",i,v[i]);
}

void print_matrix(a,nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
float **a;
/* print a matrix */
{
    int i,j;

    for (i=nrl;i<=nrh;i++)
        for (j=ncl;j<=nch;j++)
           printf("A[%d,%d] = %f\n",i,j,a[i][j]);
}

float **submatrix(a,oldrl,oldrh,oldcl,oldch,newrl,newcl)
int oldrl,oldrh,oldcl,oldch,newrl,newcl;
float **a;
/* Returns a submatrix with range [newrl..newrl+(oldrh-oldrl)] 
                                  [newcl..newcl+(oldch-oldcl)] 
pointing to the existing matris range a[oldrl..olrdrh][oldcl..oldch].  */
{
     int i,j;
     float **m;

/*  Allocate pointers to rows  */
m = (float **) malloc((unsigned) (oldrh - oldrl + 1)*sizeof(float *));
if (!m) nerror("allocation failure in submatrix()");
m -= newrl;

/*  set pointers to rows  */
for (i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j] = a[i]+oldcl-newcl;

/* return pointer to array of pointers to rows  */
return m;
}


void insert_matrix(A,rl,rh,cl,ch,M,nrl,ncl)
float **A,**M;
int rl,rh,cl,ch,nrl,ncl;
/* insert matrix A with range [rl..rh][cl..ch]
 * into matrix M with range [nrl..nrl+(rh-rl+1)][ncl..ncl+(ch-cl+1)].
 * The matrix C is modified.
*/
{
int i,j,k,l;

for (i=rl,k=nrl;i<=rh;i++,k++)
    for (j=cl,l=ncl;j<=ch;j++,l++)
        M[k][l] = A[i][j];
}

void free_vector(v,nl,nh)
float *v;
int nl,nh;
/* Frees a float vector allocated by vector().  */
{
     free((char*) (v+nl));
}

void free_matrix(m,nrl,nrh,ncl,nch)
float **m;
int nrl,nrh,ncl,nch;
/* Frees a float matrix allocated by matrix().  */
{
     int i;

     for (i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
     free((char*) (m+nrl));
}

void free_submatrix(b,nrl,nrh,ncl,nch)
  float **b;
  int nrl,nrh,ncl,nch;
/* Frees a float submatrix allocated by submatrix. */
{
  free((char*) (b+nrl));
/*  free_vector(m,nrl,nrh); */
}

float matrix_norm(m,n,A)
float **A;
int m,n;
/*  A is an m X n matrix with range [1..m][1..n].
*   Return S = sum_{i,j} A_{i,j}.
*/

{
float S;
int i,j;

for (i=1;i<=m;i++)
    for (j=1;j<=n;j++)
      S = S + fabs(A[i][j]);
return S;
}


float **matrix_add(m,n,A,B)
float **A,**B;
int m,n;
/*  Matrix Add.  A,B are m X n matrices with range [1..m][1..n].
 *  C = A + B
*/
{
int i,j;
float **C;

C = matrix(1,m,1,n);
for (i=1;i<=m;i++)
    for (j=1;j<=n;j++)
        C[i][j] = A[i][j] + B[i][j];
return C;
}

float **matrix_sub(m,n,A,B)
float **A,**B;
int m,n;
/*  Matrix subtraction.  A,B are m X n matrices with range [1..m][1..n].
 *  C = A - B
*/
{
int i,j;
float **C;

C = matrix(1,m,1,n);
for (i=1;i<=m;i++)
    for (j=1;j<=n;j++)
        C[i][j] = A[i][j] - B[i][j];
return C;
}

float **matrix_prod(m1,n1,m2,n2,A,B,NB)
float **A,**B;
int m1,n1,m2,n2;
int NB;
/*  
* Matrix product.  A is a m1 X n1 matrix with range [1..m1][1..n1]
*  and B is a m2 X n2 matrix with range [1..m2][1..n2].  n1 = m2.
*  C = A * B.
*/
{
int i,j,k;
float **C;
int MU, NU, KU;
int ii,jj,kk;
MU=2; NU=2; KU=4;
float c0, c1, c2, c3;
float a0, a1, b0, b1;
float a2, a3, b2, b3;
float a4, a5, b4, b5;
float a6, a7, b6, b7;
float t;

C = zero_matrix(1,m1,1,n2);
for (i=1;i<m1;i+=NB)
{
    for (j=1;j<n2;j+=NB)
    {
        for (k=1;k<n1;k+=NB) 
        {
            for (ii=i;ii<i+NB;ii+=MU)
            {
            // Mini-MMM ijk loop
                for (jj=j;jj<j+NB;jj+=NU)
                {
                    c0 = C[ii][jj];
                    c1 = C[ii+1][jj];
                    c2 = C[ii][jj+1];
                    c3 = C[ii+1][jj+1];

                    for (kk=j;kk<k+NB;kk+=KU) 
                    {
                        // Hand-unrolled micro-MMM kij loop
                        // MU=NU=2, KU=1
                        a0 = A[ii][kk];
                        a1 = A[ii+1][kk];
                        a2 = A[ii][kk+1];
                        a3 = A[ii+1][kk+1];
                        a4 = A[ii][kk+2];
                        a5 = A[ii+1][kk+2];
                        a6 = A[ii][kk+3];
                        a7 = A[ii+1][kk+3];
                        b0 = B[kk][jj];
                        b1 = B[kk][jj+1];
                        b2 = B[kk+1][jj];
                        b3 = B[kk+1][jj+1];
                        b4 = B[kk+2][jj];
                        b5 = B[kk+2][jj+1];
                        b6 = B[kk+3][jj];
                        b7 = B[kk+3][jj+1];

                        t = a0 * b0; 
                        c0 = c0 + t;
                        t = a1 * b0; 
                        c1 = c1 + t;
                        t = a0 * b1;
                        c2 = c2 + t;
                        t = a1 * b1;
                        c3 = c3 + t;
                        t = a2 * b2;
                        c0 = c0 + t;
                        t = a3 * b2;
                        c1 = c1 + t;
                        t = a2 * b3;
                        c2 = c2 + t;
                        t = a3 * b3;
                        c3 = c3 + t;
                        t = a4 * b4;
                        c0 = c0 + t;
                        t = a5 * b4;
                        c1 = c1 + t;
                        t = a4 * b5;
                        c2 = c2 + t;
                        t = a5 * b5;
                        c3 = c3 + t;
                        t = a6 * b6;
                        c0 = c0 + t;
                        t = a7 * b6;
                        c1 = c1 + t;
                        t = a6 * b7;
                        c2 = c2 + t;
                        t = a7 * b7;
                        c3 = c3 + t;

                        // C[ii][jj] += A[ii][kk] * B[kk][jj];
                        // C[ii+1][jj] += A[ii+1][kk] * B[kk][jj];
                        // C[ii][jj+1] += A[ii][kk] * B[kk][jj+1];
                        // C[ii+1][jj+1] += A[ii+1][kk] * B[kk][jj+1];
                        // C[ii][jj] += A[ii][kk+1] * B[kk+1][jj];
                        // C[ii+1][jj] += A[ii+1][kk+1] * B[kk+1][jj];
                        // C[ii][jj+1] += A[ii][kk+1] * B[kk+1][jj+1];
                        // C[ii+1][jj+1] += A[ii+1][kk+1] * B[kk+1][jj+1];
                        // C[ii][jj] += A[ii][kk+2] * B[kk+2][jj];
                        // C[ii+1][jj] += A[ii+1][kk+2] * B[kk+2][jj];
                        // C[ii][jj+1] += A[ii][kk+2] * B[kk+2][jj+1];
                        // C[ii+1][jj+1] += A[ii+1][kk+2] * B[kk+2][jj+1];
                        // C[ii][jj] += A[ii][kk+3] * B[kk+3][jj];
                        // C[ii+1][jj] += A[ii+1][kk+3] * B[kk+3][jj];
                        // C[ii][jj+1] += A[ii][kk+3] * B[kk+3][jj+1];
                        // C[ii+1][jj+1] += A[ii+1][kk+3] * B[kk+3][jj+1];
                    }
                    C[ii][jj] = c0;
                    C[ii+1][jj] = c1;
                    C[ii][jj+1] = c2;
                    C[ii+1][jj+1] = c3;
                }
            }
        }
    }
}
return C;
}
