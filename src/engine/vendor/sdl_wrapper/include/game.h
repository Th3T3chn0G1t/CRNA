#ifndef GAME_H
#define GAME_H

#include "context.h"
#include "window.h"
#include "input.h"

typedef struct GAME {
    int framerate;
    int tickrate;

    context_T* context;
    window_T* window;
    input_T* input;
} game_T;

/**
 * Initialized a game by creating a window with the given parameters and creates a drawing context for the window
 */
game_T* init(int width, int height, bool fullscreen, char* title);

/**
 * Sets up a loop to call func at n calls per second roughly
 */
void start(uint32_t (*func) (uint32_t time, void* pass), int n);

/**
 * Updates input and renders the context to the window
 * DOES NOT poll for window events - you must do that in the MAIN THREAD
 */
void update(game_T* game);

#endif
