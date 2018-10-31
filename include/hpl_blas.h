/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef __HPL_BLAS_H__
#include "types.h"
#include "common.h"

//cblas dgemm api
void hpl_dgemm(const HBLAS_LAYOUT layout, const HBLAS_TRANSPOSE transa,
                 const HBLAS_TRANSPOSE transb, const HPL_INT m, const
                 HPL_INT n, const HPL_INT k, const double alpha, const
                 double *a, const HPL_INT lda, const double *b, const
                 HPL_INT ldb, const double beta, double *c, const HPL_INT ldc);

void hpl_dgemm_backend(HPL_INT m, HPL_INT n, HPL_INT k, double alpha,
    const double *a, HPL_INT lda, const double *b, HPL_INT ldb, 
    double beta, double *c, HPL_INT ldc);

void hpl_dgemm_kernel_d8x6(HPL_INT M, HPL_INT N, HPL_INT K,
    double alpha, double *a, HPL_INT lda, double *b, HPL_INT ldb, 
    double beta, double *c, HPL_INT ldc);
//naive dgemm
void cblas_dgemm_naive(const HBLAS_LAYOUT layout, const HBLAS_TRANSPOSE transa,
                 const HBLAS_TRANSPOSE transb, const HPL_INT m, const
                 HPL_INT n, const HPL_INT k, const double alpha, const
                 double *a, const HPL_INT lda, const double *b, const
                 HPL_INT ldb, const double beta, double *c, const HPL_INT ldc);

#endif
