        .file   "abs.c"
        .text
        .align 2
        .align 16
.globl absval
        .type   absval, @function
absval:
        pushl   %ebp
        movl    %esp, %ebp
        movl    8(%ebp), %eax
        testl   %eax, %eax
        js      L3
L2:
        popl    %ebp
        ret
        .align 16
L3:
        negl    %eax
        jmp     L2
