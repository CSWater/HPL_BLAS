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
#include <omp.h>

void hpl_dgemm_backend(HPL_INT m, HPL_INT n, HPL_INT k, double alpha,
    const double *a, HPL_INT lda, const double *b, HPL_INT ldb, 
    double beta, double *c, HPL_INT ldc) {
  //packing B
  double *pb = (double *)malloc(n * k * sizeof(double) );
  for(int i = 0; i < k; i++) {
    for(int j = 0; j < n; j++) {
      *(pb + i * n + j) = *(b + j * k + i);
    }
  }
  HPL_INT step = lda / 6;
#pragma omp parallel for shared(pb)
  for(int i = 0; i < lda; i += step) {
    double *c_me = c + i;
    double *a_me = a + i;
    hpl_dgemm_kernel_d8x6(m, n, k, -1.0, a_me, m, pb, n, 1, c_me, m);
  }
  //free pack memory
  free(pb);

}

