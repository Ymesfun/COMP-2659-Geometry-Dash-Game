#ifndef RASTER_H
#define RASTER_H

#include "constant.h"

// Draw a monochrome bitmap to screen memory
void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height);

#endif