#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

typedef struct COLOR {
    float r;
    float g;
    float b;
} color_T;

/**
 * Creates a color using the given normalized color values
 */
color_T* color(float r, float g, float b);

/**
 * Converts a color_T* to an SDL_Color
 */
SDL_Color as_sdlcolor(color_T* color);

/**
 * Converts a color_T* to a uint32_t using the given pixel Format 
 */
uint32_t as_uint32(color_T* color, SDL_PixelFormat* format);

#endif
