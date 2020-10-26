	.file	"bubble_sort.c"
	.text
	.p2align 4,,15
	.globl	bubble_sort
	.type	bubble_sort, @function
bubble_sort:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L1
	leal	-1(%rsi), %r11d
	movl	$1, %r9d
	addq	$4, %rdi
	movq	%rdi, %r8
	leal	-2(%rsi), %r10d
	addq	$1, %r11
	cmpq	%r11, %r9
	je	.L1
	.p2align 4,,10
	.p2align 3
.L8:
	movl	%r10d, %eax
	addq	%r9, %rax
	leaq	(%rdi,%rax,4), %rsi
	movq	%r8, %rax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	-4(%r8), %edx
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L3
	movl	%ecx, -4(%r8)
	movl	%edx, (%rax)
.L3:
	addq	$4, %rax
	cmpq	%rsi, %rax
	jne	.L4
	addq	$1, %r9
	addq	$4, %r8
	subl	$1, %r10d
	cmpq	%r11, %r9
	jne	.L8
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	bubble_sort, .-bubble_sort
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
