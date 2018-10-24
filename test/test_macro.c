/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * For the purpose of optimizing hpl benchmark,I wrote this 
 * sub-blas lib, including a subset of functions needed by hpl.
 * This lib is specially optimized for AMD ZEN architecture and
 * gemm shapes appeared in the hpl pannel factorization.
 *
 *           By Chaoyang Shui from NCIC
 *           email: shuichaoyang@ncic.ac.cn
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "common.h"
#include "bli_x86_asm_macros.h"

int main() {
  PRINT_DEFINE(prefetch(0, mem(rcx, 7*8)) );
  PRINT_DEFINE(prefetch(0, mem(rcx, rdi, 1, 7*8)) );
  PRINT_DEFINE(add(imm(32*4), rbx) );
  PRINT_DEFINE(add(rdi, rdx));
  return 0;
}
