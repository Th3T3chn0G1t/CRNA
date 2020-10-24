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
 * Polls for and logs SDL & SDL library errors
 * Prefix is a message to be placed before the logged error
 * Should exit determines whether the program should exit if an error is found
 * Returns whether an error was found
 */
bool check_errors(const char* prefix, bool should_exit);

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
