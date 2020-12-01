#ifndef KEY_INPUT_MANAGER_H
#define KEY_INPUT_MANAGER_H

#include <stdbool.h>

#include <SDL2/SDL.h>

/**
 * Contains input data from the last fetch call
 */
typedef struct INPUT {
    const uint8_t* states;
} input_T;

/**
 * Creates a new input handler and populates it with the current keyboard state
 * @return A heap pointer to the created struct
 */
input_T* input();

/**
 * Gets the state of a key cached from last fetch() call
 * @param input_manager The input manager to perform this operation on
 * @param keycode The scancode of the key
 * @return The keystate 
 */
bool is_keydown(input_T* input_manager, int keycode);

/**
 * Caches the current keyboard state
 * Do not call directly unless you need mid-frame keystate updating
 * @param input_manager The input manager to perform this operation on
 */
void fetch(input_T* input_manager);

#endif
