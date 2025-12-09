#ifndef VBL_ISR_H
#define VBL_ISR_H

void vbl_isr();

extern int render_request;

void Install_VBL_ISR();
void restore__VBL_ISR_isr();
#endif