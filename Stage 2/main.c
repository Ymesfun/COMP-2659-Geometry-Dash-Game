#include <osbind.h>
#include <stdio.h>
#include "constant.h"
#include "raster.h"
#include "bitmaps.h"

  
int main(int argc, char const *argv[]) {
    UINT16 *base16  = (UINT16 *) Physbase();
    unsigned long *base32 = (unsigned long *) Physbase();

   
    plot_bitmap_16(base16, 50, 50, invader_bitmap);
    Cnecin();
    screen_region_clear_16(50, 50);
    Cnecin();

    
    plot_bitmap_32(base32, 100, 100, ground_block);
    Cnecin();
    screen_region_clear_32(100, 100);
    Cnecin();

    
    drawline(0, 639, 0);     
    drawline(0, 639, 399);   
    drawline(0, 639, 200);   
    drawline(0, 399, 320);   
    Cnecin();

  
    plot_bitmap_16(base16, 0, 0, invader_bitmap);             
    plot_bitmap_16(base16, 639, 399, invader_bitmap);        
    plot_bitmap_16(base16, -5, -5, invader_bitmap);          
    plot_bitmap_16(base16, 640, 400, invader_bitmap);        
    plot_bitmap_32(base32, 300, 620, ground_block);           
    plot_bitmap_32(base32, 390, 300, ground_block);          
    Cnecin();

    clear_screen();
    Cnecin();

    return 0;
}
