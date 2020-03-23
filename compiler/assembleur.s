.text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp
BB0:
	movq $42, -16(%rbp)
	movq -16(%rbp), %rax
	movq %eax, -8(%rbp)
	movq $27, -24(%rbp)
	movq -24(%rbp), %rax
	movq %eax, -8(%rbp)
	movq $2, -40(%rbp)
	movq $2, -48(%rbp)
	movq -40(%rbp), %rdx
	movq -48(%rbp), %rax
	addq %rdx, %rax
	movq  %rax,-40(%rbp)
	movq -32(%rbp), %rax
	movq %eax, -8(%rbp)
	movq -8(%rbp), %rax
endmain:
	popq %rbp
	ret
