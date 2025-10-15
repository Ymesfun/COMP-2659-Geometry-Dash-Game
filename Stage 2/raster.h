#ifndef RASTER_H
#define RASTER_H

#include "constant.h"

#define word_leftshift 6
#define word_rightshift 4
#define long_leftshift 5
#define long_rightshift 3
#define screensize_long 8000

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap);

void plot_bitmap_32(unsigned long *base, int row, int col, const unsigned long *bitmap);

void clear_screen();

void screen_region_clear_16(int y_cord, int x_cord);

void screen_region_clear_32(int y_cord, int x_cord);

void drawline(int start, int end, int y);
#endif