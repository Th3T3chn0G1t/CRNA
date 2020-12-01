#include "include/crna.h"
#include <time.h>

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

static const char* SIGNAL_NAMES[32] = {
    "Invalid Signal",
    "Host Process Hangup",
    "User Interrupt",
    "Quit",
    "Illegal Instruction",
    "Trace Trap",
    "Abort",
    "Bus Error",
    "Floating-Point Error",
    "Invalid Signal Handler Call SIGKILL",
    "User Signal 1",
    "Segmentation Fault",
    "User Signal 2",
    "Broken Pipe",
    "Alarm",
    "Terminate",
    "Stack Fault",
    "Child Process Changed",
    "Continue",
    "Invalid Signal Handler Call SIGSTOP",
    "Stop",
    "Read from TTY",
    "Write to TTY",
    "Urgent Condition on Socket",
    "CPU Limit Exceeded",
    "File Size Limit Exceeded",
    "Timer Expired",
    "Timer Expired",
    "Window Size Changed",
    "IO Available",
    "Power Failure",
    "Bad Syscall"
};

void on_signal_received(int signal) {
    fatal(SIGNAL_NAMES[signal]);
}

void crna_init(start_function_T, update_function_T, destroy_function_T) {
    atexit(exit_callback);

    #ifdef __APPLE__
        for(int i = 1; i != __DARWIN_NSIG; i++)
            signal(i, on_signal_received);
    #endif

    CRNA = calloc(1, sizeof(struct CRNA));

    CRNA->settings = settings_load(".crna/game_settings.ini");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char pattern[255];
    sprintf(pattern, CRNA->settings->log_output_pattern, CRNA->settings->title, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    init_logger(pattern);

    CRNA->game = init(CRNA->settings->resX, CRNA->settings->resY, CRNA->settings->fullscreen, CRNA->settings->title);
    {
        set_decorated(CRNA->game->window, CRNA->settings->decorated);
        set_position(CRNA->game->window, CRNA->settings->posX, CRNA->settings->posY);    

        CRNA->game->context->font = font(CRNA->settings->font, CRNA->settings->font_size);
    }

    start_func(CRNA->settings, &(CRNA->registry), CRNA->game);

    CRNA->cam = camera_controller(get(CRNA->registry, 0), CRNA->game->context);

    CRNA->update_func = update_func;
    CRNA->destroy_func = destroy_func;

    start(frame_callback, CRNA->settings->framerate, CRNA);
}

void print_gamestate_info() {
    char msg[1024];
    sprintf(
        msg,
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
    debug(msg);
}
