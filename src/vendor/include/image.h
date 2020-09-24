#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include "font.h"

typedef struct IMAGE {
    SDL_Surface* surface;
} image_T;

/**
 * Wraps the given surface as an image
 */
image_T* surface_image(SDL_Surface* surface);

/**
 * Creates a new image in memory from the given file to the given format
 * The format should be of the drawing surface not of the source image
 */
image_T* image(const char* path, SDL_PixelFormat* format);

/**
 * Creates an image with the given text str using the provided font and color
 */
image_T* text(font_T* font, const char* str, color_T* color);

/**
 * Gets a pixel from the specified x and y coordinate of the image
 * Return value is 4 uint8 values representing rgba all as a uint32
 */
uint32_t get_pixel(image_T* image, int x, int y);

/**
 * Sets the color of the pixel at the specified x and y coordinate in the image to pixel
 * Pixel should be 4 uint8 values representing rgba all as a uint32
 */
void set_pixel(image_T* image, int x, int y, uint32_t pixel);

#endif
