// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/window.h"

window_T* window() {
    window_T* WINDOW = calloc(1, sizeof(struct WINDOW));

    WINDOW->window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
    
    return WINDOW;
}

void poll(window_T* window) {
    SDL_UpdateWindowSurface(window->window);

    SDL_Event e;
    while(SDL_PollEvent(&e))
        switch(e.type) {
            case SDL_QUIT: {
                info("Quit requested by user");
                // TODO Are you sure? + saving
                exit(0);
                break;
            }
        }
}

void set_visible(window_T* window, bool visible) {
    visible ? SDL_ShowWindow(window->window) : SDL_HideWindow(window->window);
}

void set_decorated(window_T* window, bool decorated) {
    SDL_SetWindowBordered(window->window, decorated);
}

void set_fullscreen(window_T* window, bool fullscreen) {
    int w;
    int h;
    SDL_GetWindowSize(window->window, &w, &h);
    SDL_SetWindowFullscreen(window->window, fullscreen ? (w == 0 && h == 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN) : 0);
}


void set_position(window_T* window, int x, int y) {
    SDL_SetWindowPosition(window->window, x, y);
}

void set_size(window_T* window, int width, int height) {
    SDL_SetWindowSize(window->window, width, height);
}

void set_title(window_T* window, const char* title) {
    SDL_SetWindowTitle(window->window, title);
}
