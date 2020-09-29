#include "include/linked_list.h"
#include "include/camera.h"
#include "vendor/include/window.h"

#include "object/include/player.h"
#include "object/include/interactable.h"

game_T* game;

node_T* registry;

camera_T* cam;

void frame() {
    clear(game->context);
    
    node_T* current = registry;
    do {
        game_object_T* o = (game_object_T*) current->data;
                
        if(!o)
          break;

        tick(o, game);
        update_camera_pos(cam);
        render(o, game->context, game);

        if(!current->next)
            break;
            
        current = current->next;

    } while(1);
    
    update(game);
}

int main(int argc, char** argv) {
    game = init(1280, 800, false, "SDL");
    {
        set_decorated(game->window, false);
        set_position(game->window, 0, 0);    
    }

    set_font(game->context, font("res/font/BPdotsSquareBold.ttf", 16));
    
    registry = node(game_object(NULL, 0, 0, 0, 0, direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/0x0.png")));
    
    animation_T* interactable_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/A.png");
    interactable(registry, 512, 512, 64, 64, &interactable_animation);
    
    animation_T* player_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/B.png");
    player(registry, 640, 400, &player_animation);

    cam = camera(get(registry, 2), game->context);
    
    // Rudimentary game loop
    start(frame, 60);
}
