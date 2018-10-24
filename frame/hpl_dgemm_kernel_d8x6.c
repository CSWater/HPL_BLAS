/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a_0 subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <immintrin.h>
#include <xmmintrin.h>
#include "cblas.h"

#define MR 8
#define NR 6

//Assume ColMajor, assume m >> n = k = 6
//Implement 16 * 3 kernel, means mr = 16, nr = 3
void hpl_dgemm_kernel_d8x6(HPL_INT M, HPL_INT N, HPL_INT K,
    double alpha, double *a, HPL_INT lda, double *b, HPL_INT ldb, 
    double beta, double *c, HPL_INT ldc) {
  __m256d ymm4,  ymm5,  ymm6,  ymm7;
  __m256d ymm8,  ymm9,  ymm10, ymm11;
  __m256d ymm12, ymm13, ymm14, ymm15;
  __m256d ymm0, ymm1, ymm2, ymm3;

  int m_remainder;  
  int n_remainder;
  int mm, nn;
  double *c_0 = c;
  double *a_0 = a;
  //double *c_1 = c_0 + ldc;
  //double *c_2 = c_0 + 2 * ldc;
  //double *c_3 = c_0 + 3 * ldc;
  //double *c_4 = c_0 + 4 * ldc;
  //double *c_5 = c_0 + 5 * ldc;
  //HPL_INT ldc_m = 3 * ldc;
  for(mm = 0; mm + (MR - 1) < M; mm += MR) {
    //may need to optimize, cache conficts may occur if ldc is a_0 multiple of cache bank size
    ymm0 = _mm256_broadcast_sd(b);  //broadcast b[0][0]
    ymm1 = _mm256_broadcast_sd(b+4);  //broadcast b[0][1]
    ymm2 = _mm256_loadu_pd(a_0);        //load a_0[0][0-3]
    ymm3 = _mm256_loadu_pd(a_0 + 4);    //load a_0[0][4-7]
    //clear registers
    ymm4  = _mm256_setzero_pd();
    ymm5  = _mm256_setzero_pd();
    ymm6  = _mm256_setzero_pd();
    ymm7  = _mm256_setzero_pd();
    ymm8  = _mm256_setzero_pd();
    ymm9  = _mm256_setzero_pd();
    ymm10 = _mm256_setzero_pd();
    ymm11 = _mm256_setzero_pd();
    ymm12 = _mm256_setzero_pd();
    ymm13 = _mm256_setzero_pd();
    ymm14 = _mm256_setzero_pd();
    ymm15 = _mm256_setzero_pd();
    //calculate MR * NR block of C
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 8);  //broadcast b[0][2]
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 12);   //broadcast b[0][3]
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 16);   //broadcast b[0][4]
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm3, ymm11);
    ymm1  = _mm256_broadcast_sd(b + 20);   //broadcast b[0][5]
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm2  = _mm256_loadu_pd(a_0 + ldc);       //load a_0[0][1]
    ymm0  = _mm256_broadcast_sd(b + 24);    //broadcast b[1][0]
    ymm14 = _mm256_fmadd_pd(ymm1, ymm2, ymm14);
    ymm3 = _mm256_loadu_pd(a_0 + ldc + 4);    //load a_0[1][1]
    ymm15 = _mm256_fmadd_pd(ymm1, ymm3, ymm15);
    _mm_prefetch((char *)(c_0 + 0), _MM_HINT_T0);
    //iteration 1
    ymm1  = _mm256_broadcast_sd(b + 28);    //broadcast b[1][1]
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 32);    //broadcast b[1][2]
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 36);    //broadcast b[1][3]
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 40);    //broadcast b[1][4]
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm3, ymm11);
    ymm1  = _mm256_broadcast_sd(b + 44);    //broadcast b[1][5]
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm0  = _mm256_broadcast_sd(b + 48);    //broadcast b[2][0]
    ymm14 = _mm256_fmadd_pd(ymm1, ymm2, ymm14);
    ymm2  = _mm256_loadu_pd(a_0 + 2 * ldc);
    ymm15 = _mm256_fmadd_pd(ymm1, ymm3, ymm15);
    ymm3  = _mm256_loadu_pd(a_0 + 2 * ldc + 4);
    _mm_prefetch((char *)(c_0 + ldc), _MM_HINT_T0);
    //iteration 3
    ymm1  = _mm256_broadcast_sd(b + 52);    //broadcast b[2][1]
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 56);    //broadcast b[2][2]
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 60);
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 64);
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm3, ymm11);
    ymm1  = _mm256_broadcast_sd(b + 68);
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm0  = _mm256_broadcast_sd(b + 72);
    ymm14 = _mm256_fmadd_pd(ymm1, ymm2, ymm14);
    ymm2  = _mm256_loadu_pd(a_0 + 3 * ldc);
    ymm15 = _mm256_fmadd_pd(ymm1, ymm3, ymm15);
    ymm3  = _mm256_loadu_pd(a_0 + 3 * ldc + 4);
    _mm_prefetch((char *)(c_0 + 2 * ldc), _MM_HINT_T0);
    //iteration 4
    ymm1  = _mm256_broadcast_sd(b + 76);
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 80);
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 84);
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 88);
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm2, ymm11);
    ymm1  = _mm256_broadcast_sd(b + 92);
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm0  = _mm256_broadcast_sd(b + 96);
    ymm14 = _mm256_fmadd_pd(ymm1, ymm2, ymm14);
    ymm2  = _mm256_loadu_pd(a_0 + 4 * ldc);
    ymm15 = _mm256_fmadd_pd(ymm1, ymm2, ymm15);
    ymm3  = _mm256_loadu_pd(a_0 + 4 * ldc + 4);
    _mm_prefetch((char *)(c_0 + 3 * ldc), _MM_HINT_T0);
    //iteration 5
    ymm1  = _mm256_broadcast_sd(b + 100);
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 104);
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 108);
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 112);
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm3, ymm11);
    ymm1  = _mm256_broadcast_sd(b + 116);
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm0  = _mm256_broadcast_sd(b + 120);
    ymm14 = _mm256_fmadd_pd(ymm1, ymm2, ymm14);
    ymm2  = _mm256_loadu_pd(a_0 + 5 * ldc);
    ymm15 = _mm256_fmadd_pd(ymm1, ymm3, ymm15);
    ymm3  = _mm256_loadu_pd(a_0 + 5 * ldc + 4);
    _mm_prefetch((char *)(c_0 + 4 * ldc), _MM_HINT_T0);
    //iteration 6
    ymm1  = _mm256_broadcast_sd(b + 124);
    ymm4  = _mm256_fmadd_pd(ymm0, ymm2, ymm4);
    ymm5  = _mm256_fmadd_pd(ymm0, ymm3, ymm5);
    ymm0  = _mm256_broadcast_sd(b + 128);
    ymm6  = _mm256_fmadd_pd(ymm1, ymm2, ymm6);
    ymm7  = _mm256_fmadd_pd(ymm1, ymm3, ymm7);
    ymm1  = _mm256_broadcast_sd(b + 132);
    ymm8  = _mm256_fmadd_pd(ymm0, ymm2, ymm8);
    ymm9  = _mm256_fmadd_pd(ymm0, ymm3, ymm9);
    ymm0  = _mm256_broadcast_sd(b + 136);
    ymm10 = _mm256_fmadd_pd(ymm1, ymm2, ymm10);
    ymm11 = _mm256_fmadd_pd(ymm1, ymm2, ymm11);
    ymm1  = _mm256_broadcast_sd(&alpha);
    ymm12 = _mm256_fmadd_pd(ymm0, ymm2, ymm12);
    ymm13 = _mm256_fmadd_pd(ymm0, ymm3, ymm13);
    ymm0  = _mm256_broadcast_sd(&beta);
    _mm_prefetch((char *)(c_0 + 5 * ldc), _MM_HINT_T0);
    //multiply A*B by alpha
    ymm4  = _mm256_mul_pd(ymm4, ymm1);
    ymm5  = _mm256_mul_pd(ymm5, ymm1);
    ymm6  = _mm256_mul_pd(ymm6, ymm1);
    ymm7  = _mm256_mul_pd(ymm7, ymm1);
    ymm8  = _mm256_mul_pd(ymm8, ymm1);
    ymm9  = _mm256_mul_pd(ymm9, ymm1);
    ymm10 = _mm256_mul_pd(ymm10, ymm1);
    ymm11 = _mm256_mul_pd(ymm11, ymm1);
    ymm12 = _mm256_mul_pd(ymm12, ymm1);
    ymm13 = _mm256_mul_pd(ymm13, ymm1);
    ymm14 = _mm256_mul_pd(ymm14, ymm1);
    ymm15 = _mm256_mul_pd(ymm15, ymm1);
    //beta is always 1, we just omit beta*c_0
    //col 1-2
    ymm0  = _mm256_loadu_pd(c_0);
    ymm1  = _mm256_loadu_pd(c_0 + 4);
    ymm2  = _mm256_loadu_pd(c_0 + ldc);
    ymm3  = _mm256_loadu_pd(c_0 + ldc + 4);
    ymm4  = _mm256_add_pd(ymm0, ymm4);
    ymm5  = _mm256_add_pd(ymm1, ymm5);
    ymm6  = _mm256_add_pd(ymm2, ymm6);
    ymm7  = _mm256_add_pd(ymm3, ymm7);
    _mm256_storeu_pd(c_0, ymm4);
    _mm256_storeu_pd(c_0 + 4, ymm5);
    _mm256_storeu_pd(c_0 + ldc, ymm6);
    _mm256_storeu_pd(c_0 + ldc + 4, ymm7);
    //col 3-4
    ymm0  = _mm256_loadu_pd(c_0 + 2 * ldc);
    ymm1  = _mm256_loadu_pd(c_0 + 2 * ldc + 4);
    ymm2  = _mm256_loadu_pd(c_0 + 3 * ldc);
    ymm3  = _mm256_loadu_pd(c_0 + 3 * ldc + 4);
    ymm8  = _mm256_add_pd(ymm0, ymm8);
    ymm9  = _mm256_add_pd(ymm1, ymm9);
    ymm10 = _mm256_add_pd(ymm2, ymm10);
    ymm11 = _mm256_add_pd(ymm3, ymm11);
    _mm256_storeu_pd(c_0 + 2 * ldc, ymm8);
    _mm256_storeu_pd(c_0 + 2 * ldc + 4, ymm9);
    _mm256_storeu_pd(c_0 + 3 * ldc, ymm10);
    _mm256_storeu_pd(c_0 + 3 * ldc + 4, ymm11);
    //col 5-6
    ymm0  = _mm256_loadu_pd(c_0 + 4 * ldc);
    ymm1  = _mm256_loadu_pd(c_0 + 4 * ldc + 4);
    ymm2  = _mm256_loadu_pd(c_0 + 5 * ldc);
    ymm3  = _mm256_loadu_pd(c_0 + 6 * ldc + 4);
    ymm12 = _mm256_add_pd(ymm0, ymm12);
    ymm13 = _mm256_add_pd(ymm1, ymm13);
    ymm14 = _mm256_add_pd(ymm2, ymm14);
    ymm15 = _mm256_add_pd(ymm3, ymm15);
  }
    
}
