	.file	"hpl_dgemm_kernel_d8x6.c"
	.text
	.p2align 4,,15
	.globl	hpl_dgemm_kernel_d8x6
	.type	hpl_dgemm_kernel_d8x6, @function
hpl_dgemm_kernel_d8x6:
.LFB1081:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$176, %rsp
	cmpq	$7, %rdi
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, 144(%rsp)
	movq	24(%rbp), %rax
	movq	32(%rbp), %r8
	jbe	.L5
	leaq	8(%r9), %rbx
	movq	%r8, %r11
	vxorpd	%xmm0, %xmm0, %xmm0
	movq	%rbx, 152(%rsp)
	leaq	32(%rcx), %rbx
	salq	$4, %r11
	movq	%rbx, 128(%rsp)
	leaq	16(%r9), %rbx
	addq	$32, %r11
	leaq	0(,%r8,8), %r15
	movq	%rbx, 136(%rsp)
	leaq	24(%r9), %rbx
	movq	%rbx, 120(%rsp)
	leaq	(%rcx,%r15), %rbx
	movq	%rbx, 112(%rsp)
	leaq	200(%r9), %r13
	movq	%rbx, %rsi
	leaq	48(%r9), %rbx
	movq	%r13, -48(%rsp)
	movq	%rbx, 104(%rsp)
	leaq	32(%r15), %rbx
	leaq	(%rcx,%rbx), %rdx
	addq	%rax, %rbx
	movq	%rdx, 96(%rsp)
	leaq	56(%r9), %rdx
	movq	%rdx, 88(%rsp)
	leaq	64(%r9), %rdx
	movq	%rdx, 80(%rsp)
	leaq	72(%r9), %rdx
	movq	%rdx, 72(%rsp)
	leaq	96(%r9), %rdx
	movq	%rdx, 64(%rsp)
	leaq	(%rsi,%r15), %rdx
	leaq	(%rcx,%r11), %rsi
	movq	%rdx, 56(%rsp)
	addq	%rax, %r11
	movq	%rsi, 48(%rsp)
	leaq	104(%r9), %rsi
	movq	%rsi, 40(%rsp)
	leaq	112(%r9), %rsi
	movq	%rsi, 32(%rsp)
	leaq	120(%r9), %rsi
	movq	%rsi, 24(%rsp)
	leaq	144(%r9), %rsi
	movq	%rsi, 16(%rsp)
	leaq	(%rdx,%r15), %rsi
	leaq	(%r8,%r8,2), %rdx
	movq	%rsi, %r14
	movq	%rsi, 8(%rsp)
	leaq	32(,%rdx,8), %r10
	leaq	152(%r9), %rdx
	movq	%rdx, -8(%rsp)
	leaq	208(%r9), %r13
	leaq	160(%r9), %rdx
	movq	%r13, -56(%rsp)
	movq	%rdx, -16(%rsp)
	leaq	216(%r9), %r13
	leaq	168(%r9), %rdx
	movq	%r13, -64(%rsp)
	movq	%rdx, -24(%rsp)
	leaq	(%r14,%r15), %r14
	leaq	192(%r9), %rdx
	leaq	240(%r9), %r13
	movq	%rdx, -32(%rsp)
	movq	%r8, %rdx
	movq	%r13, -72(%rsp)
	leaq	(%r8,%r8,4), %r8
	salq	$5, %rdx
	leaq	(%r14,%r15), %r13
	movq	%r13, -80(%rsp)
	leaq	32(%rcx,%r8,8), %r13
	movq	144(%rsp), %r8
	leaq	(%rcx,%r10), %rsi
	movq	%r13, -88(%rsp)
	addq	%rax, %r10
	leaq	(%rax,%r15), %rdi
	movq	%rsi, (%rsp)
	leaq	32(%rcx,%rdx), %rdx
	leaq	(%rdi,%r15), %rsi
	subq	$8, %r8
	movq	%rdx, -40(%rsp)
	leaq	248(%r9), %r12
	shrq	$3, %r8
	leaq	(%rsi,%r15), %rdx
	movq	%r12, -96(%rsp)
	addq	$1, %r8
	leaq	256(%r9), %r12
	movq	%r12, -104(%rsp)
	leaq	(%rdx,%r15), %r13
	leaq	264(%r9), %r12
	addq	%r13, %r15
	movq	%r12, -112(%rsp)
	leaq	32(%rax), %r12
	movq	%r8, 144(%rsp)
	xorl	%r8d, %r8d
	movq	%rcx, -120(%rsp)
	.p2align 4,,10
	.p2align 3
