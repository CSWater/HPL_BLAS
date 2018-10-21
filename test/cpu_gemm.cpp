/*
 *  gemm performance benchmark
 *
 *  Chaoyang Shui
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include <dlfcn.h>
#ifdef BLIS
#include <blis/cblas.h>
#elif BLIS_SMALL
#include <blis/cblas.h>
#else
#include <cblas.h>
#endif
#include "timer.h"
const size_t N = 20890;
const size_t MATRIX_SIZE = 42000;
typedef void(*dgemm_type)(enum CBLAS_ORDER, enum CBLAS_TRANSPOSE, 
                          enum CBLAS_TRANSPOSE, int, int,
                          int, double, const double *,
                          int, const double *, int,
                          double, double *, int);

struct timeval UTIL_CPU_TIME_start, UTIL_CPU_TIME_end;
void UTIL_CPU_TIME_tic(){
    gettimeofday(&UTIL_CPU_TIME_start, NULL);
}
double UTIL_CPU_TIME_toc(){
    gettimeofday(&UTIL_CPU_TIME_end, NULL);
    double result = (UTIL_CPU_TIME_end.tv_sec - UTIL_CPU_TIME_start.tv_sec) + \
	  	    (UTIL_CPU_TIME_end.tv_usec - UTIL_CPU_TIME_start.tv_usec) / 1000000.0;
    return result;
}

int main(int argc, char* argv[]) {
  void *blas_handle = NULL;
#ifdef BLIS_SMALL
  blas_handle = dlopen("/home/scy/software/blis_nothreading/lib/libblis.so", RTLD_LAZY);
#elif BLIS
  blas_handle = dlopen("/home/scy/software/blis/lib/libblis.so", RTLD_LAZY);
#else
  blas_handle = dlopen("/home/scy/software/openblas/lib/libopenblas.so", RTLD_LAZY);
#endif
  if(!blas_handle) {
    std::cout << "no blaslib found in the destination dir" << std::endl;
    return 1;
  }
  dgemm_type dgemm_ptr = (dgemm_type)dlsym(blas_handle, "cblas_dgemm");
  //timer
  unsigned cycles_high, cycles_low, cycles_low1, cycles_high1;
  uint64_t start, end;
  //read gemm sizes
  size_t gemm_size[N][3];
  std::ifstream fin("small_gemm");
  int n_case = 0;
  while(fin >> gemm_size[n_case][0] >> gemm_size[n_case][1] >> gemm_size[n_case][2]) {
    n_case++;
  }
  size_t m, n, k;
  // DGEMM: C = alpha*Amk*Bkn + beta*Cmn
  double alpha = -1.0;
  double beta  = 1.0;
  double EPSILON = 0.0001;
  //allocate gemm memory
  double *gemm_data = new double[MATRIX_SIZE * MATRIX_SIZE];
  //for(int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
  //  *(gemm_data + i) = sin(i);
  //}
  double *A, *B, *C;
  size_t lda = MATRIX_SIZE;
  size_t ldb = MATRIX_SIZE;
  size_t ldc = MATRIX_SIZE;
  for(int i = 0; i < n_case; i++) {
    //get m n k
    m = gemm_size[i][0];
    n = gemm_size[i][1];
    k = gemm_size[i][2];
    A = gemm_data + k * MATRIX_SIZE;        //A = (k, 0)
    B = gemm_data + k;                      //B = (0, k)
    C = gemm_data + k * MATRIX_SIZE + k;    //C = (k, k)
    //warm up
    for(int j = 0; j < 10; j++) {
      dgemm_ptr(CblasColMajor,
                 CblasNoTrans, CblasNoTrans,
                 m, n, k,
                 alpha,
                 A, lda,
                 B, ldb,
                 beta,
                 C, ldc);
    }
    //UTIL_CPU_TIME_tic();
    double total_cycle = 0;
    const int REPEATED_TIMES = 100;
    for(int j = 0; j < REPEATED_TIMES; j++) {
      TIMER_START(cycles_high, cycles_low);
      dgemm_ptr(CblasColMajor,
                  CblasNoTrans, CblasNoTrans,
                  m, n, k,
                  alpha,
                  A, lda,
                  B, ldb,
                  beta,
                  C, ldc);
	    //time_stage += UTIL_CPU_TIME_toc();
      TIMER_END(cycles_high1, cycles_low1);
      start = ( ((uint64_t)cycles_high << 32) | cycles_low );
      end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
      total_cycle += (end - start);
#ifdef VERBOSE
      printf("%llu\t", end - start);
#endif
    }
    printf("cycles: %.0lf\n", total_cycle / REPEATED_TIMES);
    //double gemm_perf = 2.0 * 1e-12 * m * n * k / time_stage;
    //double gemm_time = 1.0 * time_stage;
    //printf("%d,%d,%d,%.4lf,%lf\n",
    //       m, n, k,
    //       gemm_perf, gemm_time);
    //  
  }

// Clean up resources
  delete gemm_data;
  return 0;
}
