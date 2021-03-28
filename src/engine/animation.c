// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/animation.h"

#include <stdarg.h>

animation_T* animation(image_T** frames, int interval) {
    animation_T* animation = calloc(1, sizeof(struct ANIMATION));

    animation->frames = frames;
    animation->count = sizeof(frames) / sizeof(struct IMAGE);
    animation->interval = interval;
    animation->current = 0;
    animation->elapsed = 0;

    return animation;
}

animation_T* direct_load_animation(SDL_PixelFormat* format, int interval, int count, ...) {
    va_list sources;
    va_start(sources, count);

    image_T** frames = calloc(count, sizeof(image_T*));

    for(int i = 0; i < count; i++)
        frames[i] = image(va_arg(sources, const char*), format);
    
    va_end(sources);

    return animation(frames, interval);
}

void advance_frame(animation_T* animation) {
    if(animation->interval) {
        animation->elapsed++;
    
        if(animation->elapsed == animation->interval) {
            animation->current++;
            if(animation->current > animation->count)
                animation->current = 0;
            animation->elapsed = 0;
        }
        
    }
}

image_T* get_frame(animation_T* animation) {
    return animation->frames[animation->current];
}
