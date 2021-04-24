	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 1
	.globl	_new_state              ## -- Begin function new_state
	.p2align	4, 0x90
_new_state:                             ## @new_state
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
                                        ## kill: def $dil killed $dil killed $edi
	movb	%dil, -1(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$32, %edi
	callq	_malloc
	movq	%rax, -32(%rbp)
	movb	-1(%rbp), %cl
	movq	-32(%rbp), %rax
	movb	%cl, (%rax)
	movq	-16(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rax, 8(%rdx)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rax, 16(%rdx)
	movq	-32(%rbp), %rax
	movl	$0, 24(%rax)
	movq	-32(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_new_frag               ## -- Begin function new_frag
	.p2align	4, 0x90
_new_frag:                              ## @new_frag
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_new_list               ## -- Begin function new_list
	.p2align	4, 0x90
_new_list:                              ## @new_list
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	$0, (%rax)
	movq	-16(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_merge                  ## -- Begin function merge
	.p2align	4, 0x90
_merge:                                 ## @merge
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
LBB3_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-8(%rbp), %rax
	cmpq	$0, (%rax)
	je	LBB3_3
## %bb.2:                               ##   in Loop: Header=BB3_1 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB3_1
LBB3_3:
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-24(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_patch                  ## -- Begin function patch
	.p2align	4, 0x90
_patch:                                 ## @patch
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$0, -8(%rbp)
	je	LBB4_4
## %bb.2:                               ##   in Loop: Header=BB4_1 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, (%rcx)
## %bb.3:                               ##   in Loop: Header=BB4_1 Depth=1
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB4_1
LBB4_4:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_add_char               ## -- Begin function add_char
	.p2align	4, 0x90
_add_char:                              ## @add_char
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
                                        ## kill: def $sil killed $sil killed $esi
                                        ## kill: def $dil killed $dil killed $edi
	movb	%dil, -1(%rbp)
	andb	$1, %sil
	movb	%sil, -2(%rbp)
	testb	$1, -2(%rbp)
	jne	LBB5_2
## %bb.1:
	jmp	LBB5_2
LBB5_2:
	xorl	%eax, %eax
	movl	%eax, %ecx
	movq	_op_ptr(%rip), %rdx
	movq	%rdx, %rsi
	addq	$1, %rsi
	movq	%rsi, _op_ptr(%rip)
	movb	$-3, (%rdx)
	movsbl	-1(%rbp), %edi
	movq	%rcx, %rsi
	movq	%rcx, %rdx
	callq	_new_state
	movq	%rax, -16(%rbp)
	movq	_out_ptr(%rip), %rax
	movq	%rax, %rcx
	addq	$16, %rcx
	movq	%rcx, _out_ptr(%rip)
	movq	-16(%rbp), %rdi
	movq	-16(%rbp), %rcx
	addq	$8, %rcx
	movq	%rdi, -40(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdi
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	callq	_new_list
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movq	%rax, %rsi
	callq	_new_frag
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-32(%rbp), %rax
	movq	-48(%rbp), %rcx         ## 8-byte Reload
	movq	%rax, (%rcx)
	movq	-24(%rbp), %rax
	movq	%rax, 8(%rcx)
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_parse                  ## -- Begin function parse
	.p2align	4, 0x90
_parse:                                 ## @parse
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -8(%rbp)
LBB6_1:                                 ## =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx), %edx
	cmpl	$0, %edx
	movb	%al, -65(%rbp)          ## 1-byte Spill
	je	LBB6_3
## %bb.2:                               ##   in Loop: Header=BB6_1 Depth=1
	movq	-8(%rbp), %rax
	movsbl	(%rax), %ecx
	cmpl	$47, %ecx
	setne	%dl
	movb	%dl, -65(%rbp)          ## 1-byte Spill
LBB6_3:                                 ##   in Loop: Header=BB6_1 Depth=1
	movb	-65(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB6_4
	jmp	LBB6_5
LBB6_4:                                 ##   in Loop: Header=BB6_1 Depth=1
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -8(%rbp)
	jmp	LBB6_1
LBB6_5:
	movq	-8(%rbp), %rax
	cmpb	$0, (%rax)
	jne	LBB6_7
## %bb.6:
	jmp	LBB6_20
LBB6_7:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -8(%rbp)
	movb	$0, -10(%rbp)
LBB6_8:                                 ## =>This Inner Loop Header: Depth=1
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	addq	$1, %rcx
	movq	%rcx, -8(%rbp)
	movb	(%rax), %dl
	movb	%dl, -9(%rbp)
	cmpb	$0, %dl
	je	LBB6_20
## %bb.9:                               ##   in Loop: Header=BB6_8 Depth=1
	movsbl	-9(%rbp), %eax
	movl	%eax, %ecx
	addl	$-40, %ecx
	subl	$4, %ecx
	movl	%eax, -72(%rbp)         ## 4-byte Spill
	jb	LBB6_17
	jmp	LBB6_21
LBB6_21:                                ##   in Loop: Header=BB6_8 Depth=1
	movl	-72(%rbp), %eax         ## 4-byte Reload
	subl	$47, %eax
	je	LBB6_10
	jmp	LBB6_22
LBB6_22:                                ##   in Loop: Header=BB6_8 Depth=1
	movl	-72(%rbp), %eax         ## 4-byte Reload
	subl	$63, %eax
	je	LBB6_17
	jmp	LBB6_23
LBB6_23:                                ##   in Loop: Header=BB6_8 Depth=1
	movl	-72(%rbp), %eax         ## 4-byte Reload
	subl	$124, %eax
	je	LBB6_17
	jmp	LBB6_18
LBB6_10:
	jmp	LBB6_11
LBB6_11:                                ## =>This Inner Loop Header: Depth=1
	leaq	_op_stack(%rip), %rax
	cmpq	%rax, _op_ptr(%rip)
	je	LBB6_16
## %bb.12:                              ##   in Loop: Header=BB6_11 Depth=1
	movq	_op_ptr(%rip), %rax
	movq	%rax, %rcx
	addq	$-1, %rcx
	movq	%rcx, _op_ptr(%rip)
	movb	-1(%rax), %dl
	movb	%dl, -11(%rbp)
	movsbl	-11(%rbp), %esi
	cmpl	$-3, %esi
	jne	LBB6_14
## %bb.13:                              ##   in Loop: Header=BB6_11 Depth=1
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	_out_ptr(%rip), %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, _out_ptr(%rip)
	movq	-16(%rcx), %rdx
	movq	%rdx, -32(%rbp)
	movq	-8(%rcx), %rcx
	movq	%rcx, -24(%rbp)
	movq	_out_ptr(%rip), %rcx
	movq	%rcx, %rdx
	addq	$-16, %rdx
	movq	%rdx, _out_ptr(%rip)
	movq	-16(%rcx), %rdx
	movq	%rdx, -48(%rbp)
	movq	-8(%rcx), %rcx
	movq	%rcx, -40(%rbp)
	movq	-24(%rbp), %rdi
	movq	-48(%rbp), %rsi
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	callq	_patch
	movq	_out_ptr(%rip), %rcx
	movq	%rcx, %rdx
	addq	$16, %rdx
	movq	%rdx, _out_ptr(%rip)
	movq	-32(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rcx, -88(%rbp)         ## 8-byte Spill
	callq	_new_frag
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-64(%rbp), %rax
	movq	-88(%rbp), %rcx         ## 8-byte Reload
	movq	%rax, (%rcx)
	movq	-56(%rbp), %rax
	movq	%rax, 8(%rcx)
	jmp	LBB6_15
LBB6_14:                                ##   in Loop: Header=BB6_11 Depth=1
	movsbl	-11(%rbp), %esi
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB6_15:                                ##   in Loop: Header=BB6_11 Depth=1
	jmp	LBB6_11
LBB6_16:
	jmp	LBB6_20
LBB6_17:                                ##   in Loop: Header=BB6_8 Depth=1
	jmp	LBB6_19
LBB6_18:                                ##   in Loop: Header=BB6_8 Depth=1
	movb	-9(%rbp), %al
	movb	-10(%rbp), %cl
	andb	$1, %cl
	movsbl	%al, %edi
	movzbl	%cl, %esi
	callq	_add_char
LBB6_19:                                ##   in Loop: Header=BB6_8 Depth=1
	jmp	LBB6_8
LBB6_20:
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_debug                  ## -- Begin function debug
	.p2align	4, 0x90
_debug:                                 ## @debug
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	_out_ptr(%rip), %rax
	leaq	_out_stack(%rip), %rcx
	subq	%rcx, %rax
	sarq	$4, %rax
	leaq	L_.str.2(%rip), %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.zerofill __DATA,__bss,_op_ptr,8,3      ## @op_ptr
.zerofill __DATA,__bss,_out_ptr,8,3     ## @out_ptr
.zerofill __DATA,__bss,_op_stack,1000,4 ## @op_stack
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"concat\n"

L_.str.1:                               ## @.str.1
	.asciz	"error %d\n"

L_.str.2:                               ## @.str.2
	.asciz	"stack: %ld\n"

.zerofill __DATA,__bss,_out_stack,16000,4 ## @out_stack
.subsections_via_symbols
