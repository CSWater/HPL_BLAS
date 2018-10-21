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
typedef enum {CblasRowMajor = 1, CblasColMajor = 2} CBLAS_LAYOUT;
typedef enum {CblasNoTrans = 3, CblasTrans = 4} CBLAS_TRANSPOSE;  //now, no need for CblasConjTrans


#endif
