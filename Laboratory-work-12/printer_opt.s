	.file	"printer.c"
	.text
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	call	connect_printer@PLT
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	PQstatus@PLT
	movl	%eax, %r8d
	movl	$1, %eax
	testl	%r8d, %r8d
	je	.L7
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	add_printer@PLT
	movq	%rbp, %rdi
	call	get_printer@PLT
	movq	%rbp, %rdi
	call	PQfinish@PLT
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
