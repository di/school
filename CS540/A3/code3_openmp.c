#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <emmintrin.h>

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
pointing to the existing matris range A[oldrl..olrdrh][oldcl..oldch].  */
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

float *vector_prod(A,B,n)
float *A,*B;
int n;
/*  
* Matrix product.  A is a n X n matrix with range [1..n][1..n]
*  and B is a m2 X n matrix with range [1..m2][1..n].  n = m2.
*  C = A * B.
*/
{
int i,j,k;
float *C;
__m128 c0, c1, c2, c3;
__m128 a0, a1, a2, a3;
__m128 b0, b1, b2, b3;

C = vector(1,n*n);

//#pragma omp parallel for private(A, B, C, i, j, k, c0, c1, c2, c3, a0, a1, a2, a3, b0, b1, b2, b3)
#pragma omp parallel for private(i, j, k, c0, c1, c2, c3, a0, a1, a2, a3, b0, b1, b2, b3)
for (i=1;i<n;i+=4)
{
    for (j=1;j<n;j+=4)
    {
        c0 = _mm_setzero_ps();
        c1 = _mm_setzero_ps();
        c2 = _mm_setzero_ps();
        c3 = _mm_setzero_ps();
        for (k=1;k<n;k+=4) 
        {
            a0 = _mm_set_ps1(A[k]);
            a1 = _mm_set_ps1(A[n+k]);
            a2 = _mm_set_ps1(A[2*n+k]);
            a3 = _mm_set_ps1(A[3*n+k]);
            b0 = _mm_load_ps( B+(k*n) + j);
            c0 = _mm_add_ps(c0, _mm_mul_ps(a0, b0));
            c1 = _mm_add_ps(c1, _mm_mul_ps(a1, b0));
            c2 = _mm_add_ps(c2, _mm_mul_ps(a2, b0));
            c3 = _mm_add_ps(c3, _mm_mul_ps(a3, b0));
            
            a0 = _mm_set_ps1(A[k+1]);
            a1 = _mm_set_ps1(A[n+k+1]);
            a2 = _mm_set_ps1(A[2*n+k+1]);
            a3 = _mm_set_ps1(A[3*n+k+1]);
            b1 = _mm_load_ps( B+((k+1)*n) + j);
            c0 = _mm_add_ps(c0, _mm_mul_ps(a0, b1));
            c1 = _mm_add_ps(c1, _mm_mul_ps(a1, b1));
            c2 = _mm_add_ps(c2, _mm_mul_ps(a2, b1));
            c3 = _mm_add_ps(c3, _mm_mul_ps(a3, b1));

            a0 = _mm_set_ps1(A[k+2]);
            a1 = _mm_set_ps1(A[n+k+2]);
            a2 = _mm_set_ps1(A[2*n+k+2]);
            a3 = _mm_set_ps1(A[3*n+k+2]);
            b2 = _mm_load_ps( B+((k+2)*n) + j);
            c0 = _mm_add_ps(c0, _mm_mul_ps(a0, b2));
            c1 = _mm_add_ps(c1, _mm_mul_ps(a1, b2));
            c2 = _mm_add_ps(c2, _mm_mul_ps(a2, b2));
            c3 = _mm_add_ps(c3, _mm_mul_ps(a3, b2));
            
            a0 = _mm_set_ps1(A[k+3]);
            a1 = _mm_set_ps1(A[n+k+3]);
            c0 = _mm_add_ps(c0, _mm_mul_ps(a0, b3));
            a2 = _mm_set_ps1(A[2*n+k+3]);
            a3 = _mm_set_ps1(A[3*n+k+3]);
            b3 = _mm_load_ps( B+((k+3)*n) + j);
            c1 = _mm_add_ps(c1, _mm_mul_ps(a1, b3));
            c2 = _mm_add_ps(c2, _mm_mul_ps(a2, b3));
            c3 = _mm_add_ps(c3, _mm_mul_ps(a3, b3));
        }
        _mm_store_ps(C+j, c0);
        _mm_store_ps(C+n+j,   c1);
        _mm_store_ps(C+n*2+j, c2);
        _mm_store_ps(C+n*3+j, c3);
    }
    C += 4*n;
    A += 4*n;
}
return C;
}
