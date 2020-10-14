#include "include/font.h"

font_T* font(const char* path, int size) {
    font_T* FONT = calloc(1, sizeof(struct FONT));

    FONT->font = TTF_OpenFont(path, size);

    return FONT;
}