.L4:
	prefetcht0	(%rax)
	prefetcht0	(%rdi)
	prefetcht0	(%rsi)
	vbroadcastsd	(%r9), %ymm14
	prefetcht0	(%rdx)
	prefetcht0	0(%r13)
	movq	152(%rsp), %rcx
	prefetcht0	(%r15)
	addq	$1, %r8
	vmovapd	%ymm14, %ymm15
	vbroadcastsd	(%rcx), %ymm12
	movq	-120(%rsp), %rcx
	vmovapd	%ymm12, %ymm13
	vmovupd	(%rcx), %ymm4
	movq	128(%rsp), %rcx
	vfmadd132pd	%ymm4, %ymm0, %ymm15
	vfmadd132pd	%ymm4, %ymm0, %ymm13
	vmovupd	(%rcx), %ymm1
	movq	136(%rsp), %rcx
	vfmadd132pd	%ymm1, %ymm0, %ymm14
	vfmadd132pd	%ymm1, %ymm0, %ymm12
	vbroadcastsd	(%rcx), %ymm10
	movq	120(%rsp), %rcx
	vmovapd	%ymm10, %ymm11
	vfmadd132pd	%ymm1, %ymm0, %ymm10
	vfmadd132pd	%ymm4, %ymm0, %ymm11
	vbroadcastsd	(%rcx), %ymm3
	movq	112(%rsp), %rcx
	vfmadd132pd	%ymm3, %ymm0, %ymm4
	vmovapd	%ymm4, %ymm8
	vfmadd132pd	%ymm3, %ymm0, %ymm1
	vmovupd	(%rcx), %ymm4
	movq	104(%rsp), %rcx
	vbroadcastsd	(%rcx), %ymm2
	movq	96(%rsp), %rcx
	vfmadd231pd	%ymm4, %ymm2, %ymm15
	vmovupd	(%rcx), %ymm3
	movq	88(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm2, %ymm14
	vbroadcastsd	(%rcx), %ymm7
	movq	80(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm7, %ymm12
	vfmadd231pd	%ymm4, %ymm7, %ymm13
	vbroadcastsd	(%rcx), %ymm5
	movq	72(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm5, %ymm10
	vfmadd231pd	%ymm4, %ymm5, %ymm11
	vbroadcastsd	(%rcx), %ymm2
	movq	64(%rsp), %rcx
	vfmadd231pd	%ymm4, %ymm2, %ymm8
	vfmadd132pd	%ymm2, %ymm1, %ymm3
	vbroadcastsd	(%rcx), %ymm2
	movq	56(%rsp), %rcx
	vmovupd	(%rcx), %ymm4
	movq	48(%rsp), %rcx
	vfmadd231pd	%ymm4, %ymm2, %ymm15
	vmovupd	(%rcx), %ymm1
	movq	40(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm2, %ymm14
	vbroadcastsd	(%rcx), %ymm9
	movq	32(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm9, %ymm12
	vfmadd231pd	%ymm4, %ymm9, %ymm13
	vbroadcastsd	(%rcx), %ymm5
	movq	24(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm5, %ymm10
	vfmadd231pd	%ymm4, %ymm5, %ymm11
	vbroadcastsd	(%rcx), %ymm7
	movq	16(%rsp), %rcx
	vfmadd132pd	%ymm7, %ymm3, %ymm1
	vfmadd132pd	%ymm7, %ymm8, %ymm4
	vbroadcastsd	(%rcx), %ymm3
	movq	8(%rsp), %rcx
	vmovupd	(%rcx), %ymm2
	movq	(%rsp), %rcx
	vfmadd231pd	%ymm2, %ymm3, %ymm15
	vmovupd	(%rcx), %ymm6
	movq	-8(%rsp), %rcx
	vfmadd231pd	%ymm6, %ymm3, %ymm14
	vbroadcastsd	(%rcx), %ymm9
	movq	-16(%rsp), %rcx
	vfmadd231pd	%ymm2, %ymm9, %ymm13
	vfmadd231pd	%ymm6, %ymm9, %ymm12
	vbroadcastsd	(%rcx), %ymm5
	movq	-24(%rsp), %rcx
	vfmadd231pd	%ymm2, %ymm5, %ymm11
	vfmadd132pd	%ymm5, %ymm10, %ymm6
	vbroadcastsd	(%rcx), %ymm7
	movq	-32(%rsp), %rcx
	vfmadd231pd	%ymm2, %ymm7, %ymm4
	vfmadd132pd	%ymm7, %ymm1, %ymm2
	vmovapd	%ymm4, %ymm8
	vmovupd	(%r14), %ymm4
	vbroadcastsd	(%rcx), %ymm1
	movq	-40(%rsp), %rcx
	vfmadd231pd	%ymm4, %ymm1, %ymm15
	vmovupd	(%rcx), %ymm3
	movq	-48(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm1, %ymm14
	vbroadcastsd	(%rcx), %ymm9
	movq	-56(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm9, %ymm12
	vfmadd231pd	%ymm4, %ymm9, %ymm13
	vbroadcastsd	(%rcx), %ymm5
	movq	-64(%rsp), %rcx
	vfmadd231pd	%ymm3, %ymm5, %ymm6
	vfmadd231pd	%ymm4, %ymm5, %ymm11
	vbroadcastsd	(%rcx), %ymm7
	movq	-72(%rsp), %rcx
	vfmadd132pd	%ymm7, %ymm8, %ymm4
	vfmadd231pd	%ymm3, %ymm7, %ymm2
	vbroadcastsd	(%rcx), %ymm10
	movq	-80(%rsp), %rcx
	vmovupd	(%rcx), %ymm1
	movq	-88(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm10, %ymm15
	vmovupd	(%rcx), %ymm5
	movq	-96(%rsp), %rcx
	vfmadd132pd	%ymm5, %ymm14, %ymm10
	vmovupd	(%r12), %ymm14
	vaddpd	%ymm10, %ymm14, %ymm10
	vbroadcastsd	(%rcx), %ymm9
	movq	-104(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm9, %ymm13
	vfmadd132pd	%ymm5, %ymm12, %ymm9
	vmovupd	(%rbx), %ymm12
	vaddpd	%ymm9, %ymm12, %ymm9
	vbroadcastsd	(%rcx), %ymm8
	movq	-112(%rsp), %rcx
	vfmadd231pd	%ymm1, %ymm8, %ymm11
	vfmadd132pd	%ymm8, %ymm6, %ymm5
	vbroadcastsd	(%rcx), %ymm7
	vfmadd231pd	%ymm1, %ymm7, %ymm4
	vfmadd132pd	%ymm1, %ymm2, %ymm7
	vmovupd	(%rax), %ymm2
	vmovupd	(%rdi), %ymm1
	vaddpd	%ymm15, %ymm2, %ymm15
	vaddpd	%ymm13, %ymm1, %ymm13
	vmovupd	%ymm15, (%rax)
	vmovupd	%ymm10, (%r12)
	vmovupd	%ymm13, (%rdi)
	vmovupd	%ymm9, (%rbx)
	vmovupd	(%rsi), %ymm3
	vmovupd	(%r11), %ymm6
	vmovupd	(%rdx), %ymm2
	vaddpd	%ymm11, %ymm3, %ymm11
	vmovupd	(%r10), %ymm1
	vaddpd	%ymm5, %ymm6, %ymm5
	vaddpd	%ymm4, %ymm2, %ymm4
	vaddpd	%ymm7, %ymm1, %ymm7
	vmovupd	%ymm11, (%rsi)
	vmovupd	%ymm5, (%r11)
	vmovupd	%ymm4, (%rdx)
	vmovupd	%ymm7, (%r10)
	cmpq	144(%rsp), %r8
	jne	.L4
	vzeroupper
.L5:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1081:
	.size	hpl_dgemm_kernel_d8x6, .-hpl_dgemm_kernel_d8x6
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",@progbits
