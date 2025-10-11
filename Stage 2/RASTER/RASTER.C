#include <stdio.h>
#include <osbind.h>
#define INVADER_HEIGHT 16
#define INVADER_WIDTH 16
#define ROW_SIZE 80
#define COL_SIZE 16
typedef unsigned int UINT16;

UINT16 invader_bitmap[INVADER_HEIGHT] = {
	0x0000,
	0x0810,
	0x0810,
	0x0420,
	0x0240,
	0x1FF8,
	0x2004,
	0x4662,
	0x4002,
	0x43C2,
	0x2424,
	0x1008,
	0x0FF0,
	0x0240,
	0x0E70,
	0x0000
};

void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, unsigned int height){
	int iter;
	UINT16 *tempbase;
	for(iter = 0; iter<height; iter++){
		tempbase = base+(row+iter)*ROW_SIZE+col;
		*tempbase |= bitmap[iter];
	}
}

int main()
{
	int x = 0, y = 0; 
	UINT16 *base = (UINT16 *) Physbase();
	
	Cnecin();
	return 0;
}

void plot_pixel (char *base, int row, int col);

void trace()
{
	printf("inside trace!\n");
}
