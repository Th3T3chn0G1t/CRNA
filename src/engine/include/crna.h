#ifndef CRNA_H
#define CRNA_H

#define start_function_T bool (*start_func) (settings_T*, node_T**, game_T*)
#define update_function_T void (*update_func) (game_T*, node_T*, camera_controller_T*)
#define destroy_function_T void (*destroy_func) (node_T*)

#include "../vendor/sdl_wrapper/include/game.h"
#include "camera_controller.h"
#include "settings.h"

/**
 * Contains the neccesary data structures to manage a CRNA application
 */ 
typedef struct CRNA {
    settings_T* settings;
    game_T* game;
    node_T* registry;
    camera_controller_T* cam;

    update_function_T;
    destroy_function_T;
} crna_T;

/**
 * Creates a new CRNA application with a game context
 */
void crna_init(start_function_T, update_function_T, destroy_function_T);

/**
 * Prints information about the state of the application
 */
void print_gamestate_info();

#endif