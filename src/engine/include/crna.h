#ifndef CRNA_H
#define CRNA_H

#define UNUSED(x) (void)(x)

/**
 * Common initialization function type
 */
#define start_function_T void (*start_func) (settings_T*, node_T**, game_T*)
/**
 * Common update function type
 */
#define update_function_T void (*update_func) (game_T*, node_T*, camera_controller_T*)
/**
 * Common deconstruction function type
 */
#define destroy_function_T void (*destroy_func) (node_T*)

#include "game.h"
#include "camera_controller.h"
#include "settings.h"

/**
 * Contains the neccesary data structures to manage a CRNA application
 * @see settings
 * @see game
 * @see camera_controller
 */ 
typedef struct CRNA {
    /**
     * Initialization and window settings
     */
    settings_T* settings;
    /**
     * Management struct for window, context and input
     */
    game_T* game;
    /**
     * A linked list of game objects
     * Acts as the 'scene'
     */
    node_T* registry;
    /**
     * The camera controller for the window context
     */
    camera_controller_T* cam;
    /**
     * The frame & ticking function for the program
     */
    update_function_T;
    /**
     * The deconstruction function for the program
     */
    destroy_function_T;
} crna_T;

/**
 * Creates a new CRNA application with a game context
 * @note This instantiates a static reference in the source file, subsequent calls will caused undefined behaviour
 * @param start_func The initialization function for the program
 * @param update_func The frame & ticking function for the program
 * @param destroy_func The deconstruction function for the program
 */
void crna_init(start_function_T, update_function_T, destroy_function_T);

/**
 * Prints information about the state of the application
 */
void print_gamestate_info();

#endif
