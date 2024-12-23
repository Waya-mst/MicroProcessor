	.file	1 "rtetest.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	softfloat
	.module	nooddspreg
	.text
 #APP
	.global __start__		
	__start__:			
		lui $sp, 0		
		ori $sp, 0xff00		
		li $gp, 0		
		li $k0, 0x02000101	
		mtc0 $k0, $12		
	
 #NO_APP
	.align	2
	.globl	__reset__
	.set	nomips16
	.set	nomicromips
	.ent	__reset__
	.type	__reset__, @function
__reset__:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	lui	$2,%hi(__sbackup)
	addiu	$2,$2,%lo(__sbackup)
	sw	$2,0($fp)
	lui	$2,%hi(__sdata)
	addiu	$2,$2,%lo(__sdata)
	sw	$2,4($fp)
	b	$L2
$L3:
	lw	$3,0($fp)
	#nop
	addiu	$2,$3,4
	sw	$2,0($fp)
	lw	$2,4($fp)
	#nop
	addiu	$4,$2,4
	sw	$4,4($fp)
	lw	$3,0($3)
	#nop
	sw	$3,0($2)
$L2:
	lw	$3,4($fp)
	lui	$2,%hi(__edata)
	addiu	$2,$2,%lo(__edata)
	sltu	$2,$3,$2
	bne	$2,$0,$L3
	lui	$2,%hi(__sbss)
	addiu	$2,$2,%lo(__sbss)
	sw	$2,4($fp)
	b	$L4
$L5:
	lw	$2,4($fp)
	#nop
	sw	$0,0($2)
	lw	$2,4($fp)
	#nop
	addiu	$2,$2,4
	sw	$2,4($fp)
$L4:
	lw	$3,4($fp)
	lui	$2,%hi(__ebss)
	addiu	$2,$2,%lo(__ebss)
	sltu	$2,$3,$2
	bne	$2,$0,$L5
 #APP
 # 24 "crt0.c" 1
	j main
 # 0 "" 2
 #NO_APP
	.set	noreorder
	nop
	.set	reorder
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	jr	$31
	.end	__reset__
	.size	__reset__, .-__reset__
 #APP
	nop			
		nop			
		nop			
		nop			
		nop			
	__vector__:			
	.set noat			
		move $k0, $sp		
		lui $sp, 0		
		ori $sp, 0xc000		
		addiu $sp, $sp, -128	
		sw $k0, 124($sp)	
		sw $at, 120($sp)	
	.set at			
		sw $v0, 116($sp)	
		sw $v1, 112($sp)	
		sw $a0, 108($sp)	
		sw $a1, 104($sp)	
		sw $a2, 100($sp)	
		sw $a3,  96($sp)	
		sw $t0,  92($sp)	
		sw $t1,  88($sp)	
		sw $t2,  84($sp)	
		sw $t3,  80($sp)	
		sw $t4,  76($sp)	
		sw $t5,  72($sp)	
		sw $t6,  68($sp)	
		sw $t7,  64($sp)	
		sw $s0,  60($sp)	
		sw $s1,  56($sp)	
		sw $s2,  52($sp)	
		sw $s3,  48($sp)	
		sw $s4,  44($sp)	
		sw $s5,  40($sp)	
		sw $s6,  36($sp)	
		sw $s7,  32($sp)	
		sw $t8,  28($sp)	
		sw $t9,  24($sp)	
		sw $gp,  20($sp)	
		sw $s8,  16($sp)	
		sw $ra,  12($sp)	
		jal interrupt_handler	
		lw $ra,  12($sp)	
		lw $s8,  16($sp)	
		lw $gp,  20($sp)	
		lw $t9,  24($sp)	
		lw $t8,  28($sp)	
		lw $s7,  32($sp)	
		lw $s6,  36($sp)	
		lw $s5,  40($sp)	
		lw $s4,  44($sp)	
		lw $s3,  48($sp)	
		lw $s2,  52($sp)	
		lw $s1,  56($sp)	
		lw $s0,  60($sp)	
		lw $t7,  64($sp)	
		lw $t6,  68($sp)	
		lw $t5,  72($sp)	
		lw $t4,  76($sp)	
		lw $t3,  80($sp)	
		lw $t2,  84($sp)	
		lw $t1,  88($sp)	
		lw $t0,  92($sp)	
		lw $a3,  96($sp)	
		lw $a2, 100($sp)	
		lw $a1, 104($sp)	
		lw $a0, 108($sp)	
		lw $v1, 112($sp)	
		lw $v0, 116($sp)	
	.set noat			
		lw $at, 120($sp)	
		lw $k0, 124($sp)	
		move $sp, $k0		
		mfc0 $k1, $14		
		nop			
		rfe			
		nop			
		jr $k1			
		nop			
	
 #NO_APP
	.align	2
	.globl	memcpy
	.set	nomips16
	.set	nomicromips
	.ent	memcpy
	.type	memcpy, @function
