/*
 * Copyright (C) 2020 - Benjamin Banerjee <kyraliancitizen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
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
