#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "logger.h"

/**
 * Contains information about a window
 */
typedef struct WINDOW {
    /**
     * The window data
     */
    SDL_Window* window;
} window_T;

/**
 * Creates a new window of size 100x100 with the title "Default"
 * @return A heap pointer to the created struct
 */  
window_T* window();

/**
 * Polls for window events from the system
 * @note Do not call directly unless you need mid-frame event polling
 * @param window The window to perform this operation on
 */
void poll(window_T* window);

/**
 * Sets the visibility of the window
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param visible The new visibility of the window
 */
void set_visible(window_T* window, bool visible);
/**
 * Sets the visibility of window decorations
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param decorated The new visibility of the window decorations
 */
void set_decorated(window_T* window, bool decorated);
/**
 * Sets the fullscreen status of the window
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param fullscreen The new fullscreen state of the window
 */
void set_fullscreen(window_T* window, bool fullscreen);
/**
 * Sets the position of the window
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param x The new x position of the window
 * @param y The new y position of the window
 */
void set_position(window_T* window, int x, int y);
/**
 * Sets the size of the window
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param width The new x extent of the window
 * @param height The new y extent of the window
 */
void set_size(window_T* window, int width, int height);
/**
 * Sets the title of the window
 * @note Does not take effect until next poll() call
 * @param window The window to perform this operation on
 * @param title The new title for the window
 */
void set_title(window_T* window, const char* title);

#endif
