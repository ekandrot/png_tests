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
    w.add_sphere({0,0,-1}, 0.5, {1,0,0,1});
    w.add_sphere({0.3,0.3,-1}, 0.3, {0,1,0,1});
    
    // create the bitmap and raycast to fill it
    RGBPixel *pixels = (RGBPixel*)malloc(WIDTH*HEIGHT*sizeof(RGBPixel));
    for (int y=0; y<HEIGHT; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            ray3 r0 = screen_to_ray(x+0.5, y+0.5);
            ray3 r1 = screen_to_ray(x, y);
            ray3 r2 = screen_to_ray(x, y+1);
            ray3 r3 = screen_to_ray(x+1, y);
            ray3 r4 = screen_to_ray(x+1, y+1);
            color4 c0 = w.cast_ray(r0);
            color4 c1 = w.cast_ray(r1);
            color4 c2 = w.cast_ray(r2);
            color4 c3 = w.cast_ray(r3);
            color4 c4 = w.cast_ray(r4);
            
            pixels[x+y*WIDTH] = to_srgb((c0+c1+c2+c3+c4)/5);
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


