#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include "font.h"

/**
 * Contains the data and formatting of an image for rendering
 */
typedef struct IMAGE {
    /**
     * The image data
     */
    SDL_Surface* surface;
} image_T;

/**
 * Wraps an SDL_Surface as an image
 * @note Use only for special cases where only an SDL_Surface is available, otherwise use image() or text() instead
 * @param surface The surface to wrap
 * @return A heap pointer to the created struct
 */
image_T* surface_image(SDL_Surface* surface);

/**
 * Creates a new image from file
 * @note The format should be of the drawing surface not of the source image
 * @param path The path to the image file
 * @param format The destination pixel format for the image
 * @return A heap pointer to the created struct
 */
image_T* image(const char* path, SDL_PixelFormat* format);

/**
 * Creates an image from a string
 * @param font The font to use for drawing the text
 * @param str The string to draw
 * @param color The color to draw the string in
 * @return A heap pointer to the created struct
 */
image_T* text(font_T* font, const char* str, color_T* color);

/**
 * Gets a pixel from the image
 * @param image The image to perform this operation on
 * @param x The x position of the image to sample from
 * @param y The y position of the image to sample from
 * @return A uint32 of the color format RRGGBBAA where each letter is a byte
 */
uint32_t get_pixel(image_T* image, int x, int y);

/**
 * Sets the color of the pixel in the image
 * @param image The image to perform this operation on
 * @param x The x position of the image to write to
 * @param y The y position of the image to write to
 * @param pixel A uint32 of the color format RRGGBBAA where each letter is a byte
 */
void set_pixel(image_T* image, int x, int y, uint32_t pixel);

#endif
