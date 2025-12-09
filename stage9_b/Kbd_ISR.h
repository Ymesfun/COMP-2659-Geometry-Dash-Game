#ifndef KBD_ISR_H
#define KBD_ISR_H

extern unsigned char KBD_scancode_var;
extern unsigned char mouse_buttons_var;
extern signed char State_mouse_dx_var;
extern signed char State_mouse_dy_var;

void install_ikbd_isr();
void restore_ikbd_isr();

#endif