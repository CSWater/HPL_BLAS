#include "hpl_blas.h"
#include <blis/cblas.h>
#include <stdlib.h>
#include <sys/time.h>
#include <dlfcn.h>

typedef void(*dgemm_type)(enum CBLAS_ORDER, enum CBLAS_TRANSPOSE,
                          enum CBLAS_TRANSPOSE, int, int,
                          int, double, const double *,
                          int, const double *, int,                                                    double, double *, int);
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

int main() {
  void *blas_handle = NULL;
  blas_handle = dlopen("/home/scy/software/hygon/lib/libblis.so", RTLD_LAZY);
  if(!blas_handle) {
    printf("no blaslib found in the destination dir\n");
    return 1;
  }
  dgemm_type dgemm_ptr = (dgemm_type)dlsym(blas_handle, "cblas_dgemm");
  double *a, *b, *c;
  double alpha = 1.0;
  double beta = 1.0;
  int REPEATED = 100;
  int m, n, k;
  m = 38400;
  n = 6;
  k = 6;
  a = (double *)malloc(m * k * sizeof(double) );
  b = (double *)malloc(k * n * sizeof(double) );
  c = (double *)malloc(m * n * sizeof(double) );
  //init data
  //for(int i = 0; i < m; i++) {
  //  for(int j = 0; j < n; j++) { 
  //    *(c + i * m + j) = i + j;
  //    *(a + i * m + j) = i + j;
  //    *(b + i * m + j) = i + j;
  //  }
  //}
  //cblas_dgemm_naive(HblasColMajor, HblasNoTrans, HblasNoTrans, m, n, k,
  //    alpha, a, m, b, k, beta, c, m);
  //hpl_dgemm(HblasColMajor, HblasNoTrans, HblasNoTrans, m, n, k,
  //    alpha, a, m, b, k, beta, c, m);

  double time_cost = 0.0;
  double flops = m * n * k * 2 * 1e-9;

  dgemm_ptr(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k,
      alpha, a, m, b, k, beta, c, m);
  for(int i = 0; i < REPEATED; i++) {
    UTIL_CPU_TIME_tic();
    dgemm_ptr(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k,
        alpha, a, m, b, k, beta, c, m);
    time_cost += UTIL_CPU_TIME_toc();
  }
  printf("time: %lfs\n", time_cost / REPEATED);
  printf("hygon flop/s %lf\n", flops / (time_cost / REPEATED) );

  hpl_dgemm(HblasColMajor, HblasNoTrans, HblasNoTrans, m, n, k,
      alpha, a, m, b, k, beta, c, m);
  time_cost = 0.0;
  for(int i = 0; i < REPEATED; i++) {
    UTIL_CPU_TIME_tic();
    hpl_dgemm(HblasColMajor, HblasNoTrans, HblasNoTrans, m, n, k,
        alpha, a, m, b, k, beta, c, m);
    time_cost += UTIL_CPU_TIME_toc();
  }
  printf("time: %lfs\n", time_cost / REPEATED);
  printf("hpl flop/s %lf\n", flops / (time_cost / REPEATED) );
  
  printf("Succeed\n");

  return 0;
}
