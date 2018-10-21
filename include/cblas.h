/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef __CBLAS_H__
#include "types.h"
#include "common.h"

//cblas dgemm api
void cblas_dgemm(const CBLAS_LAYOUT layout, const CBLAS_TRANSPOSE transa,
                 const CBLAS_TRANSPOSE transb, const HPL_INT m, const
                 HPL_INT n, const HPL_INT k, const double alpha, const
                 double *a, const HPL_INT lda, const double *b, const
                 HPL_INT ldb, const double beta, double *c, const HPL_INT ldc);

//naive dgemm
void cblas_dgemm_naive(const CBLAS_LAYOUT layout, const CBLAS_TRANSPOSE transa,
                 const CBLAS_TRANSPOSE transb, const HPL_INT m, const
                 HPL_INT n, const HPL_INT k, const double alpha, const
                 double *a, const HPL_INT lda, const double *b, const
                 HPL_INT ldb, const double beta, double *c, const HPL_INT ldc);

#endif
