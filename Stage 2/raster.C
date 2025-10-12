#include "raster.h"
#include <osbind.h>   

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height) {
    for (int i = 0; i < height; i++) {
        int offset = ((row + i) << 6) + ((row + i) << 4);  
        UINT16 *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}


void clear_screen(void) {
   
    unsigned long *base = (unsigned long *)Physbase();

    for (long i = 0; i < 8000; i++) {
        base[i] = 0x00000000;   
    }
}


void screen_region_clear( int y_cord, int x_cord) {
    UINT16 *base = ( UINT16 *)Physbase();
    for (int i = 0; i < height;  i++) {
        int offset = ((y_cord + i) << 6) + ((y_cord + i) << 4);  
        UINT16 *row = base + offset + x_cord;
        *row = 0x0000;   
    }
}


void drawine(int start, int end, int y){
    UINT16 *base = ( UINT16 *)Physbase();
    int i = 0;
    for (i = start; i< end; i++){
        if (start >=1 && end > start){
            

        }

    }
}