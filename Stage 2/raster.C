#include "raster.h"
#include <osbind.h>   

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap) {
    int i = 0;
    for (i = 0; i < SPRITE16_HEIGHT; i++) {
        int offset = ((row+i)<<word_leftshift) + ((row+i)<<word_rightshift); //leftshift+rightshift = mult by 80 
        UINT16 *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}

void plot_bitmap_32(unsigned long *base, int row, int col, const unsigned long *bitmap) {
    int i = 0;
    for (i = 0; i <  SPRITE32_HEIGHT; i++) {
       int offset = ((row+i)<<long_leftshift) + ((row+i)<<long_rightshift); //left+right shift = mult by 40
        unsigned long *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}
void clear_screen() {
   
    unsigned long *base = (unsigned long *)Physbase();
    int i = 0;
    for (i = 0; i < screensize_long; i++) { //screensize_long is screensize, = 8000
        base[i] = 0x00000000;   
    }
}


void screen_region_clear_16(int y_cord, int x_cord) {
    UINT16 *base = ( UINT16 *)Physbase();
    int i = 0;
    for (i = 0; i < SPRITE16_HEIGHT;  i++) {
        int offset = ((y_cord+i)<<word_leftshift) + ((y_cord+i)<<word_rightshift);
        UINT16 *row = base + offset + x_cord;
        *row = 0x0000;   
    }
}

void screen_region_clear_32(int y_cord, int x_cord) {
    unsigned long *base = ( unsigned long *)Physbase();
    int i = 0;
    for (i = 0; i < SPRITE32_HEIGHT;  i++) {
        int offset = ((y_cord+i)<<long_leftshift) + ((y_cord+i)<<long_rightshift);
        unsigned long *row = base + offset + x_cord;
        *row = 0x00000000;   
    }
}

void drawline(int start, int end, int y) {
    UINT16 *base = (UINT16 *)Physbase();
    int offset = (y<<word_leftshift) + (y<<word_rightshift);  
    int i = 0;
    if (end <= start) return;
    for (i = start; i < end; i++) {
        int word_index = i >> 4;            
        int bit_index  = 15 - (i & 0xF);
        base[offset + word_index] |= (1 << bit_index);
    }
}