#define TIMER_START(cycles_high, cycles_low) \
  asm volatile("CPUID\n\t"  \
               "RDTSC\n\t"  \
               "mov %%edx, %0\n\t"  \
               "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: \
               "%rax", "%rbx", "%rcx", "%rdx")


#define TIMER_END(cycles_high, cycles_low) \
  asm volatile("RDTSCP\n\t"  \
               "mov %%edx, %0\n\t"  \
               "mov %%eax, %1\n\t"  \
               "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low)::  \
               "%rax", "%rbx", "%rcx", "%rdx")
