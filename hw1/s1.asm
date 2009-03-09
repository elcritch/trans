	push	$beg
	jmp
$v1:	-1	# viewports
$v2:	-1
$v3:	-1
	
$beg:	
	# initialize block stack 1 in view port 1
	push	$v1	# store in viewport 1
	push	$sp	# store stack+1 in $v1
	push 	1
	add
	st		# now location of stack 1 is stored in $v1
	
	push	a	# now store so many variables (offset)
	push	b	
	# dump
	
	###### store to a variable
	push 	$v1	# get viewport 0 address
	ld		# load viewport address
	push	0	# add var offset to base $v1 address
	add		
	
	push 1000	# now store in var
	st
	
	## store second var
	push 	$v1	# get viewport 0 address
	ld		# load viewport address
	push	1	# add var offset to base $v1 address
	add		
	
	push 12	# now store in var
	push 3
	div
	st
	dump
	
	push none
	push none
	
	###### read variable
	push $v1
	ld
	push 1
	add
	ld
	wr
	dump
	
	stop
	end

