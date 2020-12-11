/*
 * Copyright (C) 2020 - Benjamin Banerjee <kyraliancitizen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
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
