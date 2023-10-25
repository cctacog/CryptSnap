# Author: Sophia Garcia
# Date: Sept 29, 2023
# Description: A simple input logic gate calculator; later to be refurbished into the CryptSnap game
.include "encrypt_macros.asm"
.data
res: 	.byte	16	#for four digit num plus a null pointer end	
switch1: 	.word 	NONE, _XNOR, _XOR, _NOR, _NAND, _OR, _AND
switch2:	.word	NONE, _XNOR, _NAND, _AND
levels:	.word	NONE, level1_loop, level2_loop, level3
res_arr: 	.byte	0, 0, 0, 0
intro: 	.asciiz 	"Welcome to CryptSnap!\nToday learn about the 6 different gates!\nAND, OR, NAND, NOR, XOR, XNOR\n"
prompt: 	.asciiz 	"Solve integers 1000 and 1010 through the gate "
boo_:	.asciiz	"\nBoo fail\n"
yay_: 	.asciiz	"\nYay you got it!\n"
_and_:	.asciiz	" and "
_colon:	.asciiz	":"
_and: 	.asciiz 	"AND"
_or: 	.asciiz 	"OR"
_nand:	.asciiz 	"NAND"
_nor: 	.asciiz 	"NOR"
_xor: 	.asciiz 	"XOR"
_xnor: 	.asciiz 	"XNOR"
	

.text
	addi 	$s0, $0, 0x8
	addi 	$s1, $0, 0xA
	addi	$s2, $0, 0x0
	li 	$s3, 6
	li	$s4, 1
	
	li 	$v0, 4
	la 	$a0, intro
	syscall 		
	
	j 	gate_loop		
	
boo:	#user failed
	li	$v0, 4
	la	$a0, boo_	#prints boo to user
	syscall
	jr 	$ra
	#macro this
	
yay:	#user success
	li	$v0, 4
	la	$a0, yay_	#prints yay to user
	syscall
	jr	$ra
	#macro
	
for_translation:	#translated users char input to an array of integers						
	lb	$t0, 3($a1)
	andi	$t1, $t0, 0xF
	sb	$t1, 3($a0)
	lb	$t0, 2($a1)
	andi	$t1, $t0, 0xF
	sb	$t1, 2($a0)
	lb	$t0, 1($a1)
	andi	$t1, $t0, 0xF
	sb	$t1, 1($a0)
	lb	$t0, 0($a1)
	andi	$t1, $t0, 0xF
	sb	$t1, 0($a0)
	jr	$ra
	#macro
		
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
	#macro
	
gate_loop:
	addi	$t1, $0, 0
	mul 	$t1, $s4, 4  	#(tmp = n*4)
	lw	$t1, levels($t1)
	beq	$s3, 0, new_level
	jr	$t1
	
new_level:#if needed the level number goes up and the settings for the global variables changes based on the next level 
	#default settings for level one set when the program goes off
	addi	$s4, $s4, 1
	#no settings for level 3 just texts needed for teaching
	#possibly to add a mcq portion to make level 3 more fancy
	beq	$s4, 3, level3
	li	$s3, 3	#settings for level two
	beq	$s4, 2, level2_loop
	
level1_loop:	#level 1 loop of prompt + which gate to go to for 6 times of AND to XNOR
	li 	$v0, 4
	la 	$a0, prompt
	syscall	#print prompt
	addi	$t1, $0, 0
	mul 	$t1, $s3, 4  	#(tmp = n*4)
	#set t1 reg to the gate     	
	lw 	$t1, switch1($t1)   	
	#go to gate without conditions of reason to return 
	jr	$t1

level2_loop:	#print the prompt and go to two the coorelating gate afterwards with the condition within the gate becuase the level is int = 2
	li 	$v0, 4
	la 	$a0, prompt
	syscall	#print prompt
	addi	$t1, $0, 0
	mul 	$t1, $s3, 4	#(tmp = n*4)
	#set t1 reg to the gate     	
	lw 	$t1, switch2($t1)   
	#go to gate without conditions of reason to return then to another gate within said gate
	jr	$t1
level3:
	end #no loops here just run thru the prompts and teachings of LFSR encrypting and ask the user for their result and end
		
#the following cases translate the code and the key through a specific logic gate (AND to XNOR)	
_AND:
	li 	$v0, 4
	la 	$a0, _and
	syscall	#prints the gate
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	and_	#translates the s0 and s1 thru the gate into s2 the result with stack
	bne	$s4, 2, gate_loop2	#if the level is 2 then the next block is gate_loop2
	la	$a0, _and_	#if level two print 'and'
	syscall			#print the 'and'
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	nor_
	add	$sp, $sp, 8
	j	gate_loop2		#go to NOR gate when level 2 s4
_OR:
	li 	$v0, 4
	la 	$a0, _or
	syscall	#print 'OR'
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	or_	#set s0 and s1 thru or gate into s2
	add	$sp, $sp, 8
	j 	gate_loop2
_NAND:
	li 	$v0, 4
	la 	$a0, _nand	
	syscall	#print 'NAND'
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	nand_	#set s0 and s1 thru nand gate into s2
	bne	$s4, 2, gate_loop2	#if not level 2 go to gate_loop2 block
	la	$a0, _and_	#if level 2 print 'and'
	syscall	
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	xor_		#s2 and s1 thur xor gate bc in level 2
	add $sp, $sp, 8	#reset stack
	j	gate_loop2	#go to XOR block if level 2
_NOR:
	li 	$v0, 4		
	la 	$a0, _nor
	syscall	#print 'NOR'
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	nor_	#set s0 and s1 thru nor gate into s2
	add	$sp, $sp, 8
	j 	gate_loop2	#go to gate_loop2 block no matter what
_XOR:
	li 	$v0, 4		
	la 	$a0, _xor
	syscall	#print 'XOR'
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	xor_	#set s0 and s1 thru xor gate into s2
	add	$sp, $sp, 8
	j 	gate_loop2	#no matter what go to gate_loop2 block
_XNOR:
	li 	$v0, 4
	la 	$a0, _xnor
	syscall	#print 'XNOR'
	sub	$sp, $sp, 8
	sb	$s0, 4($sp)
	sb	$s1, 0($sp)
	xnor_
	bne	$s4, 2, gate_loop2	#if the level is not 2 go to gate_loop2 block
	la	$a0, _and_	
	syscall	#print 'and'
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	or_		#go to OR gate
	add	$sp, $sp, 8
	j	gate_loop2
NONE:
	end	#this one ends the code/level	

gate_loop2:
	la	$a0, _colon 	#print ':'
	syscall
	
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
	j 	gate_loop
