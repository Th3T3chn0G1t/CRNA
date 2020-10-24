#include "../engine/include/linked_list.h"
#include "../engine/include/camera.h"
#include "../engine/vendor/sdl_wrapper/include/window.h"

#include "object/include/player.h"
#include "object/include/interactable.h"
#include "include/dialog.h"

game_T* game;

node_T* registry;

camera_T* cam;

bool update_object(void* data) {
    game_object_T* o = (game_object_T*) data;
                
    if(!o)
        return false;

    tick(o, game);
    update_camera_pos(cam);
    render(o, game->context, game);
    
    return true;
}

uint32_t frame_callback(uint32_t time, void* pass) {
    clear(game->context);

    foreach(registry, update_object);
    
    render_dialog(game->context);

    update(game);

    return time;
}

int main(int argc, char** argv) {
    game = init(1280, 800, false, "SDL");
    {
        set_decorated(game->window, false);
        set_position(game->window, 0, 0);    

        set_font(game->context, font("res/font/BPdotsSquareBold.ttf", 16));
    }

    char* msg[] = {(char*) 15, 
        "It is a table  (Press N to continue)",
        "It is still a table",
        "Yep, a table",
        "You really love interacting with this table",
        "The table is beginning to feel uncomfortable",
        "The table is considering legal action",
        "The table is in table court",
        "The table has a restraining order",
        "You can't be here!",
        "Stop in the name of the law!",
        "The table is beyond caring",
        "The table has accepted its fate",
        "Wait, what is this again?",
        "Oh yeah, it's a table",
        "It is a table"
    };

    animation_T* interactable_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/noteTable.png");
    interactable(&registry, 512, 512, 64, 64, msg, &interactable_animation);
    
    animation_T* player_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/temp.jpg");
    player(&registry, 640, 400, &player_animation);

    cam = camera(get(registry, 1), game->context);
    
    // Rudimentary game loop
    start(frame_callback, 60);
}
