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

/*YM2149 Registers in stage 7*/
#define A_FINE 0
#define A_COARSE 1
#define B_FINE 2
#define B_COARSE 3
#define C_FINE 4
#define C_COARSE 5
#define NOISE 6
#define MIXER 7
#define A_VOL 8
#define B_VOL 9
#define C_VOL 10
#define ENVELOPE_FINEFREQ 11
#define ENVELOPE_ROUGHFREQ 12
#define ENVELOPE_SHAPE 13
/*These were made after I finalized function design:*/
#define CH_A 0
#define CH_B 1
#define CH_C 2
#define ENV_ENABLE 16
#define on 1
#define off 0

/* Notes on the YM2149 - Capital indicates major note, lowercase is minor*/
#define c_period 478
#define C_period 451
#define d_period 426
#define D_period 402
#define e_period 379
#define f_period 358
#define F_period 338
#define g_period 319
#define G_period 301
#define a_period 284
#define A_period 268
#define b_period 253

typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

typedef enum{
    false,
    true
}bool;

#endif