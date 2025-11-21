/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: TST_RAST.c
 SUMMARY: Contains thorough test cases for full screen clear, 32 bit region clear,
 16 bit region clear, line draw, and 32/16 bitmap plots.
*******************************************************************************/



#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"
#include "constant.h"

int main(int argc, char const *argv[]) {
    UINT16 *base16  = (UINT16 *) Physbase();
    unsigned long *base32 = (unsigned long *) Physbase();

    /* 1. Draw and clear a 16-bit sprite*/
    clear_screen();
    plot_bitmap_16(base16, 50, 50, invader_bitmap);
    Cnecin();
    screen_region_clear_16(50, 50);
    Cnecin();

    /* 2. Draw and clear a 32-bit sprite*/
    plot_bitmap_32(base32, 100, 100, ground_block);
    Cnecin();
    screen_region_clear_32(100, 100);
    Cnecin();

    /* 3. Draw lines in middle and edges*/
    drawline(0, 639, 0);     /* top edge*/
    drawline(0, 639, 399);   /* bottom edge*/
    drawline(0, 639, 200);   /* horizontal mid*/
    drawline(250, 550, 300); /* partitioned line*/
    Cnecin();
    clear_screen();
    

    /* 4. Edge-case sprite draws*/
    plot_bitmap_16(base16, 0, 0, invader_bitmap);             /*top-left*/ 
    Cnecin();             
    plot_bitmap_16(base16, 30, 300, invader_bitmap);         /* bottom left */
    Cnecin();
    plot_bitmap_16(base16, 16, 16, invader_bitmap);           /* adjacent to 16x16 space inavder*/
    Cnecin();
    plot_bitmap_32(base32, 250, 250, ground_block);           /* Slightly off center from middle*/
    Cnecin();
    plot_bitmap_32(base32, 300, 300, ground_block);           /* 50 off from 250*/
    Cnecin();
    plot_bitmap_32(base32, 608, 0, ground_block);           /* Bottom left*/
    Cnecin();
    plot_bitmap_32(base32, 0, 368, ground_block);           /* Top right*/
    Cnecin();
    plot_bitmap_32(base32, 320, 200, ground_block);           /* Dead center 32 bit bitmap*/
    Cnecin();

    /* 5. Final full clear*/
    clear_screen();
    Cnecin();

    return 0;
}