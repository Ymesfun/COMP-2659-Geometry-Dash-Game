;Sets the video base given an address.
;User is expected to be in supervisor mode before messing with video registers.

video_base_addr		equ		$FFFF8200
video_base_hi		equ		$FFFF8201
video_base_mi		equ		$FFFF8203
hi_offset			equ		$1
mi_offset			equ		$3

addr_offset		equ		8
		xdef		_set_video_base_asm

_set_video_base_asm:
		link		a6,#0
		movem.l		d0-1/a0-1,-(sp)
		move.l		video_base_addr,a0
		move.l		addr_offset(a6),d0
		lsr			#addr_offset,d0
		movep.w		d0,hi_offset(a0)
		movem.l		(sp)+,d0-d1/a0-a1
		unlk a6
		rts
