#include "include/game.h"
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
        set_clear(GAME->context, color(1.0f, 1.0f, 1.0f));
        set_color(GAME->context, color(0.0f, 0.0f, 0.0f));
    }

    GAME->input = input();

    return GAME;
}

void start(uint32_t (*func) (uint32_t time, void* pass), int n) {
    int delay = 1000 / n;

    #ifdef __APPLE__
       /* 
        * Apple doesn't like SDL threading
        */
        while(1) {
            func(0, NULL);
            SDL_Delay(delay);
        }
    #else
        SDL_AddTimer(delay, func, NULL);
    #endif    
}

void update(game_T* game) {
    fetch(game->input);
    poll(game->window);

    for(const char* err = SDL_GetError(); *err; err = SDL_GetError()) {
        /*
         * Fixing the bug being queried here: https://stackoverflow.com/questions/63983054/sdl-geterror-returning-an-undocumented-error-on-macos
         * Ignore errors with the following message "Unknown touch device id -1, cannot reset"
         */
        #ifdef __APPLE__
            if(err[IGNORE_0_INDEX] == IGNORE_0 && err[IGNORE_1_INDEX] == IGNORE_1)
                return;
        #endif

        fprintf(stderr, "An unknown error occurred during the frame: %s\n", err); 
        exit(-1);
    }
    
    for(const char* err = TTF_GetError(); *err; err = TTF_GetError()) {
        fprintf(stderr, "An unknown error occurred during the frame: %s\n", err); 
        exit(-1);
    }

    for(const char* err = IMG_GetError(); *err; err = IMG_GetError()) {
        fprintf(stderr, "An unknown error occurred during the frame: %s\n", err); 
        exit(-1);
    }
}
