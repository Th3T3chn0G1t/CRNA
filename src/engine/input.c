// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/input.h"

input_T* input() {
    input_T* INPUT_MANAGER = calloc(1, sizeof(struct INPUT));
 
    INPUT_MANAGER->states = SDL_GetKeyboardState(NULL);

    return INPUT_MANAGER;
}

bool is_keydown(input_T* input_manager, int keycode) {
    return input_manager->states[keycode];
}

void fetch(input_T* input_manager) {
    input_manager->states = SDL_GetKeyboardState(NULL);
}
