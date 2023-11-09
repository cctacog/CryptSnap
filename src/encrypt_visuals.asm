# Author: Sophia Garcia
# Date: Nov 07, 2023
# Description: CryptSnap visuals
#MAJORITY CODE FROM CLASS FILE EXAMPLES NOT 100% MY WORK 
.data
frameBuffer:
	.space 	0x80000
_zero:	.word 	0,0,0
_one:	.word	0,0,1
_two:	.word	0,1,0
_three:	.word	0,1,1
_four:	.word	1,0,0
_five:	.word	1,0,1
_six:	.word	1,1,0
_seven:	.word	1,1,1
_ZERO:	.word	_seven, _five, _five, _five, _seven
_ONE:	.word	_one, _one, _one, _one, _one
digit_parameters: 	.word	3,5
.text
	j	exact_coordinate
# Example of drawing a rectangle; left x-coordinate is 100, width is 25
# top y-coordinate is 200, height is 50. Coordinate system starts with
# (0,0) at the display's upper left corner and increases to the right
# and down.  (Notice that the y direction is the opposite of math tradition.)

exact_coordinate_temp:
# take arguments from a0
	li 	$a0,100	# left x-coordinate is 100 	# passed in argument
	la 	$a1,digit_parameters	# width is 3 and height 5
	li 	$a2,200	# top y-coordinate is 200	# passed in argument
	li 	$a3, 0	# passed in argument
	li	$s3, 0	#first array counter (row)
	li	$s4, 0 	#second array counter (col)
	j	rectangle
	

rectangle:
# $a0 is xmin (i.e., left edge; must be within the display)
# $a1 is width (must be nonnegative and within the display)
# $a2 is ymin  (i.e., top edge, increasing down; must be within the display)
# $a3 is height (must be nonnegative and within the display)

	lb	$s0, 0($a1)	# width
	lb	$s1, 1($a1)	# height
	beq 	$s0,$zero,rectangleReturn # zero width: draw nothing
	beq 	$s1,$zero,rectangleReturn # zero height: draw nothing

	li 	$t0,0xFF00 # color: neon green
	#in hexidecimal color scheme
	la 	$t1,frameBuffer	
	add 	$s0,$s0,$a0	# simplify loop tests by switching to first too-far value
	add 	$s1,$s1,$a2
	sll 	$a0,$a0,2 	# scale x values to bytes (4 bytes per pixel)
	sll 	$s0,$s0,2
	sll 	$a2,$a2,11	# scale y values to bytes (512*4 bytes per display row)
	sll 	$s1,$s1,11
	addu 	$t4,$a2,$t1	# translate y values to display row starting addresses
	addu 	$s1,$s1,$t1
	addu 	$a2,$t4,$a0	# translate y values to rectangle row starting addresses
	addu 	$s1,$s1,$a0
	addu 	$t4,$t4,$s0	# and compute the ending address for first rectangle row
	li 	$t5,0x800	# bytes per display row
	bne	$a3, 0, _one_sett	
	j	_zero_sett	
		
_one_sett:
	la	$s5, _ONE	#set the array sequence to 
	j	rectangleYloop

_zero_sett:
	la	$s5, _ZERO
	j	rectangleYloop
	
rectangleYloop:
	move 	$s1, $a2 # pointer to current pixel for X loop; start at left edge	
	
rectangleXloop_write:
	# adress = base +((r * numcols)+c)*4)
	##FROM SOPHIA GARCIA HW3
	mul 	$t0, $s3, 5
	add 	$t1, $s4, $t0
	mul 	$t1, $t1, 4
	add 	$t2, $t1, $s5
	lb 	$v0, 0($t2)	
	bne	$v0, 1, rectangleXloop_nextpxl
	sw 	$t0,($s1)
	
rectangleXloop_nextpxl:
	addiu 	$s1, $s1,4
	bne 	$s1, $t4, rectangleXloop_write # keep going if not past the right edge of the rectangle
	
	addu 	$a2, $a2,$t5 # advace one row worth for the left edge
	addu 	$t4, $t4,$t5 # and right edge pointers
	addi	$s3, $s3, 1
	add	$s4, $zero, $0
	bne 	$a2, $s1,rectangleYloop # keep going if not off the bottom of the rectangle

rectangleReturn:
	li 	$v0,10	#for now in debugging
	syscall