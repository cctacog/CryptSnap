# Important: do not put any other data before the frameBuffer
# Also: the Bitmap Display tool must be connected to MARS and set to
#   display width in pixels: 512
#   display height in pixels: 256
#   base address for display: 0x10010000 (static data)
.data
_zero:	.byte 	0,0,0
_one:	.byte	0,0,1
_two:	.byte	0,1,0
_three:	.byte	0,1,1
_four:	.byte	1,0,0
_five:	.byte	1,0,1
_six:	.byte	1,1,0
_seven:	.byte	1,1,1
_ZERO:	.word 	_seven, _five, _five, _five, _seven
_ONE:	.word	_one, _one, _one,_one, _one

.text
		
_one_sett:
	la	$t7, _ONE	#set the array sequence to 
	j	rectangleYloop

_zero_sett:
	la	$t7, _ZERO
	j	rectangleYloop
	
rectangleloop_det_write:
	# address = base + ((r * numcols) + c) * 4)
	## FROM SOPHIA GARCIA HW3
	mul 	$t8, $s7, 5
	add 	$t8, $s6, $t8
	mul 	$t8, $t8, 4
	add 	$t8, $t8, $t7
	lb 	$v0, ($t8)	
	bne	$v0, 1, rectangleloop_nextpxl

coloring:
	sw 	$t0,($t3)
	
rectangleXloop_nextpxl:
	addiu 	$t3, $t3, 4	# move one byte over by the 
	addi	$t5, $t5, 1	# add until 10 blocks colored	
	bne	$t5, 10, rectangleXloop_det_write	# keep at pos adding until ten blocks printed
	addi	$t5, $0, 0	# restart coloring count
	addi	$s6, $s6, 1	# move over by one on col of current row
	bne 	$t3, $t2, rectangleXloop_det_write # keep going if not past the right edge of the rectangle
	
	addu 	$a2, $a2, $t4	# advance one row worth for the left edge
	addi	$t6, $t6, 1	# add to how many of rows of current row colored in
	addu 	$t2, $t2, $t4	# and right edge pointers
	add	$s6, $zero, $0	# restart col count
	bne	$t6, 10, rectangleYloop	# if not 10 of same row colored then keep going at same row
	addi	$t6, $0, 0	# restart coloring row cnt
	addi	$s7, $s7, 1	# add to the wanted row

	bne 	$a2, $a3, rectangleYloop # keep going if not off the bottom of the rectangle

rectangleReturn:
	jr	$ra
