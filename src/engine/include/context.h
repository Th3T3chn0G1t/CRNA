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
 * Fills a rectangle using the current foreground color
 * @param context The context to peform this operation on
 * @param x The x position to start filling the shape at
 * @param y The y position to start filling the shape at
 * @param width The x extent to which the shape should be filled
 * @param height The y extent to which the shape should be filled
 */
void fill_rect(context_T* context, int x, int y, int width, int height);

/**
 * Samples an image and draws it to the screen
 * @param context The context to peform this operation on
 * @param image The image to sample from
 * @param x The x position to start filling the shape at
 * @param y The y position to start filling the shape at
 */
void draw_image(context_T* context, image_T* image, int x, int y);

/**
 * Draws a string using the current foreground color
 * @note To avoid allocation overheads - only use this for dynamic strings. For static strings create an image of the string using the text() function in image.h
 * @see image
 * @param context The context to peform this operation on
 * @param str The string to be drawn
 * @param x The x position to start filling the shape at
 * @param y The y position to start filling the shape at
 */
void draw_string(context_T* context, const char* str, int x, int y);

/**
 * Draws a string using the current foreground color, allowing wrapping and newline chars
 * @param context The context to peform this operation on
 * @param str The string to be drawn
 * @param x The x position to start filling the shape at
 * @param y The y position to start filling the shape at
 * @param width The width at which the text will wrap
 */
void draw_string_bounded(context_T* context, const char* str, int x, int y, int width);

#endif
