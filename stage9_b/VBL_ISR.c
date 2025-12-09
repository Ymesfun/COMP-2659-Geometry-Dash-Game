#include <osbind.h>
#include "VBL_ISR.h"
#include "model.h"

static void *old_VBL_vector;
int render_request = 0; 

void Install_VBL_ISR() {
    long old_ssp = Super(0);
    
    /* Save old vector */
    old_VBL_vector = *(void**)0x70;
    
    /* Install new vector */
    *(void**)0x70 = (void*)vbl_isr;
    
    Super(old_ssp);
}

void restore__VBL_ISR_isr(void) {
    long old_ssp = Super(0);
    *(void**)0x70 = old_VBL_vector;
    Super(old_ssp);
}

void VBL_ISR(){
    render_request = 1;
    /*update_music();*/
}