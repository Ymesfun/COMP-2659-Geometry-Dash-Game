;==============================================================================
; IKBD INTERRUPT SERVICE ROUTINE (ISR)
;==============================================================================
; PURPOSE: Handles keyboard and mouse input from the IKBD microcontroller
;
; DESCRIPTION:
;   This ISR is invoked by vector #70 ($118) whenever the IKBD sends a byte
;   through the ACIA. It implements a finite state machine to distinguish
;   between keyboard scancodes and 3-byte mouse packets.
;
; MOUSE PACKET FORMAT (3 bytes):
;   Byte 1 (Header): %11111brl  where b=both buttons, r=right, l=left
;   Byte 2 (dx):     
;   Byte 3 (dy):     
;
; KEYBOARD SCANCODES:
;   Any byte < $F8 is treated as a keyboard scancode (make or break code)
;
; STATE MACHINE:
;   counter_byte = 0: Waiting for keyboard scancode or mouse header
;   counter_byte = 1: Waiting for mouse dx (second byte of packet)
;   counter_byte = 2: Waiting for mouse dy (third byte of packet)
;==============================================================================


;-------------------------------------------------------------------------
; Hardware Register Addresses
;-------------------------------------------------------------------------
IKBD_STATUS   equ $FFFFFC00
IKBD_DATA     equ $FFFFFC02
MFP_ISRB      equ $FFFA11
;--------------------------------------------------------------------------
		xdef		_KBD_interrupt
		xdef		_KBD_interrupt
		xdef		_KBD_scancode_var
		xdef		_mouse_buttons_var
		xdef		_State_mouse_dx_var
		xdef		_State_mouse_dy_var

;--------------------------------------------------------------------------







_KBD_interrupt:
    movem.l d0,-(sp)               ; Save registers used by ISR

    ; Check if IKBD actually has data ready (bit 0 of status register)

    move.b  IKBD_STATUS,d0
    btst    #0,d0                  ; Test bit 0: 1=data ready, 0=no data
    beq.s   end_ISR                ; If no data, end IRSR



;falls through to KBD_or_MOUSE   



;==============================================================================
; KBD_or_MOUSE - Determine if byte is keyboard or mouse data
;==============================================================================
; Reads the byte from IKBD and checks if it's a mouse header (>= $F8)
; or a keyboard scancode (< $F8)
;==============================================================================



KBD_or_MOUSE: 
    clr.l    d0
    move.b   IKBD_DATA,d0

; Check if byte is a mouse header byte ($F8-$FF) or keyboard scancode

    cmp.b    #$F8,d0
    blt.s    KBD_scancode

; If we reach here: d0 >= $F8, so it's a mouse-related byte
; Check if we're in the middle of a mouse packet (counter != 0)

    move.b   counter_byte,d1         ; Load current state & below test if 0.
    tst.b    d1                        
    bne.s    mouse_state_machine    ; If counter != 0, we're mid-packet
    
; Counter is 0, so this is a new mouse header byte
; Fall through to mouse_HEADER_buttons



;==============================================================================
; mouse_HEADER_buttons - Process Mouse Packet Byte 1 (Header)
;==============================================================================
; Extracts button state from header byte (%11111brl)
; Sets counter to 1 to indicate next byte will be dx
;==============================================================================


mouse_HEADER_buttons:
    andi.b   #%00000111,d0          ; Mask to get brl bits
    move.b   d0,_mouse_buttons_var   ; Store button state
    addq.b   #1,counter_byte
    bra      end_ISR

; fall through to mouse_state_machine

;==============================================================================
; mouse_state_machine - Route to appropriate mouse packet byte handler
;==============================================================================
; Uses counter_byte to determine which byte of the packet we're processing
; counter = 1 → expecting dx (byte 2)
; counter = 2 → expecting dy (byte 3)
;==============================================================================

mouse_state_machine:
   cmp.b    #1,d1
    beq      State_mouse_dx
    bra      State_mouse_dy

;==============================================================================
; KBD_scancode - Process Keyboard Scancode
;==============================================================================
; Stores keyboard make or break code for later processing by main program
;==============================================================================

KBD_scancode:
    move.b   d0,_KBD_scancode_var
    bra      end_ISR

;==============================================================================
; State_mouse_dx - Process Mouse Packet Byte 2 (X Displacement)
;==============================================================================
; Stores signed X displacement
; Sets counter to 2 to indicate next byte will be dy
;==============================================================================

State_mouse_dx:
    move.b   d0,_State_mouse_dx_var
    addq.b   #1,counter_byte      
    bra      end_ISR


;==============================================================================
; State_mouse_dy - Process Mouse Packet Byte 3 (Y Displacement)
;==============================================================================
; Stores signed Y displacement
; Resets counter to 0 (packet complete, ready for next scancode/header)
;==============================================================================

State_mouse_dy:
    move.b   d0,_State_mouse_dy_var
    clr.b    counter_byte         ; Reset to 0 (packet complete)
    bra      end_ISR
    
;==============================================================================
; end_ISR - Clean up and return from interrupt
;==============================================================================
; CRITICAL: Must clear bit 6 of MFP ISRB register before returning
; or the ISR will never be called again
;==============================================================================

end_ISR:
    bclr    #6,MFP_ISRB             ; clear MFP in-service bit
    movem.l (sp)+,d0
    rte


;---------------------------------------------------------------------------
_KBD_scancode_var:      ds.b 1  ;Lastt keyboard scancode (make/break code)
_mouse_buttons_var:     ds.b 1  ; Mouse button state (bits 2-0: brl)
_State_mouse_dx_var:    ds.b 1  ; Mouse X displacement 
_State_mouse_dy_var:    ds.b 1  ; Mouse Y displacement 
counter_byte:          ds.b 1  ; State machine counter (0, 1, or 2)
;---------------------------------------------------------------------------
