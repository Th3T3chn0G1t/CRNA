#ifndef ANIMATION_H
#define ANIMATION_H

#include "image.h"

/**
 * Contains basic information for frame-by-frame rendering of sprite animations
 */
typedef struct ANIMATION {
    /**
     * The number of frames supplied
     */
    int count;
    /**
     * The current frame
     */
    int current;
    /**
     * The number of updates since last frame change
     */
    int elapsed;
    /**
     * The frame data for the struct
     */
    image_T** frames;
    /**
     * The number of updates in-between frame changes
     */
    int interval;
} animation_T;

/**
 * Creates a new animation
 * @param frames The frame data to be managed
 * @param interval The number of calls to advance frame before the next frame is set
 * @return A heap pointer to the created struct
 */
animation_T* animation(image_T** frames, int interval);

/**
 * Loads an animation from the filesystem
 * @param format SDL_PixelFormat to use for the created frames
 * @param interval The number of calls to advance frame before the next frame is set
 * @param count The number of frames provided
 * @return A heap pointer to the created struct
 */
animation_T* direct_load_animation(SDL_PixelFormat* format, int interval, int count, ...);

/**
 * Attempts to advance the frame if interval is reached
 * @param animation The animation to perform the operation on
 */
void advance_frame(animation_T* animation);

/**
 * Returns the current frame
 * @param animation The animation to perform the operation on
 * @return A pointer to the current frame
 */
image_T* get_frame(animation_T* animation);

#endif
