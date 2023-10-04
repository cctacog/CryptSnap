# Author: Sophia Garcia
# Date: Sept 29, 2023
# Description: A simple input logic gate calculator; later to be refurbished into the CryptSnap game

.data
	intro: 	.asciiz 	"Welcome to CryptSnap!\nToday learn about the 6 different gates!\nAND, OR, NAND, NOR, XOR, XNOR\n"
	prompt: 	.asciiz 	"Solve integers 1000 and 1010 through the gate "
	boo_:	.asciiz	"Boo fail\n"
	yay_: 	.asciiz	"Yay you got it\n!"
	res: 	.space	6 	#for three digit num plus a null pointer end
	_and: 	.asciiz 	"AND:"
	_or: 	.asciiz 	"OR:"
	_nand:	.asciiz 	"NAND:"
	_nor: 	.asciiz 	"NOR:"
	_xor: 	.asciiz 	"XOR:"
	_xnor: 	.asciiz 	"XNOR:"
	switch: 	.word 	NONE, _XNOR, _XOR, _NOR, _NAND, _OR, _AND
	res_arr: 	.word 	0, 0, 0, 0

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
		jr 	$ra
	yay:	#user success
		li	$v0, 4
		la	$a0, yay_
		syscall
		jr	$ra

	for_translation:	#translated users char input to an array of integers
		move	$t6, $a1
		andi	$t6, $t6, 0xF
		move	$a0, $t6
		addi	$a1, $a1, 4
		addi	$a0, $a0, 4
		addi	$a3, $a3, 1
		bne 	$a3, 4, for_translation
		lw	$v0, -12($a0)
		jr 	$ra

	compare_:	#comapres user input with actual calculated result
		lb	$t5, 0($a0)
		lb	$t6, 0($a1)
		seq	$t7, $t5, $t6
		bne 	$t7, 1, boo
		addi	$a0, $a0, 4
		addi	$a1, $a1, 4
		addi	$a3, $a3, 1
		bne 	$a3, 4, compare_
		jr 	$ra
		
	
	gate_loop1:
		li 	$v0, 4
		la 	$a0, prompt
		syscall	
		
		mul 	$t1, $s3, 4  	# (tmp = n*4)	      	
		lw 	$t1, switch($t1)   	# to be edited not a huge fan of this system fr like bleh
		jr	$t1
		
	#the following cases translate the code and the key through a specific logic gate (AND to XNOR)	
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
	_AND:
		li 	$v0, 4
		la 	$a0, _and
		syscall
		and 	$s2, $s0, $s1
		j 	gate_loop2
	
	gate_loop2:
		li 	$v0, 8
		la 	$a0, res	#ask user what they think for ...
		li 	$a1, 5
		syscall
		
		lw 	$a0, res_arr
		lw	$a1, res
		li	$a3, 0
		jal 	for_translation	#goes through gate per the array (AND = 6 then NONE = 0)
		sw	$v0, res_arr
		lw 	$a0, res_arr
		move	$a1, $s2
		li	$a2, 0
		jal	compare_
		addi	$s3, $s3, -1
		j	gate_loop1
		
		
		
			
		
		
		
		
		
		
		