memcpy:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	sw	$6,24($fp)
	lw	$2,16($fp)
	nop
	sw	$2,0($fp)
	lw	$2,20($fp)
	nop
	sw	$2,4($fp)
	b	$L7
	nop

$L8:
	lw	$3,4($fp)
	nop
	addiu	$2,$3,1
	sw	$2,4($fp)
	lw	$2,0($fp)
	nop
	addiu	$4,$2,1
	sw	$4,0($fp)
	lb	$3,0($3)
	nop
	sb	$3,0($2)
$L7:
	lw	$2,24($fp)
	nop
	addiu	$3,$2,-1
	sw	$3,24($fp)
	bne	$2,$0,$L8
	nop

	lw	$2,16($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	memcpy
	.size	memcpy, .-memcpy
	.globl	font8x8
	.rdata
	.align	2
	.type	font8x8, @object
	.size	font8x8, 768
font8x8:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	95
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	100
	.byte	60
	.byte	38
	.byte	100
	.byte	60
	.byte	38
	.byte	36
	.byte	0
	.byte	38
	.byte	73
	.byte	73
	.byte	127
	.byte	73
	.byte	73
	.byte	50
	.byte	0
	.byte	66
	.byte	37
	.byte	18
	.byte	8
	.byte	36
	.byte	82
	.byte	33
	.byte	0
	.byte	32
	.byte	80
	.byte	78
	.byte	85
	.byte	34
	.byte	88
	.byte	40
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	28
	.byte	34
	.byte	65
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	34
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	21
	.byte	21
	.byte	14
	.byte	14
	.byte	21
	.byte	21
	.byte	0
	.byte	0
	.byte	8
	.byte	8
	.byte	62
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	80
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	32
	.byte	16
	.byte	8
	.byte	4
	.byte	2
	.byte	1
	.byte	0
	.byte	0
	.byte	62
	.byte	65
	.byte	65
	.byte	65
	.byte	62
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	127
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	66
	.byte	97
	.byte	81
	.byte	73
	.byte	110
	.byte	0
	.byte	0
	.byte	0
	.byte	34
	.byte	65
	.byte	73
	.byte	73
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	20
	.byte	18
	.byte	127
	.byte	16
	.byte	0
	.byte	0
	.byte	0
	.byte	39
	.byte	73
	.byte	73
	.byte	73
	.byte	113
	.byte	0
	.byte	0
	.byte	0
	.byte	60
	.byte	74
	.byte	73
	.byte	72
	.byte	112
	.byte	0
	.byte	0
	.byte	0
	.byte	67
	.byte	33
	.byte	17
	.byte	13
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	54
	.byte	73
	.byte	73
	.byte	73
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	9
	.byte	73
	.byte	41
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	82
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	20
	.byte	20
	.byte	34
	.byte	0
	.byte	0
	.byte	0
	.byte	20
	.byte	20
	.byte	20
	.byte	20
	.byte	20
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	34
	.byte	20
	.byte	20
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	1
	.byte	89
	.byte	5
	.byte	2
	.byte	0
	.byte	0
	.byte	62
	.byte	65
	.byte	93
	.byte	85
	.byte	77
	.byte	81
	.byte	46
	.byte	0
	.byte	64
	.byte	124
	.byte	74
	.byte	9
	.byte	74
	.byte	124
	.byte	64
	.byte	0
	.byte	65
	.byte	127
	.byte	73
	.byte	73
	.byte	73
	.byte	73
	.byte	54
	.byte	0
	.byte	28
	.byte	34
	.byte	65
	.byte	65
	.byte	65
	.byte	65
	.byte	34
	.byte	0
	.byte	65
	.byte	127
	.byte	65
	.byte	65
	.byte	65
	.byte	34
	.byte	28
	.byte	0
	.byte	65
	.byte	127
	.byte	73
	.byte	73
	.byte	93
	.byte	65
	.byte	99
	.byte	0
	.byte	65
	.byte	127
	.byte	73
	.byte	9
	.byte	29
	.byte	1
	.byte	3
	.byte	0
	.byte	28
	.byte	34
	.byte	65
	.byte	73
	.byte	73
	.byte	58
	.byte	8
	.byte	0
	.byte	65
	.byte	127
	.byte	8
	.byte	8
	.byte	8
	.byte	127
	.byte	65
	.byte	0
	.byte	0
	.byte	65
	.byte	65
	.byte	127
	.byte	65
	.byte	65
	.byte	0
	.byte	0
	.byte	48
	.byte	64
	.byte	65
	.byte	65
	.byte	63
	.byte	1
	.byte	1
	.byte	0
	.byte	65
	.byte	127
	.byte	8
	.byte	12
	.byte	18
	.byte	97
	.byte	65
	.byte	0
	.byte	65
	.byte	127
	.byte	65
	.byte	64
	.byte	64
	.byte	64
	.byte	96
	.byte	0
	.byte	65
	.byte	127
	.byte	66
	.byte	12
	.byte	66
	.byte	127
	.byte	65
	.byte	0
	.byte	65
	.byte	127
	.byte	66
	.byte	12
	.byte	17
	.byte	127
	.byte	1
	.byte	0
	.byte	28
	.byte	34
	.byte	65
	.byte	65
	.byte	65
	.byte	34
	.byte	28
	.byte	0
	.byte	65
	.byte	127
	.byte	73
	.byte	9
	.byte	9
	.byte	9
	.byte	6
	.byte	0
	.byte	12
	.byte	18
	.byte	33
	.byte	33
	.byte	97
	.byte	82
	.byte	76
	.byte	0
	.byte	65
	.byte	127
	.byte	9
	.byte	9
	.byte	25
	.byte	105
	.byte	70
	.byte	0
	.byte	102
	.byte	73
	.byte	73
	.byte	73
	.byte	73
	.byte	73
	.byte	51
	.byte	0
	.byte	3
	.byte	1
	.byte	65
	.byte	127
	.byte	65
	.byte	1
	.byte	3
	.byte	0
	.byte	1
	.byte	63
	.byte	65
	.byte	64
	.byte	65
	.byte	63
	.byte	1
	.byte	0
	.byte	1
	.byte	15
	.byte	49
	.byte	64
	.byte	49
	.byte	15
	.byte	1
	.byte	0
	.byte	1
	.byte	31
	.byte	97
	.byte	20
	.byte	97
	.byte	31
	.byte	1
	.byte	0
	.byte	65
	.byte	65
	.byte	54
	.byte	8
	.byte	54
	.byte	65
	.byte	65
	.byte	0
	.byte	1
	.byte	3
	.byte	68
	.byte	120
	.byte	68
	.byte	3
	.byte	1
	.byte	0
	.byte	67
	.byte	97
	.byte	81
	.byte	73
	.byte	69
	.byte	67
	.byte	97
	.byte	0
	.byte	0
	.byte	0
	.byte	127
	.byte	65
	.byte	65
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	4
	.byte	8
	.byte	16
	.byte	32
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	65
	.byte	127
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	2
	.byte	1
	.byte	1
	.byte	2
	.byte	4
	.byte	0
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	52
	.byte	74
	.byte	74
	.byte	74
	.byte	60
	.byte	64
	.byte	0
	.byte	0
	.byte	65
	.byte	63
	.byte	72
	.byte	72
	.byte	72
	.byte	48
	.byte	0
	.byte	0
	.byte	60
	.byte	66
	.byte	66
	.byte	66
	.byte	36
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	72
	.byte	72
	.byte	73
	.byte	63
	.byte	64
	.byte	0
	.byte	0
	.byte	60
	.byte	74
	.byte	74
	.byte	74
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	72
	.byte	126
	.byte	73
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	38
	.byte	73
	.byte	73
	.byte	73
	.byte	63
	.byte	1
	.byte	0
	.byte	65
	.byte	127
	.byte	72
	.byte	4
	.byte	68
	.byte	120
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	68
	.byte	125
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	68
	.byte	61
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	127
	.byte	16
	.byte	24
	.byte	36
	.byte	66
	.byte	66
	.byte	0
	.byte	0
	.byte	64
	.byte	65
	.byte	127
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	66
	.byte	126
	.byte	2
	.byte	124
	.byte	2
	.byte	126
	.byte	64
	.byte	0
	.byte	66
	.byte	126
	.byte	68
	.byte	2
	.byte	66
	.byte	124
	.byte	64
	.byte	0
	.byte	0
	.byte	60
	.byte	66
	.byte	66
	.byte	66
	.byte	60
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	127
	.byte	73
	.byte	9
	.byte	9
	.byte	6
	.byte	0
	.byte	0
	.byte	6
	.byte	9
	.byte	9
	.byte	73
	.byte	127
	.byte	65
	.byte	0
	.byte	0
	.byte	66
	.byte	126
	.byte	68
	.byte	2
	.byte	2
	.byte	4
	.byte	0
	.byte	0
	.byte	100
	.byte	74
	.byte	74
	.byte	74
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	63
	.byte	68
	.byte	68
	.byte	32
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	62
	.byte	64
	.byte	64
	.byte	34
	.byte	126
	.byte	64
	.byte	2
	.byte	14
	.byte	50
	.byte	64
	.byte	50
	.byte	14
	.byte	2
	.byte	0
	.byte	2
	.byte	30
	.byte	98
	.byte	24
	.byte	98
	.byte	30
	.byte	2
	.byte	0
	.byte	66
	.byte	98
	.byte	20
	.byte	8
	.byte	20
	.byte	98
	.byte	66
	.byte	0
	.byte	1
	.byte	67
	.byte	69
	.byte	56
	.byte	5
	.byte	3
	.byte	1
	.byte	0
	.byte	0
	.byte	70
	.byte	98
	.byte	82
	.byte	74
	.byte	70
	.byte	98
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	54
	.byte	65
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	127
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	65
	.byte	54
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	8
	.byte	8
	.byte	16
	.byte	16
	.byte	24
	.byte	0
	.byte	-86
	.byte	85
	.byte	-86
	.byte	85
	.byte	-86
	.byte	85
	.byte	-86
	.byte	85
	.text
	.align	2
	.globl	interrupt_handler
	.set	nomips16
	.set	nomicromips
	.ent	interrupt_handler
	.type	interrupt_handler, @function
interrupt_handler:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	interrupt_handler
	.size	interrupt_handler, .-interrupt_handler
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	li	$2,65284			# 0xff04
	sw	$2,0($fp)
	li	$2,65304			# 0xff18
	sw	$2,4($fp)
$L12:
	lw	$2,0($fp)
	nop
	lw	$3,0($2)
	lw	$2,4($fp)
	nop
	sw	$3,0($2)
	b	$L12
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.4.0"
