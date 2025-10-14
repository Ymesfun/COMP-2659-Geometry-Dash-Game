#include "raster.h"
#include <osbind.h>   

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap) {
    int i = 0;
    for (i = 0; i < SPRITE16_HEIGHT; i++) {
        int offset = ((row+i)<<5) + ((row+i)<<3);
        UINT16 *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}

void plot_bitmap_32(unsigned long *base, int row, int col, const unsigned long *bitmap) {
    int i = 0;
    for (i = 0; i <  SPRITE32_HEIGHT; i++) {
       int offset = ((row+i)<<4) + ((row+i)<<2); 
        unsigned long *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}
void clear_screen() {
   
    unsigned long *base = (unsigned long *)Physbase();
    int i = 0;
    for (i = 0; i < 8000; i++) {
        base[i] = 0x00000000;   
    }
}


void screen_region_clear_16(int y_cord, int x_cord) {
    UINT16 *base = ( UINT16 *)Physbase();
    int i = 0;
    for (i = 0; i < SPRITE16_HEIGHT;  i++) {
        int offset = ((y_cord+i)<<5) + ((y_cord+i)<<3);
        UINT16 *row = base + offset + x_cord;
        *row = 0x0000;   
    }
}

void screen_region_clear_32(int y_cord, int x_cord) {
    unsigned long *base = ( unsigned long *)Physbase();
    int i = 0;
    for (i = 0; i < SPRITE32_HEIGHT;  i++) {
        int offset = ((y_cord+i)<<4) + ((y_cord+i)<<2);
        unsigned long *row = base + offset + x_cord;
        *row = 0x00000000;   
    }
}

void drawline(int start, int end, int y) {
    UINT16 *base = (UINT16 *)Physbase();
    int offset = (y<<5) + (y<<3);  
    int i = 0;
    if (end <= start) return;
    for (i = start; i < end; i++) {
        int word_index = i >> 4;            
        int bit_index  = 15 - (i & 0xF);
        base[offset + word_index] |= (1 << bit_index);
    }
}