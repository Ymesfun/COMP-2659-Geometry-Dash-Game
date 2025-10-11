#ifndef CONSTANT_H
#define CONSTANT_H

// Screen layout (Atari ST high-res: 640x400, 1 bitplane)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define ROW_SIZE 40       // 640 pixels / 16 pixels per word = 40 words per row
#define COL_SIZE 16       // pixels per word

// Sprite dimensions (for your invader bitmap)
#define INVADER_WIDTH 16
#define INVADER_HEIGHT 16

// Type alias for clarity
typedef unsigned int UINT16;   // 16-bit word (matches ST screen memory word size)

#endif