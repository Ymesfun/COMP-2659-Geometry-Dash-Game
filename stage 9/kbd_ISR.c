#include <osbind.h>
#include "kbd_ISR.h"

static void *old_ikbd_vector;

/* External references to assembly variables */
extern unsigned char KBD_scancode_var;
extern unsigned char mouse_buttons_var;
extern signed char State_mouse_dx_var;
extern signed char State_mouse_dy_var;
/*Type of vector*/
typedef void (*Vector)();
static Vector orig;
#define KBD_VECT 70

extern void KBD_interrupt();

void install_ikbd_isr(){
    long num = KBD_VECT;
    Vector *vectp = (Vector *)((long)num<<2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = KBD_interrupt;
    Super(old_ssp);
}

void restore_ikbd_isr() {
    long num = KBD_VECT;
    Vector *vectp = (Vector *)((long)num<<2);
    long old_ssp = Super(0);
    *vectp = orig;
    Super(old_ssp);
}
/*
void install_ikbd_isr() {
    long old_ssp = Super(0);
    void KBD_interrupt();
    
    /* Save old vector */
/*    old_ikbd_vector = *(void**)0x118;
    
    /* Install new vector */
/*    *(void**)0x118 = (void*)KBD_interrupt;
    
    Super(old_ssp);
}

void restore_ikbd_isr(void) {
    long old_ssp = Super(0);
    *(void**)0x118 = old_ikbd_vector;
    Super(old_ssp);
}
*/