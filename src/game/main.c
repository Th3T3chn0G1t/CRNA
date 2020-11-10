#include "../engine/include/linked_list.h"
#include "../engine/include/camera_controller.h"
#include "../engine/vendor/sdl_wrapper/include/window.h"

#include "object/include/player.h"
#include "object/include/interactable.h"
#include "include/dialog.h"
#include "../engine/include/settings.h"
#include "../engine/include/crna.h"

void on_start(settings_T* settings, node_T** registry, game_T* game) {
    const static char* msg[] = {(char*) 15, 
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
    interactable(registry, 512, 512, 64, 64, msg, &interactable_animation);
    
    animation_T* player_animation = direct_load_animation(game->context->image->surface->format, 0, 1, "res/img/temp.jpg");
    player(registry, 640, 400, &player_animation);
}

bool on_update(game_T* game, node_T* registry, camera_controller_T* camera) {
    static bool echoed_gamestate = false;
    if(!echoed_gamestate) {
        print_gamestate_info();
        echoed_gamestate = true;
    }

    camera->latch = get(registry, 1);

    render_dialog(game->context);
    return true;
}

void on_destroy(node_T* registry) {
    info("Shutting down...\n");
}

int main(int argc, char** argv) {
    crna_init(on_start, on_update, on_destroy);
}
