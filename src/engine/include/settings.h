#ifndef SETTINGS_H
#define SETTINGS_H

#include "../vendor/sdl_wrapper/include/font.h"
#include <stdbool.h>

/**
 * Contains data for initializing and running and application
 */
typedef struct SETTINGS {
    /**
     * The x position to create the application window at
     */
    int posX;
    /**
     * The y position to create the application window at
     */
    int posY;
    /**
     * The x resolution to create the application window at
     */
    int resX;
    /**
     * The y resolution to create the application window at
     */
    int resY;
    /**
     * Whether the created window should be fullscreen
     */
    bool fullscreen;
    /**
     * Whether the created window should be decorated
     */
    bool decorated;
    /**
     * The title for the created window and the name of the application
     */
    char* title;
    /**
     * The version of the application
     */
    char* version;
    /**
     * The framerate for the program
     */
    int framerate;
    /**
     * The default font to use for drawing text
     */
    char* font;
    /**
     * The default font size to use for drawing text
     */
    int font_size;
    /**
     * A fprintf pattern for log output 
     */
    char* log_output_pattern;
} settings_T;

/**
 * Loads settings from the provided game settings ini file
 * @param file The file to read from
 * @return A heap pointer to the created struct
 */
settings_T* settings_load(const char* file);

#endif
