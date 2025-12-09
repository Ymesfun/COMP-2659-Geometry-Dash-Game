
#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

#include "VBL_ISR.h"
#include "Kbd_ISR.h"
#include "raster.h"
#include "constant.h"
#include "model.h"

/* 
 * MouseDriver
 * Runs the mouse input loop and returns a selection code:
 *   1 → Start game
 *   2 → Quit game
 *   0 → No selection
 */
int MouseDriver(UINT32 *base);

/* Getters for mouse state */
int getMouseX();
/*int getMouseY();*/
int getMouseClick();


bool mouse_bound_check(unsigned int x,
                       unsigned int y,
                       unsigned int width,
                       unsigned int height);

#endif