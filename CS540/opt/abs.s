	.file	"abs.c"
	.text
.globl absval
	.type	absval, @function
absval:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%edx, %eax
	xorl	8(%ebp), %eax
	subl	%edx, %eax
	popl	%ebp
	ret
	.size	absval, .-absval
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.1 (Mandrake Linux 9.2 3.3.1-2mdk)"
