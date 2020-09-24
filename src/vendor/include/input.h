#ifndef KEY_INPUT_MANAGER_H
#define KEY_INPUT_MANAGER_H

#include <stdbool.h>

#include <SDL2/SDL.h>

typedef struct INPUT {
    const uint8_t* states;
} input_T;

/**
 * Creates a new input handler and populates it with the current keyboard state
 */
input_T* input();

/**
 * Returns the state of the specified key from the list of keys cached from last fetch() call
 */
bool get_keydown(input_T* input_manager, int keycode);

/**
 * Caches the current keyboard state
 * Do not call directly unless you need mid-frame keystate updating
 */
void fetch(input_T* input_manager);

#endif
