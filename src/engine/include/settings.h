#ifndef SETTINGS_H
#define SETTINGS_H

#include "../vendor/sdl_wrapper/include/font.h"
#include <stdbool.h>

typedef struct SETTINGS {
    int resX, resY;
    int posX, posY;
    bool fullscreen;
    bool decorated;
    char* title;
    char* version;
    int framerate;
    char* font;
    int font_size;
    char* log_output_pattern;
} settings_T;

settings_T* settings_load(const char* file);

#endif
