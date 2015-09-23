//
//  ray0.c
//  
//
//  Created by reed on 9/23/15.
//
//

#include "png_wrapper.h"
#include <png.h>

#define WIDTH 512
#define HEIGHT 512

struct coord3 {
    float x, y, z;
};

struct ray3 {
    coord3 origin;
    coord3 dir;
};

ray3 screen_to_ray(int x, int y) {
    ray3 ray;
    ray.origin.x = x;
    ray.origin.y = y;
    ray.origin.z = 0;
    ray.dir.x = 0;
    ray.dir.y = 0;
    ray.dir.z = -1;
    return ray;
}

RGBPixel cast_ray(const ray3& ray __attribute__((unused))) {
    RGBPixel c = {1,0,0};
    return c;
}


int main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
    //#pragma unused(argc, argv)
    
    // create the bitmap and raycast to fill it
    RGBPixel *pixels = (RGBPixel*)malloc(WIDTH*HEIGHT*sizeof(RGBPixel));
    for (int y=0; y<HEIGHT/2; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            ray3 ray = screen_to_ray(x, y);
            RGBPixel color = cast_ray(ray);
            pixels[x+y*WIDTH] = color;
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


