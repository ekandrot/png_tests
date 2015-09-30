//
//  ray0.c
//  
//
//  Created by reed on 9/23/15.
//
//

#include "png_wrapper.h"
#include "world.h"
#include <png.h>

#define WIDTH 512
#define HEIGHT 512
#define SUBSAMPLING 4

ray3 screen_to_ray(double x, double y) {
    ray3 ray;
    ray.origin.x = 0;
    ray.origin.y = 0;
    ray.origin.z = 5;
    ray.direction.x = 0.5*(2*(x/WIDTH) - 1);
    ray.direction.y = 0.5*(1 - 2*(y/HEIGHT));
    ray.direction.z = -ray.origin.z;
    ray.direction = unit_vector(ray.direction);
    return ray;
}


double srgbEncode(double c) {
    double x;
    if (c <= 0.0031308f) {
        x = 12.92f * c;
    } else {
        x = 1.055f * powf(c, 1/2.4) - 0.055f;
    }
    x *= 256;
    if (x<0) {
        x = 0;
    } else if (x>255) {
        x = 255;
    }
    return x;
}

// gamma corrected
RGBPixel to_srgb(color4 c) {
    // ignore alpha for now
    return {(uint8_t)(srgbEncode(c.r)), (uint8_t)(srgbEncode(c.g)), (uint8_t)(srgbEncode(c.b))};
}


int main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
    //#pragma unused(argc, argv)
    world w;
    w.add_sphere({0,0,-1}, 0.4, {1,0,0,1});
    w.add_sphere({0.3,0.3,-1}, 0.3, {0,1,0,1});
    
    // create the bitmap and raycast to fill it
    RGBPixel *pixels = (RGBPixel*)malloc(WIDTH*HEIGHT*sizeof(RGBPixel));
    for (int y=0; y<HEIGHT; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            color4 summingColor;
            for (int j=0; j<=SUBSAMPLING; ++j) {
                for (int i=0; i<=SUBSAMPLING; ++i) {
                    ray3 r = screen_to_ray(x+(1.0/SUBSAMPLING)*i, y+(1.0/SUBSAMPLING)*j);
                    color4 c = w.cast_ray(r);
                    summingColor += c;
                }
            }
            pixels[x+y*WIDTH] = to_srgb(summingColor/sqr(SUBSAMPLING+1));
        }
    }
    
    // save it as a PNG for now
    RGBBitmap bitmap;
    bitmap.width = WIDTH;
    bitmap.height = HEIGHT;
    bitmap.bytewidth = HEIGHT * 3;
    bitmap.bytes_per_pixel = 3;
    bitmap.pixels = pixels;
    int err = save_png_to_file(&bitmap, "ray0.png");
    printf("Error code:  %d\n", err);
    free(pixels);
    return 0;
}


