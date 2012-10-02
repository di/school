	.file	"loop.c"
	.text
	.p2align 4,,15
.globl loop
	.type	loop, @function
loop:
.LFB2:
	testl	%ecx, %ecx
	jle	.L5
	xorl	%r8d, %r8d
	xorl	%eax, %eax
	.p2align 4,,7
.L4:
	movsd	(%rsi,%rax,8), %xmm0
	addl	$1, %r8d
	addsd	(%rdx,%rax,8), %xmm0
	movsd	%xmm0, (%rdi,%rax,8)
	addq	$1, %rax
	cmpl	%ecx, %r8d
	jne	.L4
.L5:
	rep ; ret
.LFE2:
	.size	loop, .-loop
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x0
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 4.2.3 (Ubuntu 4.2.3-2ubuntu7)"
	.section	.note.GNU-stack,"",@progbits
