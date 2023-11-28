# Author: Sophia Garcia
# Date: Oct 27, 2023
# Description: Macros to help repetetive code that need not the data from encrypt_1 
.macro 	end	
	li 	$v0, 10	#end program
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
	la	$a0, 1000	#700ms
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

.macro	print_bin	# macro with argument officially
## Here the each printed val is achieved by shifting the bits up to the desired bit then 
## AND-ing with 0x01 the AND operation isolated the bit to the what is the rightmost bit
	addi	$t2, $0, 3	# cntr for shifter
	addi	$t0, $a0, 0	# initialize $t0 with argument entered
for_loop_printer:
	srlv	$t3, $t0, $t2	# shift res to $t3
	andi	$t3, $t3, 0x1	# isolate digit
	li	$v0, 1	# syscall int to print a digit
	addi	$a0, $t3, 0	# what value to print
	syscall	#print left most bit
	addi	$t2, $t2, -1	# sub from val
	bgt	$t2, -1, for_loop_printer	# if no longer in range to print int num then leave
	
.end_macro

.macro	repeat_check	
	li	$t2, 0	# counter for loop
	li	$t1, 0	# set for whether or not the repeat is there or not
repeat_checker:
	beq	$t2, 4, go_back	# if cntr done then go back
	lb	$t0, 0($a0)	# retrieve from array
	beq	$t0, $s2, repeat	# if repeat go to repeat
	addi	$a0, $a0, 1	# add to array 
	addi	$t2, $t2, 1	# for loop cntr add
	j	repeat_checker

repeat:
	li	$t1, 1	# repeat true

go_back:
	#end macro
.end_macro

.macro 	status_bar
	# Example of drawing a rectangle; left x-coordinate is 100, width is 25
# top y-coordinate is 200, height is 50. Coordinate system starts with
# (0,0) at the display's upper left corner and increases to the right
# and down.  (Notice that the y direction is the opposite of math tradition.)
	li 	$a0,0	# left x-coordinate is 100
	li 	$a1,100	# width is 25
	li 	$a2,200	# top y-coordinate is 200
	mul 	$a3,$a3,50	# height is 50
	j 	rectangle
	

rectangle:
## CODE FROM PROF KEN ARNOLD

# $a0 is xmin (i.e., left edge; must be within the display)
# $a1 is width (must be nonnegative and within the display)
# $a2 is ymin  (i.e., top edge, increasing down; must be within the display)
# $a3 is height (must be nonnegative and within the display)

	beq 	$a1,$zero,rectangleReturn # zero width: draw nothing
	beq 	$a3,$zero,rectangleReturn # zero height: draw nothing

	li 	$t0,0xFF00 # color: white
	la 	$t1,frameBuffer
	add 	$a1,$a1,$a0 # simplify loop tests by switching to first too-far value
	add 	$a3,$a3,$a2
	sll 	$a0,$a0,2 # scale x values to bytes (4 bytes per pixel)
	sll 	$a1,$a1,2
	sll 	$a2,$a2,11 # scale y values to bytes (512*4 bytes per display row)
	sll 	$a3,$a3,11
	addu	$t2,$a2,$t1 # translate y values to display row starting addresses
	addu 	$a3,$a3,$t1
	addu 	$a2,$t2,$a0 # translate y values to rectangle row starting addresses
	addu 	$a3,$a3,$a0
	addu 	$t2,$t2,$a1 # and compute the ending address for first rectangle row
	li 	$t4,0x800 # bytes per display row

rectangleYloop:
	move 	$t3,$a2 # pointer to current pixel for X loop; start at left edge
	
rectangleXloop:
	sw 	$t0,($t3)
	addiu 	$t3,$t3,4
	bne 	$t3,$t2,rectangleXloop # keep going if not past the right edge of the rectangle
	
	addu 	$a2,$a2,$t4 # advace one row worth for the left edge
	addu 	$t2,$t2,$t4 # and right edge pointers
	bne 	$a2,$a3,rectangleYloop # keep going if not off the bottom of the rectangle
rectangleReturn:
.end_macro
