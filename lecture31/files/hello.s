	.file	"pic.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello World!"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	call	.L2
.L2:
	popl	%ebx
	addl	$_GLOBAL_OFFSET_TABLE_+[.-.L2], %ebx
	andl	$-16, %esp
	subl	$12, %esp
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	call	printf@PLT
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.3 (SuSE Linux)"
