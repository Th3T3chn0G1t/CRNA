#ifndef CONTEXT_H
#define CONTEXT_H

#include "image.h"

typedef struct CONTEXT {
    image_T* image;

    color_T* clear;
    color_T* foreground;

    font_T* font;

    int offset_x, offset_y;
} context_T;

/**
 * Creates a new drawing context for drawing to the image's surface
 */
context_T* context(image_T* surface);

/**
 * Clears the surface with the current clear color
 */
void clear(context_T* context);

/**
 * Fills a rectangle in the surface with the current foreground color with the given dimensions
 */
void fill_rect(context_T* context, int x, int y, int width, int height);

/**
 * Draws the given image to the surface at the given location
 */
void draw_image(context_T* context, image_T* image, int x, int y);

/**
 * Draws the given string str to the surface at the given position using the current foreground color
 */
void draw_string(context_T* context, const char* str, int x, int y);

/**
 * Sets the clear color of the context
 */
void set_clear(context_T* context, color_T* color);

/**
 * Sets the foreground color of the context
 */
void set_color(context_T* context, color_T* color);

/**
 * Sets the active font of the context
 */
void set_font(context_T* context, font_T* font);

/**
 * Sets the offset at which drawing will occur
 */
void set_offset(context_T* context, int x, int y);

#endif
