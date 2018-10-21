#include "cblas.h"
#include <stdlib.h>

int main() {
  double *a, *b, *c;
  double alpha = 1.0;
  double beta = 1.0;
  int m, n, k;
  m = 100;
  n = 100;
  k = 100;
  a = (double *)malloc(m * k * sizeof(double) );
  b = (double *)malloc(k * n * sizeof(double) );
  c = (double *)malloc(m * n * sizeof(double) );
  //init data
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) { 
      *(c + i * m + j) = i + j;
      *(a + i * m + j) = i + j;
      *(b + i * m + j) = i + j;
    }
  }
  cblas_dgemm_naive(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k,
      alpha, a, m, b, k, beta, c, m);

  printf("Succeed\n");

  return 0;
}
