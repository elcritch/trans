	push	$beg
	jmp
$v1:	-1	# viewports
$v2:	-1
$v3:	-1
	
$beg:
	push 	"a<b==t"
	wr
	#################################
	
	# check if a < b
   	push 1000	
   	push 3333	
	sub
	push $ef0
	jn
$et0:	push 0
	# push f
	# wr
	push $eq0
	jmp
$ef0:	push 1
	# push t
	# wr
	
$eq0:	
	dup
	wr 
	# dump


	push 	"a>b==f"
	wr
	#################################
	# check if a > b
   	push 1000	
   	push 3333	
	sub
	push $ef1
	jp
$et1:	push 0
	# push f
	# wr
	push $eq1
	jmp
$ef1:	push 1
	# push t
	# wr
	
$eq1:	
	dup
	wr
	# dump
	
	
	push 	"a<b==f"
	wr
	#################################
	# check if a < b
   	push 3333	
   	push 1000	
	sub
	push $ef2
	jn
$et2:	push 0
	# push f
	# wr
	push $eq2
	jmp
$ef2:	push 1
	# push t
	# wr
	
$eq2:	
	dup
	wr 
	# dump

	push 	"a>b==t"
	wr
	# check if a > b
   	push 3333	
   	push 1000	
	sub
	push $ef3
	jp
$et3:	push 0
	# push f
	# wr
	push $eq3
	jmp
$ef3:	push 1
	# push t
	# wr
	
$eq3:	
	dup
	wr
	dump
	stop
	end

