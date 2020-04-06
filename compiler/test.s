.text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp
	jmp BB0
BB0:
	movq $13, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	movq $0, -40(%rbp)
	movq -40(%rbp), %rax
	cmpq -8(%rbp), %rax
	sete %al
	movzbq %al, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	jmp endmain
endmain:
	popq %rbp
	ret
