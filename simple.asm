	push	$lab0
	jmp
$fps:	0
$lab0:
	push	$fps
	push	0
	add
	push	$sp
	ld
	st
	push	$sp
	dup
	ld
	push	3
	add
	st
	push	$fps
	push	0
	add
	ld
	push	0
	add
	rd
	st
	push	$fps
	push	0
	add
	ld
	push	1
	add
	rd
	st
	push	$fps
	push	0
	add
	ld
	push	0
	add
	ld
	push	$fps
	push	0
	add
	ld
	push	1
	add
	ld
	sub
	push	1
	swap
	push	$lab3
	jn
	not
$lab3:
	push	$lab1
	jz
	push	$fps
	push	0
	add
	ld
	push	2
	add
	push	$fps
	push	0
	add
	ld
	push	0
	add
	ld
	push	$fps
	push	0
	add
	ld
	push	1
	add
	ld
	div
	st
	push	$lab2
	jmp
$lab1:
	push	$fps
	push	0
	add
	ld
	push	2
	add
	push	$fps
	push	0
	add
	ld
	push	1
	add
	ld
	push	$fps
	push	0
	add
	ld
	push	0
	add
	ld
	div
	st
$lab2:
	push	$fps
	push	0
	add
	ld
	push	2
	add
	ld
	wr
	push	$sp
	dup
	ld
	push	3
	sub
	st
	stop
	end
