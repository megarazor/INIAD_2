        .text
        .globl  sigma
sigma:
        push    %rbp
        mov     %rsp, %rbp
        mov     %edi, -0x4(%rbp)
        mov     %esi, -0x8(%rbp)
        sub     $0, %rsp        /* can be omitted */

        mov     $0, %eax
        mov     -0x4(%rbp), %ecx
        
.loop:
        cmp     %esi, %ecx
        jg     .end            /* jump if greater */

        add     %ecx, %eax
        add     $1, %ecx
        jmp     .loop
.end:
        leave
        ret
