#include "include/crna.h"

static crna_T* CRNA;

bool update_object(void* data, void* pass) {
    game_object_T* o = (game_object_T*) data;
    
    if(!o)
        return false;

    tick(o, CRNA->game);
    update_camera_pos(CRNA->cam);
    render(o, CRNA->game->context, CRNA->game);
    
    return true;
}

uint32_t frame_callback(uint32_t time, void* pass) {
    clear(CRNA->game->context);

    foreach(CRNA->registry, update_object, CRNA);
    
    CRNA->update_func(CRNA->game, CRNA->registry, CRNA->cam);

    update(CRNA->game);

    return time;
}

void exit_callback() {
    SDL_DestroyWindow(CRNA->game->window->window);

    CRNA->destroy_func(CRNA->registry);

    SDL_Quit();
}

void on_close_signal_received(int signal) {
    exit(0);
}

void crna_init(start_function_T, update_function_T, destroy_function_T) {
    atexit(exit_callback);

    signal(SIGTERM, on_close_signal_received);
    signal(SIGQUIT, on_close_signal_received);
    signal(SIGINT, on_close_signal_received);
    signal(SIGABRT, on_close_signal_received);

    CRNA = calloc(1, sizeof(struct CRNA));

    CRNA->settings = settings_load(".crna/game_settings.ini");

    CRNA->game = init(CRNA->settings->resX, CRNA->settings->resY, CRNA->settings->fullscreen, CRNA->settings->title);
    {
        set_decorated(CRNA->game->window, CRNA->settings->decorated);
        set_position(CRNA->game->window, CRNA->settings->posX, CRNA->settings->posY);    

        set_font(CRNA->game->context, font(CRNA->settings->font, CRNA->settings->font_size));
    }

    start_func(CRNA->settings, &(CRNA->registry), CRNA->game);

    CRNA->cam = camera_controller(get(CRNA->registry, 0), CRNA->game->context);

    CRNA->update_func = update_func;
    CRNA->destroy_func = destroy_func;

    start(frame_callback, CRNA->settings->framerate, CRNA);
}

void print_gamestate_info() {
        printf(
"\
Gamestate Information\n\
\n\
Game Settings:\n\
\tResolution: %i x %i\n\
\tFramerate: %i\n\
\tPosition: %i, %i\n\
\tTitle: %s\n\
\tVersion: %s\n\
\tFullscreen?: %s\n\
\tDecorated?: %s\n\
\tFont: %s\n\
\tFont Size: %i\n\
Registry Length: %i\n\
Game:\n\
\tWindow: %s\n\
\tWindow Context: %s\n\
\tInput Context: %s\n\
Camera Controller:\n\
\tDrawing Context: %s\n\
\tLatch: %s\n\
",
        CRNA->settings->resX,
        CRNA->settings->resY,
        CRNA->settings->framerate,
        CRNA->settings->posX,
        CRNA->settings->posY,
        CRNA->settings->title,
        CRNA->settings->version,
        CRNA->settings->fullscreen ? "True" : "False",
        CRNA->settings->decorated ? "True" : "False",
        CRNA->settings->font,
        CRNA->settings->font_size,
        length(CRNA->registry),
        CRNA->game->window ? "Valid" : "Invalid",
        CRNA->game->context ? "Valid" : "Invalid",
        CRNA->game->input ? "Valid" : "Invalid",
        CRNA->cam->control ? "Valid" : "Invalid",
        CRNA->cam->latch ? "Valid" : "Invalid"
    );
}
