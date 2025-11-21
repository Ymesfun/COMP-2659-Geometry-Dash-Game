#ifndef CONSTANT_H
#define CONSTANT_H

/*Size defs for raster.c*/
#define SPRITE16_HEIGHT 16
#define SPRITE32_HEIGHT 32


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

#define GRAVITY -1 
#define JUMP_SPEED 12

#define ROW_SIZE 40
#define COL_SIZE 16 

typedef unsigned int UINT16;

typedef enum{
    false,
    true
}bool;

#endif