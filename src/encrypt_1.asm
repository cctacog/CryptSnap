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
rand_arr:	.byte	0, 0, 0, 0, 0
intro: 	.asciiz 	"Welcome to CryptSnap!\nToday learn about the 6 different gates!\nAND, OR, NAND, NOR, XOR, XNOR\n"
prompt: 	.asciiz 	"\nSolve integers 1000 and 1010 through the gate "
l3_p1:	.asciiz	"\nWhen you implement gates to bit sequences you are encrypting data!\nNow let us say we want to encrypt data one bit at a time\nand never the less specific bits at a time\n"
l3_p2: 	.asciiz	"Is it possible?\nAnswer: YES!\nWith a method called Linear Feedback Shift Register encryption we can send specific\nbits thru gates to then SHIFT and CHANGE the current bit sequence to a brand new value!\n"
l3_p3:	.asciiz	"Here we will be reading bits LEFT to RIGHT\n so in our bit sequence 1010 the last bit (bit 4) is the 0\nAnd our first bit (bit 1) is 1\n"
l3_p4:	.asciiz 	"Because we only have four total bits we will XOR bits 3 and 4 then move the resulting bit to the left-most end shifting the bit to the right\n"
l3_p5:	.asciiz	"Now let us try with some random four bit values!\n"
lvl3_p:	.asciiz	"What is the one step LFSR translation for "
boo_:	.asciiz	"\nBoo fail :"
yay_: 	.asciiz	"\nYay you got it!\n"
_and_:	.asciiz	" and "
_colon:	.asciiz	":"
next:	.asciiz	"\n"
_and: 	.asciiz 	"AND"
_or: 	.asciiz 	"OR"
_nand:	.asciiz 	"NAND"
_nor: 	.asciiz 	"NOR"
_xor: 	.asciiz 	"XOR"
_xnor: 	.asciiz 	"XNOR"
	
.text
	addi 	$s0, $0, 0x8	#set var 1 constant to 8
	addi 	$s1, $0, 0xA	#set var 2 constant to 10
	addi	$s2, $0, 0x0	#set var 3 non-constant to 0
	li 	$s3, 6		#for level 1 six rounds (per gate)
	li	$s4, 1		#level 1 start off
	li	$s5, 0	#the pos of the repeat array for ran val to not be repeated
	li 	$v0, 4	#print syscall
	la 	$a0, intro	#what to print
	syscall 	#printing
	slp	#sleep macro
	j 	gate_loop		
	
boo:	#user failed
	li	$v0, 4
	la	$a0, boo_	#prints boo to user
	syscall	#print boo_ string
	slp
	move	$a0, $s2
	print_bin
	slp
	li	$v0, 4
	la	$a0, next	
	syscall	#next line print
	jr 	$ra
	
yay:	#user success
	li	$v0, 4
	la	$a0, yay_	#prints yay to user
	syscall	#print yay_ string
	slp
	jr	$ra
	
for_translation:	#translated users char input to an array of integers						
	lb	$t0, 3($a1)	#load left most bit
	andi	$t1, $t0, 0xF	#isolate bit
	sb	$t1, 3($a0)	#store left most bit to left most of array
	#above process repeated for all four bits to be store in array
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
		
compare_:	#compares user input with actual calculated result			
	lb	$t2, 0($a0)	#get rightmost bit of array user input
	srl	$t3, $s2, 3	#get rightmost bit of s2 var
	andi	$t3, $t3, 0x1	#isolate s2 rightmost bit
	bne	$t2, $t3, boo	#compare if they not equal then user failed go to boo
	#the sequence will continue 
	#until either all equal or 
	#error found then will go back to gate_loop2
	#above sequence repeated
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
#CODE FROM SWITCH TEMPLATE IN COMPE 271 SHARED FILES
	addi	$t1, $0, 0
	mul 	$t1, $s4, 4  	#(tmp = n*4)
	lw	$t1, levels($t1)
	beq	$s3, 0, new_level
	jr	$t1
	
new_level:#if needed the level number goes up and the settings for the global variables changes based on the next level 
	#default settings for level one set when the program goes off
	addi	$s4, $s4, 1
	addi	$s3, $zero, 0
	#possibly to add a mcq portion to make level 3 more fancy
	beq	$s4, 3, level3
	li	$s3, 3	#settings for level two
	beq	$s4, 2, level2_loop
	end
	
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
	
level3:	bne	$s3, 0, lvl3_loop1
	li	$v0, 4
	la	$a0, l3_p1
	syscall	#prints prompt one
	slp
	la	$a0, l3_p2
	syscall	#print prompt two
	slp
	la	$a0, l3_p3
	syscall	#print prompt three
	slp
	la	$a0, l3_p4
	syscall	#print prompt four
	slp
	move	$a0, $s1	
	#here use 10 as changing val so next transform will be of 10 into var s2
	lfsr_random
	la	$a0, lvl3_p
	syscall	#print level 3 prompt
	addi	$a0, $s1, 0
	print_bin
	j	gate_loop2
	
lvl3_loop1:
	blt	$s3, -2, lvl3_loop2
	la	$a0, lvl3_p
	syscall	#print level 3 prompt
	move	$a0, $s2
	print_bin	#print s2 bits
	move	$a0, $s2
	lfsr_random	#generate the LFSR transform of s2
	j	gate_loop2
	end
lvl3_loop2:
	blt	$s3, -6, NONE
	li	$v0, 4
	la	$a0, l3_p5
	syscall	#prints prompt five
	slp
	la	$a0, lvl3_p
	syscall
	jal	no_zero_norep
	move	$a0, $s2
	print_bin	#print random val s2 before using LFSR
	move	$a0, $s2
	lfsr_random	#LFSR s2
	j	gate_loop2
	end	#in case of errors just end code
	
no_zero_norep:	
	rand	#generate random val from 0-15 for s2
	beq	$s2, 0, no_zero_norep	#is is zero then rerun block
	la	$a0, rand_arr
	repeat_check	#goes through prev vals to make sure no repeats (saves up to four vals)
	bne	$t1, 0, no_zero_norep
	mul	$t1, $s5, 4
	sw	$s2, rand_arr($t1)
	addi	$s5, $s5, 1
	jr	$ra	#when not 0 go back to prev block of code line stored
			
##the following cases translate the code and the key through a specific logic gate (AND to XNOR)	
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
	syscall	#print the 'and'
	li 	$v0, 4		
	la 	$a0, _nor
	syscall	#print 'NOR'
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	nor_	#go to nor gate macro
	add	$sp, $sp, 8
	j	gate_loop2	#go to NOR gate when level 2 s4
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
	syscall	#print 'NAND'
	li 	$v0, 4		
	la 	$a0, _xor
	syscall	#print 'XOR'
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	xor_	#s2 and s1 thur xor gate bc in level 2
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
	li 	$v0, 4
	la 	$a0, _or
	syscall	#print 'OR'
	sb	$s1, 4($sp)
	sb	$s2, 0($sp)
	or_	#go to OR gate
	add	$sp, $sp, 8
	j	gate_loop2
NONE:
	end	#this one ends the code/level	

gate_loop2:
	li	$v0, 4
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
