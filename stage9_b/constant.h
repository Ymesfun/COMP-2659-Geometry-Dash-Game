#ifndef CONSTANT_H
#define CONSTANT_H

/* Used in raster.c*/
#define SPRITE16_HEIGHT 16
#define SPRITE32_HEIGHT 32

/* Used in stage 3 */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define GROUND_BASE 338
#define PLATFORM_OFFSET 5
#define WIDTH_32LIMIT 608
#define HEIGHT_32LIMIT 368

/*Stage 4*/

#define GRND_RNDR 2 /*This should be the same level as the number of buffers youre drawing to.*/

/*Stage 5*/

#define JUMP_KEY 32

#define ROW_SIZE 40
#define COL_SIZE 16 
/*Stage 6*/

#define CLOCK_ADDR 0x462

typedef unsigned int UINT16;
typedef unsigned char UINT8;
typedef unsigned long UINT32;

typedef enum{
    false,
    true
} bool;



/* stage 9 */
#define ESC_SCANCODE    0x01
#define KEY_1_SCANCODE  0x02
#define KEY_2_SCANCODE  0x03
#define SPACE_SCANCODE  57


#endif