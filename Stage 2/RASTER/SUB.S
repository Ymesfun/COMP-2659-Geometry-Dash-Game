		xdef		_add
		xref		_trace

y		equ		10
x		equ		8

_add:		link		a6,#0
		move.w		x(a6),d0
		add.w		y(a6),d0

		movem.l		d0-2/a0-2,-(sp)
		jsr		_trace
		movem.l		(sp)+,d0-2/a0-2

		unlk		a6
		rts
