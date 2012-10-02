	.file	"loop.c"
	.text
.globl loop
	.type	loop, @function
loop:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	$0, -16(%ebp)
.L2:
	movl	-16(%ebp), %eax
	cmpl	20(%ebp), %eax
	jge	.L1
	movl	-16(%ebp), %eax
	leal	0(,%eax,8), %esi
	movl	8(%ebp), %edi
	movl	-16(%ebp), %eax
	leal	0(,%eax,8), %ebx
	movl	12(%ebp), %ecx
	movl	-16(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	fldl	(%ebx,%ecx)
	faddl	(%edx,%eax)
	fstpl	(%esi,%edi)
	leal	-16(%ebp), %eax
	incl	(%eax)
	jmp	.L2
.L1:
	addl	$4, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	loop, .-loop
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.4.6 (Gentoo 3.4.6-r1, ssp-3.4.5-1.0, pie-8.7.9)"
