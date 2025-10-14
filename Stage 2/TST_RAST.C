#include <osbind.h>
#include "raster.h"
#include "constant.h"

int main(int argc, char const *argv[]) {
    UINT16 *base16  = (UINT16 *) Physbase();
    unsigned long *base32 = (unsigned long *) Physbase();

    // 1. Draw and clear a 16-bit sprite
    plot_bitmap_16(base16, 50, 50, invader_bitmap);
    Cnecin();
    screen_region_clear_16(50, 50);
    Cnecin();

    // 2. Draw and clear a 32-bit sprite
    plot_bitmap_32(base32, 100, 100, ground_block);
    Cnecin();
    screen_region_clear_32(100, 100);
    Cnecin();

    // 3. Draw lines in middle and edges
    drawline(0, 639, 0);     // top edge
    drawline(0, 639, 399);   // bottom edge
    drawline(0, 639, 200);   // horizontal mid
    drawline(0, 399, 320);   // vertical mid
    Cnecin();

    // 4. Edge-case sprite draws
    plot_bitmap_16(base16, 0, 0, invader_bitmap);             // top-left
    plot_bitmap_16(base16, 639, 399, invader_bitmap);         // bottom-right (likely clipped)
    plot_bitmap_16(base16, -5, -5, invader_bitmap);           // off-screen negative
    plot_bitmap_16(base16, 640, 400, invader_bitmap);         // off-screen beyond
    plot_bitmap_32(base32, 300, 620, ground_block);           // partially off right edge
    plot_bitmap_32(base32, 390, 300, ground_block);           // partially off bottom edge
    Cnecin();

    // 5. Final full clear
    clear_screen();
    Cnecin();

    return 0;
}