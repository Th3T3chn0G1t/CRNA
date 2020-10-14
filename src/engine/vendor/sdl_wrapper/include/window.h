#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "logger.h"

typedef struct WINDOW {
    SDL_Window* window;
} window_T;

/**
 * Creates a new window of size 100x100 with the title "Default"
 */  
window_T* window();

/**
 * Polls for events from the system
 * Do not call directly unless you need mid-frame event polling
 */
void poll(window_T* window);

/**
 * Sets the visibility of the window
 * Does not take effect until next poll() call
 */
void set_visible(window_T* window, bool visible);
/**
 * Sets the visibility of window decorations
 * Does not take effect until next poll() call    
 */
void set_decorated(window_T* window, bool decorated);
/**
 * Sets the fullscreen status of the window
 * Does not take effect until next poll() call    
 */
void set_fullscreen(window_T* window, bool fullscreen);

/**
 * Sets the position of the window
 * Does not take effect until next poll() call    
 */
void set_position(window_T* window, int x, int y);
/**
 * Sets the size of the window
 * Does not take effect until next poll() call    
 */
void set_size(window_T* window, int width, int height);

/**
 * Sets the title of the window
 * Does not take effect until next poll() call    
 */
void set_title(window_T* window, const char* title);

#endif
