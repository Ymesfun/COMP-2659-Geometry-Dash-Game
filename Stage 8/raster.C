/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: raster.c
 SUMMARY: Contains functions for all game raster graphics.
*******************************************************************************/
#include <osbind.h>
#include <stdio.h>
#include "GeoDash.h"
#include "raster.h"


void set_video_base_asm(UINT32 *base);


/*******************************************************************************
	PURPOSE: Plotting a 16 bit bitmap given a base pointer by finding the remainder bit_shift by anding 
    every bit outside of the MSB, and getting the word_offset by dividing our x coord by 16 and bit 
    shifting our y by multiplying it by 40. If we're on an aligned address, we just insert our bitmaps,
    otherwise we align by shifting the bits on the first and second bit to align the bitmap in.

	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
	OUTPUT: N/A
    ASSUMPTIONS: The function does no bounds checking for the bitmap. Caller is expected to do bounds
    checking on their end, for a 640x400 atari st screen. Obviously, this only supports 16 bit bitmaps 
    as given by the name. All x/y coordinates are based on the atari ST screen's pixel size.
*******************************************************************************/

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap) {
    int i = 0;

    int word_offset = (x >> 4) + ((y<<5)+(y<<3)); /* Word-aligned base offset */
    int bit_shift = x & 15; /* Offset within the 16-bit word */

    for (i = 0; i < SPRITE16_HEIGHT; i++) {
        UINT16 *pixel_addr = base + word_offset + ((i<<5)+(i<<3));
        if (bit_shift == 0) {
            /* Perfectly aligned on a 32-bit boundary */
            *pixel_addr |= bitmap[i];
        } else {
            /* Bitmap is split across two 32-bit words */
            pixel_addr[0] |= bitmap[i] >> bit_shift; /* First part in current word */
            pixel_addr[1] |= bitmap[i] << (16 - bit_shift); /* Remaining part in next word */
        }
    }
}

/*******************************************************************************
	PURPOSE: Plotting a 32 bit bitmap given a base pointer by finding the remainder bit_shift by anding 
    every bit outside of the MSB, and getting the word_offset by dividing our x coord by 32 and bit 
    shifting our y by multiplying it by 20. If we're on an aligned address, we just insert our bitmaps,
    otherwise we align by shifting the bits on the first and second bit to align the bitmap in.

	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
	OUTPUT: N/A
    ASSUMPTIONS: The function does no bounds checking for the bitmap. Caller is expected to do bounds
    checking on their end, for a 640x400 atari st screen. Obviously, this only supports 32 bit bitmaps 
    as given by the name. All x/y coordinates are based on the atari ST screen's pixel size.
*******************************************************************************/
    void plot_bitmap_32(unsigned long *base, int x, int y, const unsigned long *bitmap) {
        int i;
        int word_offset = (x >> 5) + ((y<<4)+(y<<2)); /* Word-aligned base offset */
        int bit_shift = x & 31; /* Offset within the 32-bit word */

        for (i = 0; i < SPRITE32_HEIGHT; i++) {
        unsigned long *pixel_addr = base + word_offset + ((i<<4)+(i<<2));

            if (bit_shift == 0) {
                /* Perfectly aligned on a 16-bit boundary */
                *pixel_addr |= bitmap[i];
            } else {
                /* Bitmap is split across two 32-bit words */
                pixel_addr[0] |= bitmap[i] >> bit_shift; /* First part in current word */
                pixel_addr[1] |= bitmap[i] << (32 - bit_shift); /* Remaining part in next word */
            }
        }
    }

    void plot_bitmap(unsigned long *base, int x, int y, const unsigned long *bitmap, 
                 int width, int height) {
    int i;
    int word_offset = (x >> 5) + ((y << 4) + (y << 2)); /* Word-aligned base offset */
    int bit_shift = x & 31; /* Offset within the 32-bit word */
    int words_per_row = (width + 31) >> 5; /* Number of 32-bit words per bitmap row */

    for (i = 0; i < height; i++) {
        unsigned long *pixel_addr = base + word_offset + ((i << 4) + (i << 2));
        const unsigned long *bitmap_row = bitmap + (i * words_per_row);
        
        int j;
        for (j = 0; j < words_per_row; j++) {
            if (bit_shift == 0) {
                /* Perfectly aligned on a 32-bit boundary */
                pixel_addr[j] |= bitmap_row[j];
            } else {
                /* Bitmap is split across two 32-bit words */
                pixel_addr[j] |= bitmap_row[j] >> bit_shift;
                pixel_addr[j + 1] |= bitmap_row[j] << (32 - bit_shift);
            }
        }
    }
}

/*******************************************************************************
	PURPOSE: Fully clearing our screen for when we need to update/refresh everything

	INPUT: 	N/A
	OUTPUT: N/A
    ASSUMPTIONS: This fully wipes out the screen one called. Expected this is what the caller wants.
*******************************************************************************/
/*
void clear_screen(unsigned long *base) {
	clr_scrn((long *)base);
}

*/
/*Dead function, gave it a bad name to kill it*/
void cleeeeer_screen(UINT32 *base) {
    int i;
   
    for (i = 0; i < 8000; i++) {
        base[i] = 0x00000000;   
    }
}

