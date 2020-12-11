/*
 * Copyright (C) 2005 - Benjamin Banerjee <kyraliancitizen@gmail.com>
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
#include "include/game.h"
#include "include/logger.h"

#include "SDL2/SDL_image.h"

#ifdef __APPLE__
    #define IGNORE_0 '-'
    #define IGNORE_1 '1'
    #define IGNORE_0_INDEX 24
    #define IGNORE_1_INDEX 25
#endif

game_T* init(int width, int height, bool fullscreen, char* title) {
    game_T* GAME = calloc(1, sizeof(struct GAME));

    SDL_Init(SDL_INIT_VIDEO);

    #ifndef __APPLE__
        SDL_Init(SDL_INIT_TIMER);
    #endif

    TTF_Init();

    GAME->window = window(); 
    {
        set_size(GAME->window, width, height);
        set_title(GAME->window, title);
        set_fullscreen(GAME->window, fullscreen);
    }

    GAME->context = context(surface_image(SDL_GetWindowSurface(GAME->window->window)));
    {
        GAME->context->clear = color(1.0f, 1.0f, 1.0f);
        GAME->context->foreground = color(0.0f, 0.0f, 0.0f);
    }

    GAME->input = input();

    return GAME;
}

bool check_errors(const char* prefix, bool should_exit) {
    bool found_errors = false;
    for(const char* err = SDL_GetError(); *err; err = SDL_GetError()) {
        found_errors = true;
        /*
         * Fixing the bug being queried here: https://stackoverflow.com/questions/63983054/sdl-geterror-returning-an-undocumented-error-on-macos
         * Ignore errors with the following message "Unknown touch device id -1, cannot reset"
         */
        #ifdef __APPLE__
            if(err[IGNORE_0_INDEX] == IGNORE_0 && err[IGNORE_1_INDEX] == IGNORE_1)
                return false;
        #endif

        char msg[255];
        sprintf(msg, "%s %s\n", prefix ? prefix : "An unknown error occurred:", err); 
        error(msg);
        if(should_exit)
            exit(-1);
    }

    return found_errors;
}

void start(uint32_t (*func) (uint32_t time, void* pass), int n, void* pass) {
    check_errors("Failed to load correctly: ", true);
    
    int delay = 1000 / n;

    #ifdef __APPLE__
       /* 
        * Apple doesn't like SDL threading
        */
        while(1) {
            func(0, pass);
            
            SDL_Delay(delay);
        }
    #else
        // TODO Return condition
        SDL_AddTimer(delay, func, pass);
    #endif    
}

void update(game_T* game) {
    fetch(game->input);
    poll(game->window);
    check_errors(NULL, true);
}
