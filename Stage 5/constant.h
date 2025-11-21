#ifndef CONSTANT_H
#define CONSTANT_H

/* Used in raster.c*/
#define SPRITE16_HEIGHT 16
#define SPRITE32_HEIGHT 32

/* Used in stage 3 */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define GROUND_BASE 338


#define JUMP_KEY 32

#define ROW_SIZE 40
#define COL_SIZE 16 

typedef unsigned int UINT16;

typedef enum{
    false,
    true
}bool;

#endif