#include "include/linked_list.h"
#include "vendor/include/window.h"
#include "object/include/player.h"

/*
 * A reference the the game object
 * This holds references to the drawing context, window and input handlers
 */
game_T* game;

node_T* registry;

void frame() {
    // Clears the screen before drawing using the game->context->clear color
    clear(game->context);

    
    node_T* current = registry;
    do {
        game_object_T* o = (game_object_T*) current->data;
                
        if(!o)
          break;

        tick(o, game);
        render(o, game->context, game);

        if(!current->next)
            break;
            
        current = current->next;
    } while(1);
    
    // Update the screen, window and input states 
    update(game);
}

int main(int argc, char** argv) {
    // Initializes the game with a 1080x720 window in fullscreen with the title "SDL"
    game = init(1280, 800, false, "SDL");
    {
        set_decorated(game->window, false);
        set_position(game->window, 0, 0);    
    }
    
    registry = node(game_object(NULL, 0, 0, 64, 64, direct_load_animation(game->context->image->surface->format, 10, 2, "res/img/A.png", "res/img/B.png")));
    animation_T* player_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/flag.jpg");
    player(registry, 64, 64, &player_animation);

    if(!registry)
        exit(-1);

    // Rudimentary game loop
    start(frame, 60);
}