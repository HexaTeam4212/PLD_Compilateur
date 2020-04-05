.text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp
	jmp BB0
BB0:
	movq $1, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	movq $0, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rax, -16(%rbp)
	movq $0, -40(%rbp)
	movq -8(%rbp), %rax
	cmpq -40(%rbp), %rax
	je BB2
	jmp BB1
BB1:
	movq $2, -48(%rbp)
	movq -48(%rbp), %rax
	movq %rax, -8(%rbp)
	jmp BB2
BB2:
	movq -8(%rbp), %rax
	jmp endmain
endmain:
	popq %rbp
	ret
