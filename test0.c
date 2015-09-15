#include "png_wrapper.h"
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
    //#pragma unused(argc, argv)
    RGBPixel *pixels = malloc(256*200*sizeof(RGBPixel));
    for (int y=0; y<100; ++y) {
        for (int x=0; x<256; ++x) {
            pixels[x+y*256].red = 0x00;
            pixels[x+y*256].green = 0x00;
            pixels[x+y*256].blue = 0xff;
        }
    }

    RGBBitmap bitmap;
    bitmap.width = 256;
    bitmap.height = 200;
    bitmap.bytewidth = 256 * 3;
    bitmap.bytes_per_pixel = 3;
    bitmap.pixels = pixels;
    int err = save_png_to_file(&bitmap, "test0.png");
    printf("Error code:  %d\n", err);
    free(pixels);
    return 0;
}

