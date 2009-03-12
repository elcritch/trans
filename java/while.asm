		push		$beg
		jmp
		$view1:		-1
		$view2:		-1
		$beg:
		push		$view1
		push		$sp
		push		0
		add
		st
		# x
		push		$view1
		ld
		push		0
		add
		push		1
		st
		$ws0
		# x
		push		$view1
		ld
		push		0
		add
		push		10
		sub
		push		$rf0
		jn
		$rt0:
		push		0
		push		$rq0
		jmp
		$rf0:
		push		1
		$rq0:
		push		$wq0
		jz
		# x
		push		$view1
		ld
		push		0
		add
		# x
		push		$view1
		ld
		push		0
		add
		push		1
		add
		st
		push		$ws0
		jump
		$wq0
		push		1
		wr
		stop
		end
