/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: bitmaps.c
 SUMMARY: Contains all game bitmaps. 
*************************************
******************************************/


#include "bitmaps.h"

/*******************************************************************************
	16x16 pixel bitmap ONLY for testing to demonstrate 16-bit raster bitmapping.
*******************************************************************************/

const UINT16 invader_bitmap[] = {
    0x0000, 0x0810, 0x0810, 0x0420,
    0x0240, 0x1FF8, 0x2004, 0x4662,
    0x4002, 0x43C2, 0x2424, 0x1008,
    0x0FF0, 0x0240, 0x0E70, 0x0000
};


/*******************************************************************************
	32x32 pixel bitmap of a sqaure for potential player/object collisions.
*******************************************************************************/

const unsigned long square[] = {
    0xFFFFFFFF,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x83F807E1,
    0x82100421,
    0x82100421,
    0x82100421,
    0x82100421,
    0x83F807E1,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x8FFFFFF1,
    0x8C000011,
    0x8C000011,
    0x8C000031,
    0x87FFFFF1,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0x80000001,
    0xFFFFFFFF
};


/*******************************************************************************
	32x32 pixel bitmap of a ground spike that the player cannot collide with.
*******************************************************************************/
const unsigned long ground_spike[] = {
    0x0003C000,
    0x0003C000,
    0x00066000,
    0x00042000,
    0x000DB000,
    0x00199800,
    0x001BE600,
    0x0033CC00,
    0x0037EC00,
    0x0067E600,
    0x006FF600,
    0x00CFF300,
    0x00DFFB00,
    0x019FF300,
    0x033FFCC0,
    0x033FFCC0,
    0x067FFCC0,
    0x067FFCC0,
    0x0CFFFF30,
    0x0CFFFF30,
    0x19FFFF98,
    0x19FFFF98,
    0x33FFFFCC,
    0x33FFFFCC,
    0x67FFFFE6,
    0xC7FFFFE3,
    0xC7FFFFE3,
    0x80000001,
    0x80000001,
    0xFFFFFFFF,
    0x00000000,
    0x00000000
};


/*******************************************************************************
	32x32 pixel bitmap of a ground block that the player can jump on but cannot collide with.
*******************************************************************************/
const unsigned long ground_block[] = {
    0xFFFFFFFF,
    0x80000001,
    0x80000001,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x80000001,
    0x80000001,
    0x80000001,
    0xFFFFFFFF   
};


/*******************************************************************************
	32x32 pixel bitmap of the portal  the player must collide with to win the game.
*******************************************************************************/
const unsigned long portal_bitmap[] = {
    0x00000000,
    0x001FFF00,
    0x1F03FF00,
    0x3C000F80,
    0x700C01C0,
    0xC7381C60,
    0x31000088,
    0x330C0198,
    0x741DB85E,
    0x68701C2C,
    0x6938009C,
    0xD187E198,
    0xD11C7196,
    0xD1300196,
    0x4923C892,
    0x5298D092,
    0x5213C892,
    0x49300192,
    0xD11C7196,
    0xD187E198,
    0xD1C00716,
    0x68701C2C,
    0x681DB80C,
    0x7418005E,
    0x33000098,
    0x31000088,
    0xC7381C60,
    0x700C01C0,
    0x3C000F80,
    0x1F03FF00,
    0x001FFF00,
    0x00000000,
};


/*******************************************************************************
	32x32 pixel bitmap for smaller crystal-like spikes.
*******************************************************************************/
const unsigned long crystal_spike[] = {


    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00080040,
    0x191400B3,
    0x5B72476C,
    0x7FF1E67A,
    0x4FF3BFFD,
    0x8FF7FFF9,
    0x9FFFFFFD,
    0x9FFFFFFE,
    0x3F7DF7EF,
    0xFB1E7FE7,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};

/*******************************************************************************
	32x32 pixel bitmap of the interactable platforms.
*******************************************************************************/
const unsigned long platform_bitmap[] = {
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0xFFFFFFFF,
    0x80000001,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x9FFFFFF9,
    0x8FFFFFF9,
    0x80000001,
    0x80000001,
    0xFFFFFFFF,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,

    /*******************************************************************************
	32x32 pixel bitmap of the hanging spikes.
*******************************************************************************/
};
const unsigned long hanging_spike[] = {
    
    0x00003000,
    0x00003000,
    0x00007800,
    0x00084000,
    0x00102000,
    0x00102000,
    0x01C00700,
    0x01000100,
    0x015FF500,
    0x015FF500,
    0x015FF500,
    0x015FF500,
    0x015FF500,
    0x013FF500,
    0x013FF500,
    0x013FF500,
    0x015FF500,
    0x015FF500,
    0x01000100,
    0x01000100,
    0x01BFB600,
    0x009FB400,
    0x00DFD800,
    0x005FA800,
    0x002BD200,
    0x002BD400,
    0x005B2000,
    0x005B4000,
    0x00630000,
    0x00220000,
    0x003C0000,
    0x000C0000,
};

unsigned long data[] = {
    0x00000000,
    0x00000000,
    0x0124A490,
    0x054A5408,
    0x01001020,
    0x00028000,
    0x000C2105,
    0x00000002,
    0x01248000,
    0x0444D000,
    0x05001300,
    0x1F2CC000,
    0x0200C042,
    0x001F0C00,
    0x001C0000,
    0x00000000,
    0x03FFFFFF,
    0x03FFFED8,
    0x03FFFFFF,
    0x02D554B0,
    0x03FFFFFF,
    0x03FFFFFF,
    0x03FFFFFF,
    0x00000000,
    0x00000000,
};