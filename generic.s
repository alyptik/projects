	.file	"generic.c"
	.text
	.section	.rodata
.LC2:
	.string	"\"intmax_t\" i"
.LC3:
	.string	"long int"
.LC4:
	.string	"\"ptrdiff_t\" p"
.LC5:
	.string	"unsigned long int"
.LC6:
	.string	"\"size_t\" s"
	.align 8
.LC7:
	.string	"%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n%30s is '%s'\n\n"
.LC8:
	.string	"complex long double"
.LC9:
	.string	"\"complex long double\" z"
.LC10:
	.string	"pointer to int"
.LC11:
	.string	"\"array of int\" ai[3]"
.LC12:
	.string	"unsigned int"
.LC13:
	.string	"\"0x7FFFFFFFU\""
.LC14:
	.string	"\"0xFFFFFFFF\""
.LC15:
	.string	"int"
.LC16:
	.string	"\"0x7FFFFFFF\""
.LC17:
	.string	"\"character\" constant '0'"
.LC18:
	.string	"\"4.0 + 3.0i\""
	.align 8
.LC19:
	.string	"%20s has an imaginary part of "
.LC20:
	.string	"'%Lf'"
.LC21:
	.string	"%20s has a real part of "
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -20(%rbp)
	movl	$0, -12(%rbp)
	fldt	.LC0(%rip)
	fstpt	-64(%rbp)
	fldt	.LC1(%rip)
	fstpt	-48(%rbp)
	subq	$8, %rsp
	leaq	.LC8(%rip), %rax
	pushq	%rax
	leaq	.LC9(%rip), %rax
	pushq	%rax
	leaq	.LC10(%rip), %rax
	pushq	%rax
	leaq	.LC11(%rip), %rax
	pushq	%rax
	leaq	.LC12(%rip), %rax
	pushq	%rax
	leaq	.LC13(%rip), %rax
	pushq	%rax
	leaq	.LC12(%rip), %rax
	pushq	%rax
	leaq	.LC14(%rip), %rax
	pushq	%rax
	leaq	.LC15(%rip), %rax
	pushq	%rax
	leaq	.LC16(%rip), %rax
	pushq	%rax
	leaq	.LC15(%rip), %rax
	pushq	%rax
	leaq	.LC17(%rip), %rax
	pushq	%rax
	leaq	.LC3(%rip), %rax
	pushq	%rax
	leaq	.LC2(%rip), %r9
	leaq	.LC3(%rip), %r8
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$112, %rsp
	leaq	.LC18(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC19(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	fldt	.LC1(%rip)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC18(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC21(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	fldt	.LC0(%rip)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 16
.LC0:
	.long	0
	.long	-2147483648
	.long	16385
	.long	0
	.align 16
.LC1:
	.long	0
	.long	-1073741824
	.long	16384
	.long	0
	.ident	"GCC: (Gentoo 13.2.1_p20240210 p13) 13.2.1 20240210"
	.section	.note.GNU-stack,"",@progbits
