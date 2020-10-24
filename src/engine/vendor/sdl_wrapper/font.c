#include "include/font.h"

font_T* font(const char* path, int size) {
    font_T* FONT = calloc(1, sizeof(struct FONT));

    FONT->font = TTF_OpenFont(path, size);

    if(FONT->font) {
        FONT->metrics = calloc(1, sizeof(struct FONT_METRICS));
        TTF_GlyphMetrics(FONT->font, 'a', &FONT->metrics->minx, &FONT->metrics->maxx, &FONT->metrics->miny, &FONT->metrics->maxy, &FONT->metrics->advance);
    }
    else {
        fprintf(stderr, "Failed to load font %s: %s\n", path, TTF_GetError());
    }
    
    return FONT;
}
