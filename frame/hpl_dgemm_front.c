/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "hpl_blas.h"
void hpl_dgemm(const HBLAS_LAYOUT layout, const HBLAS_TRANSPOSE transa,
                 const HBLAS_TRANSPOSE transb, const HPL_INT m, const
                 HPL_INT n, const HPL_INT k, const double alpha, const
                 double *a, const HPL_INT lda, const double *b, const
                 HPL_INT ldb, const double beta, double *c, const HPL_INT ldc) {
  if(layout != HblasColMajor) {
    printf("only support col major store\n");
    return;
  }
  if(transa != HblasNoTrans || transb != HblasNoTrans) {
    printf("only support NN\n");
    return;
  }
  if(m == 0 || n == 0 || k == 0) {
    printf("wrong n or n or k\n");
    return;
  }
  hpl_dgemm_backend(m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);

}


