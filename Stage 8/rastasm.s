;Sets the video base given an address.
;User is expected to be in supervisor mode before messing with video registers.

video_base_addr		equ		$FFFF8200
video_base_hi		equ		$FFFF8201
video_base_mi		equ		$FFFF8203
hi_offset			equ		$1
mi_offset			equ		$3

addr_offset		equ		8
		xdef		_set_video_base_asm, _set_video_base

_set_video_base_asm:
		link		a6,#0
		movem.l		d0/a0,-(sp)
		move.l		#video_base_hi,a0
		move.l		addr_offset(a6),d0
		lsr.l			#8,d0
		movep.w		d0,(a0)
		movem.l		(sp)+,d0/a0
		unlk a6
		rts

_set_video_base:
		link	a6,#0
		movem.l	d0/a0,-(sp)

		jsr		_enter_super

		clr.l 	d0
		move.l	NEW_VIDEO_BASE_OFFSET(a6),d0
		lsr.l   #8,d0
		move.l  #video_reg_address,a0
		movep.w d0,(a0)
		
		jsr		_exit_super
		
		movem.l	(sp)+,d0/a0
		unlk	a6
		rts

GEMDOS				equ		1


;----------------- SUBROUTINE: void enter_super(); ----------------
; PURPOSE:  lets user enter supervisor mode. From one of the labs
;			Uses a global in this file to keep track of the old ssp
;-------------------------------------------------------------------------------

_enter_super:
		movem.l	d0-2/a0-2,-(sp)

		clr.l	-(sp)		; enter supervisor mode with user stack
		move.w	#$20,-(sp)
		trap	#GEMDOS
		addq.l	#6,sp
		move.l	d0,old_ssp	; save old system stack pointer

		movem.l	(sp)+,d0-2/a0-2
		rts
;--------------------end of Subroutine------------------------------------------




;----------------- SUBROUTINE: void exit_super(); ----------------
; PURPOSE:  lets user exit supervisor mode. From one of the labs
;			Uses a global in this file to restore old ssp
;-------------------------------------------------------------------------------
_exit_super:
		movem.l	d0-2/a0-2,-(sp)

		move.l	old_ssp(pc),-(sp)	; return to user mode, restoring
		move.w	#$20,-(sp)			; system stack pointer
		trap	#GEMDOS
		addq.l	#6,sp

		movem.l	(sp)+,d0-2/a0-2
		rts
;--------------------end of Subroutine------------------------------------------

old_ssp:	ds.l	    1		; SSP save area
