/*
        sigma(n) = 1 + 2 + 3 + ... + n
 */
        
        .text
        .globl  sigma
sigma:
        push    %rbp
        mov     %rsp, %rbp
        sub     $0, %rsp        /* can be omitted */

        mov     $0, %eax
        mov     $1, %ecx
        
.loop:
        cmp     %edi, %ecx
        jg     .end            /* jump if greater */

        add     %ecx, %eax
        add     $1, %ecx
        jmp     .loop
.end:
        leave
        ret


        
