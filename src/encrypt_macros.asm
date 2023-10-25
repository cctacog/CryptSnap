.macro 	end
	#end program
	li 	$v0, 10
	syscall
.end_macro

.macro 	and_		
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	and 	$s2, $t0, $t1
.end_macro

.macro 	nor_
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	nor	$s2, $t0, $t1
.end_macro

.macro 	or_	
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	or	$s2, $t0, $t1
.end_macro

.macro 	nand_	
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	and 	$t0, $t0, $t1	#set s0 and s1 thru AND
	not 	$s2, $t0		#set t0 result thru NOT into s2
.end_macro

.macro 	xor_	
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	xor 	$s2, $t0, $t1	
.end_macro

.macro 	xnor_	
	lb	$t0, 0($sp)
	lb	$t1, 4($sp)
	xor 	$t0, $t0, $t1	#set number thru xor gate
	not 	$s2, $t0		#set prev result thru not gate into s2
.end_macro

.macro	lfsr
##code from hw 4##
#initalize the temp var to comence with the shifts and xor gate usage because only bi directional assembly
	move 	$t0, $a0
	addi	$t1, $zero, 0 
	addi	$t2, $zero, 0 
	addi	$t3, $zero, 0 
	addi	$t4, $zero, 0 
#process of xoring the shifted versions of the input of reg a0 then or with original shifted rigth one (log)
	srl	$t1, $t0, 0
	and	$t1, $t1, 0x1
	srl	$t2, $t0, 10
	and	$t2, $t2, 0x1
	xor	$t3, $t1, $t2
#set one compelte for the shifted a0 bit 0 and 10
	srl	$t1, $t0, 30
	and	$t1, $t1, 0x1
	srl	$t2, $t0, 31
	and	$t2, $t2, 0x1
	xor	$t4, $t1, $t2
#set two complete for the shifted a0 of 30 and 31
#final xor 
	xor	$t4, $t3, $t4
#shift argument input by 1 to the right
	srl	$t0, $t0, 1
#shift the result by 31 to move in position to be or'ed with new shifted a0
	sll	$t4, $t4, 31
#final reutrn value is of or'ed xor result and the shifted seed argument val
	or	$v0, $t0, $t4
.end_macro