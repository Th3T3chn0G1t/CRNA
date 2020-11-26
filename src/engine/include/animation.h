#ifndef ANIMATION_H
#define ANIMATION_H

#include "../vendor/sdl_wrapper/include/image.h"

/**
 * Contains basic information for frame-by-frame rendering of sprite animations
 */
typedef struct ANIMATION {
    image_T** frames;
    int count;
    int current;
    int interval;
    int elapsed;
} animation_T;

/**
 * Creates a new animation with the provided array of frames and interval
 */
animation_T* animation(image_T** frames, int interval);

/**
 * Loads an animation from a list of file paths
 */
animation_T* direct_load_animation(SDL_PixelFormat* format, int interval, int count, ...);

/**
 * Attempts to advance the frame if interval is reached
 */
void advance_frame(animation_T* animation);

/**
 * Returns the current frame
 */
image_T* get_frame(animation_T* animation);

#endif
