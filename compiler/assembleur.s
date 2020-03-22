.text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp
BB0:
	movq $42, -16(%rbp)
	movq -16(%rbp), %rax
	movq %eax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %eax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %eax, -8(%rbp)
	movq -8(%rbp), %rax
endmain:
	popq %rbp
	ret
