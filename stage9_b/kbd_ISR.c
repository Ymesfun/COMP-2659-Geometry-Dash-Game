#include <osbind.h>
#include "kbd_ISR.h"

static void *old_ikbd_vector;


void install_ikbd_isr(void) {
    long old_ssp = Super(0);
    extern void KBD_interrupt(void);
    
    /* Save old vector */
    old_ikbd_vector = *(void**)0x118;
    
    /* Install new vector */
    *(void**)0x118 = (void*)KBD_interrupt;
    
    Super(old_ssp);
}

void restore_ikbd_isr(void) {
    long old_ssp = Super(0);
    *(void**)0x118 = old_ikbd_vector;
    Super(old_ssp);
}