/*******************************************************************************
	PURPOSE: clearing a 16x16 region of our screen given a y and x coordinate

	INPUT: 	- y y coordinate you'd like to plot the bitmap at
			- x x coordinate you'd like to plot the bitmap at
	OUTPUT: N/A
    ASSUMPTIONS: The function does no bounds checking for the clear. Caller is expected to do bounds
    checking on their end, for a 640x400 atari st screen. Obviously, this only supports 16x16 region 
    clear as given by the name. All coordinates are based on the atari ST screen's pixel size
*******************************************************************************/
void screen_region_clear_16(int y, int x) {
    int i, offset;
    UINT16 *base = ( UINT16 *)get_video_base();
    int word_offset = (x >> 4) + ((y<<5)+(y<<3)); /* Word-aligned base offset */
    int bit_shift = y & 15; /* Offset within the 16-bit word */
    for (i = 0; i < SPRITE16_HEIGHT;  i++) {
    UINT16 *pixel_addr = base + word_offset + ((i<<5)+(i<<3));
        if (bit_shift == 0) {
            /* Perfectly aligned on a 16-bit boundary */
            *pixel_addr &= 0x0000;
        } else {
            /* Bitmap is split across two 32-bit words */
            pixel_addr[0] &= 0x0000 >> bit_shift; /* First part in current word */
            pixel_addr[1] &= 0x0000 << (16 - bit_shift); /* Remaining part in next word */
      }
    }
}

/*******************************************************************************
	PURPOSE: clearing a 32x32 region of our screen given a y and x coordinate

	INPUT: 	- y y coordinate you'd like to plot the bitmap at
			- x x coordinate you'd like to plot the bitmap at
	OUTPUT: N/A
    ASSUMPTIONS: The function does no bounds checking for the clear. Caller is expected to do bounds
    checking on their end, for a 640x400 atari st screen. Obviously, this only supports 32x32 region 
    clear as given by the name. All coordinates are based on the atari ST screen's pixel size
*******************************************************************************/
void screen_region_clear_32(UINT32 *base, int y, int x) {
    int i, offset;
    unsigned long *row;
    int word_offset = (x >> 5) + ((y<<4)+(y<<2)); /* Word-aligned base offset */
    int bit_shift = x & 31; /* Offset within the 16-bit word */
    for (i = 0; i < SPRITE32_HEIGHT;  i++) {
    unsigned long *pixel_addr = base + word_offset + ((i<<4)+(i<<2));
        if (bit_shift == 0) {
            /* Perfectly aligned on a 16-bit boundary */
            *pixel_addr &= 0x00000000;
        } else {
            /* Bitmap is split across two 32-bit words */
            pixel_addr[0] &= 0x00000000 >> bit_shift; /* First part in current word */
            pixel_addr[1] &= 0x00000000 << (32 - bit_shift); /* Remaining part in next word */
         }
    }
}
/*******************************************************************************
	PURPOSE: Drawing a straight line given a start pos to draw from, an end pos to stop at, and

	INPUT: 	- start where you want to start drawing at
            - end end position of line
			- y y coordinate you'd like to plot the line
	OUTPUT: N/A
    ASSUMPTIONS: The function does no bounds checking for the clear. Caller is expected to do bounds
    checking on their end, for a 640x400 atari st screen. This only draws a vertical line given a start,
    end, and y pos to draw at. start/end/y are expected to be atari pixel values.
*******************************************************************************/
void drawline(int start, int end, int y, UINT16 *base) {
    int offset = (y<<5) + (y<<3);  
    int i, word_index,bit_index;
    if (end <= start) return;
    for (i = start; i < end; i++) {
        word_index = i >> 4;            
        bit_index  = 15 - (i & 0xF);
        base[offset + word_index] |= (1 << bit_index);
    }
}

void draw_splash_screen(unsigned long splash_screen[], UINT32 *base) {
    int i;    
    /* Copy your splash screen */
    for (i = 0; i < 8000; i++) {
        base[i] = splash_screen[i];
    }
    
}


void update_progress_bar(Player *player, int goal_x_cord, UINT32 *base){
    static int progress_x = 0;  /* Tracks current progress bar position */
    static int last_player_x = 0;  /* Last recorded player position */

    int player_x = player->entity.x;
    
    /* Calculate how far player has progressed */
    if (player_x > 0) {
        /* Calculate progress as percentage: player position / goal position * bar width */
        progress_x = (player_x * 570) / goal_x_cord;
        
        /* Cap at max */
        if (progress_x > 570) {
            progress_x = 570;
        }
    }
    
    if (progress_x > 0) {
        drawline(30, 30 + progress_x, 75, (UINT16 *)base);
    }
}

/*******************************************************************************
	PURPOSE: Gets the value at VIDEO_BASE_HI and VIDEO_BASE_MI to find the start of our frame pointer.
	INPUT: 	N/A
	OUTPUT: UINT32 address
*******************************************************************************/
UINT32 get_video_base(){
    volatile UINT8 hi, mi;
    UINT32 address;
    long old_ssp = Super(0);
    hi = *(volatile UINT8*)VIDEO_BASE_HI; /*Grabs the two values at VIDEO_BASE_HI and MI*/
    mi = *(volatile UINT8*)VIDEO_BASE_MI;
    address = ((UINT32)hi << 16) | ((UINT32)mi << 8); /*Shifts them to get_vid_base address*/
    Super(old_ssp);
    return address;
}

void set_video_base(UINT32 *base){
    long old_ssp = Super(0);
    set_video_base_asm(base);
    Super(old_ssp);
}

