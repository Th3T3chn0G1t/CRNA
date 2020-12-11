#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

/**
 * A normalized color type
 */
typedef struct COLOR {
    /**
     * The red component of the color
     */
    float r;
    /**
     * The green component of the color
     */
    float g;
    /**
     * The blue component of the color
     */
    float b;
} color_T;

/**
 * Creates a color using the given normalized color values
 * @param r The red component of the color
 * @param g The green component of the color
 * @param b The blue component of the color
 * @return A heap pointer to the created struct
 */
color_T* color(float r, float g, float b);

/**
 * Converts a color_T* to an SDL_Color
 * @param color The color to perform the operation on
 * @return The converted color
 */
SDL_Color as_sdlcolor(color_T* color);

/**
 * Converts a color_T* to a uint32_t using the given pixel Format 
 * @note The color is in the format RRGGBBAA with each color being 8-bits
 * @param color The color to perform the operation on
 * @param format The color format to use for conversion
 * @return The converted color
 */
uint32_t as_uint32(color_T* color, SDL_PixelFormat* format);

#endif
