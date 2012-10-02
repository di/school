#include "matrix.h"
#include <stdio.h>
#include "mkl_cblas.h"
#include <stdlib.h>
#include "mkl.h"

float *mkl_sgemm(float *A, float *B, int n) {
    
    float *C;
    //C = zero_matrix(1,n,1,n);
    C = ((float *)malloc(n*n*sizeof(float)));
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 0.0, C, n);
    return C;
}
