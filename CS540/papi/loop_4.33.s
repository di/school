	.file	"loop.c"
	.text
	.p2align 4,,15
.globl loop
	.type	loop, @function
loop:
	pushl	%ebp
	movl	%esp, %ebp
	movl	20(%ebp), %edx
	pushl	%esi
	movl	16(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	testl	%edx, %edx
	jle	.L4
	xorl	%eax, %eax
	.p2align 4,,7
	.p2align 3
.L3:
	fldl	(%ebx,%eax,8)
	faddl	(%ecx,%eax,8)
	fstpl	(%esi,%eax,8)
	addl	$1, %eax
	cmpl	%eax, %edx
	jg	.L3
.L4:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	loop, .-loop
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
