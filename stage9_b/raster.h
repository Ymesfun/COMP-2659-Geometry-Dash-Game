#ifndef RASTER_H
#define RASTER_H
#define ROW_SIZE 40       
#define COL_SIZE 16

#include "constant.h"
#include "bitmaps.h"
#include "clr_qk.h"
#include "model.h" 

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap);

void plot_bitmap_32(unsigned long *base, int x, int y, const unsigned long *bitmap);

void cleeeeer_screen(UINT32 *base);

void screen_region_clear_16(int y, int x);

void screen_region_clear_32(UINT32 *base, int y, int x);

void drawline(int start, int end, int y);

void plot_bitmap(unsigned long *base, int x, int y, const unsigned long *bitmap, int width, int height);

void draw_splash_screen(unsigned long splash_screen[]);

void update_progress_bar(Player *player, int goal_x_cord, UINT32 *base);

void plot_mouse_bitmap(unsigned long *base, int x, int y, const unsigned long *bitmap);

#endif