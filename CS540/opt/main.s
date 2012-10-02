	.file	"main.c"
	.text
	.align 2
.globl _sub
	.def	_sub;	.scl	2;	.type	32;	.endef
_sub:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$2, (%eax)
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	call	__alloca
	call	___main
	movl	$1, -4(%ebp)
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_sub
	movl	$0, %eax
	leave
	ret
