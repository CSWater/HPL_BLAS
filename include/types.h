/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __TYPES_H__
#include <stdint.h>
typedef uint64_t HPL_INT;
typedef enum {HblasRowMajor = 1, HblasColMajor = 2} HBLAS_LAYOUT;
typedef enum {HblasNoTrans = 3, HblasTrans = 4} HBLAS_TRANSPOSE;  //now, no need for CblasConjTrans


#endif
