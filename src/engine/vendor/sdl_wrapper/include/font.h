#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

typedef struct FONT_METRICS {
    int minx;
    int miny;
    int maxx;
    int maxy;
    int advance;
} font_metrics_T;

typedef struct FONT {
    TTF_Font* font;

    font_metrics_T* metrics;
} font_T;

/**
 * Creates a font from the given .ttf file at the given pixel size
 */
font_T* font(const char* path, int size);

#endif
