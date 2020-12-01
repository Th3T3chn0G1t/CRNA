#ifndef GAME_H
#define GAME_H

#include "context.h"
#include "window.h"
#include "input.h"

/**
 * Game header update function
 * @note This is distinct from the CRNA.h update function and is not intended for userspace
 */
#define game_update_T uint32_t (*game_func) (uint32_t time, void* pass)

/**
 * A management struct for window, context and input operations
 */
typedef struct GAME {
    /**
     * Drawing context for the window's surface
     */
    context_T* context;
    /**
     * The application window
     */
    window_T* window;
    /**
     * Keyboard input manager
     */
    input_T* input;
} game_T;

/**
 * Initializes an application
 * @param width The x extent for the created window
 * @param height The y extend for the created window
 * @param fullscreen Whether the created window should be fullscreen
 * @param title The title for the created window
 * @return A heap pointer to the created struct
 */
game_T* init(int width, int height, bool fullscreen, char* title);

/**
 * Polls for and logs SDL & SDL library errors
 * @param prefix A message to be placed before the logged error
 * @param should_exit Determines whether the program should exit if an error is found
 * @return Whether an error was found
 */
bool check_errors(const char* prefix, bool should_exit);

/**
 * Sets up a loop for regular calling
 * @param game_func The function to be called
 * @param n The number of calls to game_func per second
 * @param pass A passthrough variable
 */
void start(game_update_T, int n, void* pass);

/**
 * Updates input and renders the context to the window
 * @param game The game to perform this operation on
 */
void update(game_T* game);

#endif
