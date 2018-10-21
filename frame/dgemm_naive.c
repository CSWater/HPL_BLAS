/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "cblas.h"

#define Iter(ptr, i, j, ldx) *(ptr + (i) * ldx + j)
void cblas_dgemm_naive(const CBLAS_LAYOUT layout, const CBLAS_TRANSPOSE 
    transa, const CBLAS_TRANSPOSE transb, const HPL_INT M, const HPL_INT
    N, const HPL_INT K, const double alpha, const double *a, const HPL_INT
    lda, const double *b, const HPL_INT ldb, const double beta, double *c,
    const HPL_INT ldc) {
  if(layout != CblasColMajor) {
    printf("Only support CblasColMajor\n");
    return;
  }
  if(transa != CblasNoTrans && transb != CblasNoTrans) {
    printf("Only support NN\n");
    return;
  }
  //naive three nested-loops implementation of gemm
  int i, j, k;
  //multi c by beta
  for(i = 0; i < M; i++) {
    for(j = 0; j < N; j++) {
      Iter(c, i, j, ldc) *= beta;
    }
  }
  for(i = 0; i < M; i++) {
    for(j = 0; j < N; j++) {
      for(k = 0; k < K; k++) {
        Iter(c, i, j, ldc) += Iter(a, k, i, lda) * Iter(b, j, k, ldb);
      }
    }
  }


}
