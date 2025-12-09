#include "VBL_ISR.h"
#include "Kbd_ISR.h"
#include "raster.h"
#include "constant.h"
#include "model.h"
/*Start game box*/
#define BUTTON1XLEFT  191
#define BUTTON1XRIGHT 262
#define BUTTON1Y   258
#define BUTTON1HEIGHT  34
/*Quit game box*/
#define BUTTON2XLEFT  191
#define BUTTON2XRIGHT 262
#define BUTTON2Y   339
#define BUTTON2HEIGHT  34

/*int getMouseX();*/
/*int getMouseY();*/
int getMouseClick();
bool mouse_bound_check(unsigned int x, unsigned int y, unsigned int width, unsigned int height); 
static int x = 320;
static int y = 200;
static int click;

int MouseDriver(UINT32 *base) {
    int selection = 0;

    while (selection == 0) {
         /*x = getMouseX();*/
        /*y = getMouseY();*/
        click = getMouseClick();

        /* draw cursor */
        plot_mouse_bitmap(base, x, y, mouse_unclicked);

        if (click) {
            /* Start game box */
            if (mouse_bound_check(BUTTON1XLEFT, BUTTON1Y,
                                  BUTTON1XRIGHT - BUTTON1XLEFT,
                                  BUTTON1HEIGHT)) {
                plot_bitmap_32(base, x, y, mouse_clicked);
                return 1;
            }
            /* Quit game box */
            else if (mouse_bound_check(BUTTON2XLEFT, BUTTON2Y,
                                       BUTTON2XRIGHT - BUTTON2XLEFT,
                                       BUTTON2HEIGHT)) {
                return 2;
            }
        }
        return 0;
    }
    return 0;
}
/*function: getMouseX
Purpose: returns mouse xposition and keeps pointer within bounds*/
/*
int getMouseX(){
    x = State_mouse_dx_var;
    if(x < 0)
    {
        x = 0;
        State_mouse_dx_var = 0;
    }else if(x > 608)
    {
        x = 608;
        State_mouse_dx_var = 608;
    }

    return x;
}
*/

/*function: getMouseClick
Purpose: returns the current state of mouse buttons*/
int getMouseClick()
{
    return mouse_buttons_var;
}


bool mouse_bound_check(unsigned int x, unsigned int y, unsigned int width, unsigned int height) 
{
    int mx = 0; /*getMouseX(); */
    int my = 0; /* getMouseY();*/


    if (mx >= (int)x && mx < (int)(x + width) &&
        my >= (int)y && my < (int)(y + height)) {
        return true;
    }
    return false;
}
