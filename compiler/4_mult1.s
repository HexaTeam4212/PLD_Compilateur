.text
.global main
main:
        pushq %rbp
        movq %rsp, %rbp
BB0:
        movq $42, -32(%rbp)
        movq -32(%rbp), %rax
        movq %rax, -8(%rbp)
        movq $25, -40(%rbp)
        movq -40(%rbp), %rax
        movq %rax, -24(%rbp)
        movq $51, -56(%rbp)
        movq $5, -64(%rbp)
        movq -56(%rbp), %rdx
        movq -64(%rbp), %rax
        imul %rdx, %rax
        movq  %rax, -48(%rbp)
        movq -48(%rbp), %rax
        movq %rax, -16(%rbp)
        movq -16(%rbp), %rax
endmain:
        popq %rbp
        ret
		