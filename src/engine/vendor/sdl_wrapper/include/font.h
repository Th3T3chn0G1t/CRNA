#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

/**
 * Contains size information on a font's glyphs
 */
typedef struct FONT_METRICS {
    /**
     * The smallest width of a glyph
     */
    int minx;
    /**
     * The smallest height of a glyph
     */
    int miny;
    /**
     * The greatest width of a glyph
     */
    int maxx;
    /**
     * The greatest height of a glyph
     */
    int maxy;
    /**
     * The amount by which each glyph advances beyond the previous
     */
    int advance;
} font_metrics_T;

/**
 * Contains font data and metrics for rendering a font
 */
typedef struct FONT {
    /**
     * Font data loaded using SDL2_TTF
     */
    TTF_Font* font;
    /**
     * Size information on a font's glyphs
     */
    font_metrics_T* metrics;
} font_T;

/**
 * Creates a font from a .ttf file
 * @param path The path to the font file
 * @param size The point size of the font
 * @return A heap pointer to the created struct
 */
font_T* font(const char* path, int size);

#endif
