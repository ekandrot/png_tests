#include <stdint.h>
#include <stdlib.h>

typedef struct _RGBPixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGBPixel;

typedef struct _RGBBitmap {
    RGBPixel *pixels;
    size_t width;
    size_t height;
    size_t bytewidth;
    uint8_t bytes_per_pixel;
} RGBBitmap;

/* Attempts to save PNG to file; returns 0 on success, non-zero on error. */
int save_png_to_file(RGBBitmap *bitmap, const char *path);

