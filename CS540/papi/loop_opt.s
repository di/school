	.file	"loop.c"
	.text
	.p2align 4,,15
.globl loop
	.type	loop, @function
loop:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	movl	16(%ebp), %ecx
	movl	8(%ebp), %esi
	pushl	%ebx
	movl	20(%ebp), %edx
	movl	12(%ebp), %ebx
	jmp	.L10
	.p2align 4,,7
.L12:
	fldl	(%ecx,%eax,8)
	faddl	(%ebx,%eax,8)
	fstpl	(%esi,%eax,8)
	incl	%eax
.L10:
	cmpl	%edx, %eax
	jl	.L12
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	loop, .-loop
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.4.6 (Gentoo 3.4.6-r1, ssp-3.4.5-1.0, pie-8.7.9)"
