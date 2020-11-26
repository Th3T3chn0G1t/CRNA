#ifndef SETTINGS_H
#define SETTINGS_H

#include "../vendor/sdl_wrapper/include/font.h"
#include <stdbool.h>

/**
 * Contains data for initializing and running and application
 * See .crna/game_settings.ini for details
 */
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

/**
 * Loads settings into the returned struct from the provided game settings ini file
 */
settings_T* settings_load(const char* file);

#endif
