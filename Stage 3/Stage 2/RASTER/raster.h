#ifndef RASTER_H
#define RASTER_H
#define ROW_SIZE 40       
#define COL_SIZE 16

#include "constant.h"


void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap);

void plot_bitmap_32(unsigned long *base, int x, int y, const unsigned long *bitmap);

void clear_screen();

void screen_region_clear_16(int y, int x);

void screen_region_clear_32(int y, int x);

void drawline(int start, int end, int y);
#endif