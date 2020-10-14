#ifndef ANIMATION_H
#define ANIMATION_H

#include "../vendor/sdl_wrapper/include/image.h"

typedef struct ANIMATION {
    image_T** frames;
    int count;
    int current;
    int interval;
    int elapsed;
} animation_T;

animation_T* animation(image_T** frames, int interval);

animation_T* direct_load_animation(SDL_PixelFormat* format, int interval, int count, ...);

void advance_frame(animation_T* animation);

image_T* get_frame(animation_T* animation);

#endif
