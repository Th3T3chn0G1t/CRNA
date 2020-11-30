#ifndef CONTEXT_H
#define CONTEXT_H

#include "image.h"

/**
 * A mechanic for drawing to a surface/image
 */
typedef struct CONTEXT {
    /**
     * The image to draw for
     */
    image_T* image;

    /**
     * The clear color for drawing
     */
    color_T* clear;
    /**
     * The foreground color for drawing
     */
    color_T* foreground;

    /**
     * The font for drawing text
     */
    font_T* font;

    /**
     * The x offset by which to transform draw operations
     */
    int offset_x; 
    /**
     * The y offset by which to transform draw operations
     */
    int offset_y;
} context_T;

/**
 * Creates a new drawing context
 * @param surface The image to draw to
 * @return A heap pointer to the created struct
 */
context_T* context(image_T* surface);

/**
 * Clears the surface with the current clear color
 * @param context The context to peform this operation on
 */
void clear(context_T* context);

/**
 * Fills a rectangle in the surface with the current foreground color with the given dimensions
 * @param context The context to peform this operation on
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
 * Draws the given string str to the surface at the given position using the current foreground color
 */
void draw_string_bounded(context_T* context, const char* str, int x, int y, int width);

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
