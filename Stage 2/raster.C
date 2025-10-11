#include "raster.h"

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height) {
    for (int i = 0; i < height; i++) {
        int offset = ((row + i) << 6) + ((row + i) << 4);  // row * 80
        UINT16 *tempbase = base + offset + col;
        *tempbase |= bitmap[i];
    }
}