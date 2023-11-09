# Author: Sophia Garcia
# Date: Oct 27, 2023
# Description: Macros to help repetetive code that need not the data from encrypt_1 
.macro 	end
	#end program
	li 	$v0, 10
	syscall
.end_macro

.macro 	and_		
	lb	$t0, 0($sp)	#value 1
	lb	$t1, 4($sp)	#value 2
	and 	$s2, $t0, $t1	#set s2 to v1 and'ed v2
.end_macro

.macro 	nor_
	lb	$t0, 0($sp)	#value 1
	lb	$t1, 4($sp)	#value 2
	nor	$s2, $t0, $t1	#set s2 to v1 nor'ed v2
.end_macro

.macro 	or_	
	lb	$t0, 0($sp)	#value 1
	lb	$t1, 4($sp)	#value 2
	or	$s2, $t0, $t1	#set variable s2 to v1 or'ed v2 
.end_macro

.macro 	nand_	
	lb	$t0, 0($sp)	#value 1
	lb	$t1, 4($sp)	#value 2
	and 	$t0, $t0, $t1	#set s0 and s1 thru AND
	not 	$s2, $t0		#set t0 result thru NOT into s2
.end_macro

.macro 	xor_	
	lb	$t0, 0($sp)	#v1
	lb	$t1, 4($sp)	#v2
	xor 	$s2, $t0, $t1	#set s2 v1 xor'ed v2
.end_macro

.macro 	xnor_	
	lb	$t0, 0($sp)	#v1
	lb	$t1, 4($sp)	#v2
	xor 	$t0, $t0, $t1	#set v1 v2 thru xor gate
	not 	$s2, $t0		#set prev result thru not gate into s2
.end_macro

.macro	lfsr_random	#macro with arguments officially
##code from hw 4##
#move s1 to temp
	move 	$t0, $a0
	#initialize the temps 0 just in case
	addi	$t1, $zero, 0 
	addi	$t2, $zero, 0 
	#set the temps to bits 3 and 1 LMB
	srl	$t1, $t0, 0
	and	$t1, $t1, 0x1
	srl	$t2, $t0, 1
	and	$t2, $t2, 0x1
	#use the xor gate
	xor	$t2, $t1, $t2
	#shift argument input by 1 to the right
	srl	$t0, $t0, 1
#shift the result by 31 to move in position to be or'ed with new shifted a0
	sll	$t2, $t2, 3
#final reutrn value is of or'ed xor result and the shifted seed argument val
	or	$s2, $t0, $t2
.end_macro

.macro 	slp
	move 	$t0, $v0	#records prev v0 syscall immediate
	li	$v0, 32	#sets v0 syscall immediate to sleep for an amount of time in ms(miliseconds)
	la	$a0, 700	#700ms
	syscall	#sleep done
	move	$v0, $t0	#retunrs original immediate val
.end_macro

.macro 	rand
	move	$t0, $v0	#records prev immediate syscall val
	li	$t1, 0xF	#maximum val for random
	li	$v0, 42	#syscall immediate for random generated value
	addi	$a1, $t1, 0	#set max rand val
	syscall	#generate random
	move	$s2, $a0	#store the result val
	move	$v0, $t0	#return prev immediate val
.end_macro

.macro	print_bin	#macro with argument officially
## Here the each printed val is achieved by shifting the bits up to the desired bit then 
## AND-ing with 0x01 the AND operation isolated the bit to the what is the rightmost bit
	addi	$t0, $a0, 0
	srl	$t3, $t0, 3
	andi	$t3, $t3, 0x1
	li	$v0, 1
	addi	$a0, $t3, 0
	syscall	#print left most bit
	srl	$t3, $t0, 2
	andi	$t3, $t3, 0x1
	li	$v0, 1
	addi	$a0, $t3, 0
	syscall	#print second to left most bit
	srl	$t3, $t0, 1
	andi	$t3, $t3, 0x1
	li	$v0, 1
	addi	$a0, $t3, 0
	syscall	#prints second to right most bit
	srl	$t3, $t0, 0
	andi	$t3, $t3, 0x1
	li	$v0, 1
	addi	$a0, $t3, 0
	syscall	#print right most bit
.end_macro

.macro	repeat_check
	lb	$t0, 0($a0)
	beq	$t0, $s2, repeat
	lb	$t0, 1($a0)
	beq	$t0, $s2, repeat
	lb	$t0, 2($a0)
	beq	$t0, $s2, repeat
	lb	$t0, 3($a0)
	beq	$t0, $s2, repeat
	lb	$t0, 4($a0)
	beq	$t0, $s2, repeat
		
	li	$t1, 0
	j	go_back
repeat:
	li	$t1, 1
go_back:
	#end macro
.end_macro
