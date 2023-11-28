# Important: do not put any other data before the frameBuffer
# Also: the Bitmap Display tool must be connected to MARS and set to
#   display width in pixels: 512
#   display height in pixels: 256
#   base address for display: 0x10010000 (static data)
.data
frameBuffer:
.space 0x80000
.text

rectangle:
	sub	$sp, $sp, 4
	la	4($sp), $ra
# Example of drawing a rectangle; left x-coordinate is 100, width is 25
# top y-coordinate is 200, height is 50. Coordinate system starts with
# (0,0) at the display's upper left corner and increases to the right
# and down.  (Notice that the y direction is the opposite of math tradition.)
	li 	$a0, 100	# left x-coordinate is 100
	li 	$a1, 200	# top y-coordinate is 200
	# $a0 is xmin (i.e., left edge; must be within the display)
# $a1 is width (must be nonnegative and within the display)
# $a2 is ymin  (i.e., top edge, increasing down; must be within the display)
# $a3 is height (must be nonnegative and within the display)

	beq $a2,$zero,rectangleReturn # zero width: draw nothing
	beq $a3,$zero,rectangleReturn # zero height: draw nothing

	li $t0,0xFF00 # color: white
	la $t1,frameBuffer
	add $a1,$a1,$a0 # simplify loop tests by switching to first too-far value
	add $a3,$a3,$a2
	sll $a0,$a0,2 # scale x values to bytes (4 bytes per pixel)
	sll $a1,$a1,2
	sll $a2,$a2,11 # scale y values to bytes (512*4 bytes per display row)
	sll $a3,$a3,11
	addu $t2,$a2,$t1 # translate y values to display row starting addresses
	addu $a3,$a3,$t1
	addu $a2,$t2,$a0 # translate y values to rectangle row starting addresses
	addu $a3,$a3,$a0
	addu $t2,$t2,$a1 # and compute the ending address for first rectangle row
	li $t4,0x800 # bytes per display row
	
	move $t3,$a2 # pointer to current pixel for X loop; start at left edge
	
	sw $t0,($t3)
	
	jr	$ra
	
	
