# Author: Sophia Garcia
# Date: Sept 29, 2023
# Description: A simple input logic gate calculator; later to be refurbished into the CryptSnap game

.data
	intro: .asciiz "Welcome to CryptSnap!\nToday learn about the 6 different gates!\nAND, OR, NAND, NOR, XOR, XNOR\n"
	prompt: .asciiz "Solve integers 1000 and 1010 through the gate "
	res: .space 4 #for three digit num plus a null pointer end
	_and: .asciiz "AND:"
	_or: .asciiz "OR:"
	_nand: .asciiz "NAND:"
	_nor: .asciiz "NOR:"
	_xor: .asciiz "XOR:"
	_xnor: .asciiz "XNOR:"
	gate_char: .word _and, _or, _nand, _nor, _xor, _xnor
	

.text
	li $s0, 0x8u
	li $s1, 0xAu
	li $s3, 6
	li $v0, 4
	la $a0, intro
	syscall
	
	li $v0, 10
	syscall
	
	jal gate_loop1
	
	gate_loop1:
		li $v0, 4
		la $a0, prompt
		syscall
		beq $s2, 1, _AND
		beq $s2, 2, _OR
		beq $s2, 3, _NAND
		beq $s2, 4, _NOR
		beq $s2, 5, _XOR
		beq $s2, 6, _XNOR # to be edited not a huge fan of this system fr like bleh
	
	_AND:
		li $v0, 4
		la $a0, 0(gate_char)
		syscall
		and $t0, $s0, $s1
		j gate_loop2
	_OR:
		li $v0, 4
		la $a0, 4(gate_char)
		syscall
		or $t0, $s0, $s1
		j gate_loop2
	_NAND:
		li $v0, 4
		la $a0, 8(gate_char)
		syscall
		nand $t0, $s0, $s1
		j gate_loop2		
	_NOR:
		li $v0, 4
		la $a0, 12(gate_char)
		syscall
		nor $t0, $s0, $s1
		j gate_loop2		
	_XOR:
		li $v0, 4
		la $a0, 16(gate_char)
		syscall
		xor $t0, $s0, $s1
		j gate_loop2
	_XNOR:
		li $v0, 4
		la $a0, 20(gate_char)
		syscall
		xnor $t0, $s0, $s1
		j gate_loop2
	
	gate_loop2:
		