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
        set_clear(GAME->context, color(1.0f, 1.0f, 1.0f));
        set_color(GAME->context, color(0.0f, 0.0f, 0.0f));
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
