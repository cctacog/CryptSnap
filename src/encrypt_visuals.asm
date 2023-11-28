# Author: Sophia Garcia
# Date: Nov 07, 2023
# Description: CryptSnap visuals
# MAJORITY CODE FROM CLASS FILE EXAMPLES NOT 100% MY WORK 
.data
	frameBuffer:
		.space 	0x80000
	_zero:	.byte 	0,0,0
	_one:	.byte	0,0,1
	_two:	.byte	0,1,0
	_three:	.byte	0,1,1
	_four:	.byte	1,0,0
	_five:	.byte	1,0,1
	_six:	.byte	1,1,0
	_seven:	.byte	1,1,1

	_ZERO:	_seven, 
		_five, 
		_five, 
		_five, 
		_seven
	
	_ONE:	_one, 
		_one, 
		_one, 
		_one, 
		_one
	digit_parameters: 	.byte	3,5
.text
	j	exact_coordinate_temp
# Example of drawing a rectangle; left x-coordinate is 100, width is 25
# top y-coordinate is 200, height is 50. Coordinate system starts with
# (0,0) at the display's upper left corner and increases to the right
# and down. (Notice that the y direction is the opposite of math tradition.)

exact_coordinate_temp:
# take arguments from a0
	li 	$a0, 100	# left x-coordinate is 100 	# passed in argument
	la 	$a1, digit_parameters	# width is 3 and height 5
	li 	$a2, 200	# top y-coordinate is 200	# passed in argument
	li 	$a3, 0	# passed in argument
	li	$s3, 0	# first array counter (row)
	li	$s4, 0 	# second array counter (col)
	li	$t6, 0	# later counter (row)
	li	$t7, 0	# layer counter (col)
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
	addu	$t2,$a2,$t1	# translate y values to display row starting addresses
	addu 	$s1,$s1,$t1
	addu 	$a2,$t2,$a0	# translate y values to rectangle row starting addresses
	addu 	$s1,$s1,$a0
	addu 	$t2,$t2,$s0	# and compute the ending address for first rectangle row
	li 	$t4,0x800	# bytes per display row
	bne	$a3, 0, _one_sett	
	j	_zero_sett	
		
_one_sett:
	la	$s5, _ONE	#set the array sequence to 
	j	rectangleYloop

_zero_sett:
	la	$s5, _ZERO
	j	rectangleYloop
	
rectangleYloop:
	move 	$t3, $a2 # pointer to current pixel for X loop; start at left edge	
	
rectangleXloop_det_write:
	# address = base + ((r * numcols) + c) * 4)
	## FROM SOPHIA GARCIA HW3
	mul 	$t5, $s3, 5
	add 	$t5, $s4, $t5
	mul 	$t5, $t5, 4
	add 	$t5, $t5, $s5
	lb 	$v0, 0($t5)	
	bne	$v0, 1, rectangleXloop_nextpxl

coloring:
	move 	$t0, $s1
	
rectangleXloop_nextpxl:
	addiu 	$t3, $t3, 4	# move one byte over by the 
	addi	$t7, $t7, 1	# add until 10 blocks colored	
	bne	$t7, 10, rectangleXloop_det_write	# keep at pos adding until ten blocks printed
	addi	$t7, $0, 0	# restart coloring count
	addi	$s4, $s4, 1	# move over by one on col of current row
	bne 	$s1, $t4, rectangleXloop_det_write # keep going if not past the right edge of the rectangle
	
	addu 	$a2, $a2,$t5	# advance one row worth for the left edge
	addi	$t6, $t6, 1	# add to how many of rows of current row colored in
	addu 	$t4, $t4,$t5	# and right edge pointers
	add	$s4, $zero, $0	# restart col count
	bne	$t6, 10, rectangleYloop	# if 10 of same row colored then move on
	addi	$t6, $0, 0	# restart row count
	addi	$s3, $s3, 1	# add to the wanted row
	add	$s4, $zero, $0	# restart col count
	bne 	$a2, $s1,	rectangleYloop # keep going if not off the bottom of the rectangle

rectangleReturn:
	li 	$v0,10	# for now in debugging
	syscall
