// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/context.h"
#include "include/logger.h"

#include <assert.h>

context_T* context(image_T* image) {
    context_T* context = calloc(1, sizeof(struct CONTEXT));
    
    context->image = image;
    context->offset_x = 0;
    context->offset_y = 0;

    return context;
}

void clear(context_T* context) {
    SDL_FillRect(context->image->surface, NULL, as_uint32(context->clear, context->image->surface->format));
}

void fill_rect(context_T* context, int x, int y, int width, int height) {
    SDL_LockSurface(context->image->surface);

    x += context->offset_x;
    y += context->offset_y;
    for(int i = x; i < x + width; i++)
        for(int j = y; j < y + height; j++)
            set_pixel(context->image, i, j, as_uint32(context->foreground, context->image->surface->format));

    SDL_UnlockSurface(context->image->surface);
}

void draw_image(context_T* context, image_T* image, int x, int y) {
    SDL_LockSurface(context->image->surface);

    x += context->offset_x;
    y += context->offset_y;
    for(int i = x; i < x + image->surface->w; i++)
        for(int j = y; j < y + image->surface->h; j++) {
            uint32_t pixel = get_pixel(image, i - x, j - y);
            if(((uint8_t*) &pixel)[3])
                set_pixel(context->image, i, j, pixel);
        }   

    SDL_UnlockSurface(context->image->surface);
}

void draw_string(context_T* context, const char* str, int x, int y) {
    if(!strlen(str))
        return;

    image_T* txt = text(context->font, str, context->foreground);

    draw_image(context, txt, x, y);
}

void draw_string_bounded(context_T* context, const char* str, int x, int y, int width) {
    // Ensure string to draw is valid 
    assert(str);
    if(!strlen(str))
        return;

    draw_image(context, surface_image(TTF_RenderText_Blended_Wrapped(context->font->font, str, as_sdlcolor(context->foreground), width)), x, y);
}
