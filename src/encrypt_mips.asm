# Author: Sophia Garcia
# Date: Sept 29, 2023
# Description: A simple input logic gate calculator; later to be refurbished into the CryptSnap game

.data
	res: 	.byte	16	#for four digit num plus a null pointer end	
	switch: 	.word 	NONE, _XNOR, _XOR, _NOR, _NAND, _OR, _AND
	res_arr: 	.byte	0, 0, 0, 0
	intro: 	.asciiz 	"Welcome to CryptSnap!\nToday learn about the 6 different gates!\nAND, OR, NAND, NOR, XOR, XNOR\n"
	prompt: 	.asciiz 	"Solve integers 1000 and 1010 through the gate "
	boo_:	.asciiz	"\nBoo fail\n"
	yay_: 	.asciiz	"\nYay you got it!\n"
	_and: 	.asciiz 	"AND:"
	_or: 	.asciiz 	"OR:"
	_nand:	.asciiz 	"NAND:"
	_nor: 	.asciiz 	"NOR:"
	_xor: 	.asciiz 	"XOR:"
	_xnor: 	.asciiz 	"XNOR:"
	

.text
	addi 	$s0, $0, 0x8
	addi 	$s1, $0, 0xA
	addi	$s2, $0, 0x0
	li 	$s3, 6
	
	li 	$v0, 4
	la 	$a0, intro
	syscall 		
	
	j 	gate_loop1
		
	end:	#end program
		li 	$v0, 10
		syscall
	boo:	#user failed
		li	$v0, 4
		la	$a0, boo_
		syscall
		li	$t7, 1
		jr 	$ra
	yay:	#user success
		li	$v0, 4
		la	$a0, yay_
		syscall
		addi	$s3, $s3, -1
		j	gate_loop1

	for_translation:	#translated users char input to an array of integers						
		lb	$t0, 3($a1)
		andi	$t1, $t0, 0xF
		sb	$t1, 3($a0)
		lb	$t0, 2($a1)							# # # negative indexing on all the $a1 loads was going backwards into the previous word space. This was your main bug
		andi	$t1, $t0, 0xF
		sb	$t1, 2($a0)
		lb	$t0, 1($a1)
		andi	$t1, $t0, 0xF
		sb	$t1, 1($a0)
		lb	$t0, 0($a1)
		andi	$t1, $t0, 0xF
		sb	$t1, 0($a0)
		jr	$ra
		
	compare_:	#compares user input with actual calculated result			
		lb	$t2, 0($a0)
		srl	$t3, $s2, 3
		andi	$t3, $t3, 0x1
		bne	$t2, $t3, boo
		lb	$t2, 1($a0)
		srl	$t3, $s2, 2
		andi	$t3, $t3, 0x1
		bne	$t2, $t3, boo
		lb	$t2, 2($a0)
		srl	$t3, $s2, 1
		andi	$t3, $t3, 0x1
		bne	$t2, $t3, boo
		lb	$t2, 3($a0)
		srl	$t3, $s2, 0
		andi	$t3, $t3, 0x1
		bne	$t2, $t3, boo
		j	yay
		
	gate_loop1:
		li 	$v0, 4
		la 	$a0, prompt
		syscall	
		addi	$t1, $0, 0
		mul 	$t1, $s3, 4  	# (tmp = n*4)	      	
		lw 	$t1, switch($t1)   	
		jr	$t1
		
	#the following cases translate the code and the key through a specific logic gate (AND to XNOR)	
	_AND:
		li 	$v0, 4
		la 	$a0, _and
		syscall
		and 	$s2, $s0, $s1
		j 	gate_loop2
	_OR:
		li 	$v0, 4
		la 	$a0, _or
		syscall
		or 	$s2, $s0, $s1
		j 	gate_loop2
	_NAND:
		li 	$v0, 4
		la 	$a0, _nand
		syscall
		and 	$t0, $s0, $s1
		not 	$s2, $t0	
		j 	gate_loop2		
	_NOR:
		li 	$v0, 4
		la 	$a0, _nor
		syscall
		nor 	$s2, $s0, $s1
		j 	gate_loop2		
	_XOR:
		li 	$v0, 4
		la 	$a0, _xor
		syscall
		xor 	$s2, $s0, $s1
		j 	gate_loop2
	_XNOR:
		li 	$v0, 4
		la 	$a0, _xnor
		syscall
		xor 	$t0, $s0, $s1
		not 	$s2, $t0		
		j 	gate_loop2
	NONE:
		j 	end	# this one ends the code/level	
	
	gate_loop2:
		li 	$v0, 8
		la 	$a0, res	#ask user what they think for ...
		li 	$a1, 5
		syscall
		
		la	$a0, res_arr
		la	$a1, res
		jal 	for_translation	# goes through gate per the array (AND = 6 then NONE = 0)			
		
		la 	$a0, res_arr
		addi	$a1, $s2, 0
		li	$a2, 0
		jal	compare_				
		
		addi	$s3, $s3, -1
		j	gate_loop1
