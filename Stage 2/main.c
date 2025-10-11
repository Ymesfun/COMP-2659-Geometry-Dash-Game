#include <osbind.h>
#include <stdio.h>
#include "constant.h"
#include "raster.h"
#include "bitmaps.h"

int main(int argc, char const *argv[]) {
    UINT16 *base = (UINT16 *) Physbase();
    int x = 10, y = 50;

    // Draw the invader
    plot_bitmap_16(base, y, x, invader_bitmap, INVADER_HEIGHT);

    Cnecin();  // Wait for keypress
    return 0;
}