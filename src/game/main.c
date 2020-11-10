#include "../engine/include/crna.h"
#include "../engine/include/io.h"

#include "object/include/player.h"
#include "object/include/interactable.h"
#include "include/dialog.h"

void on_start(settings_T* settings, node_T** registry, game_T* game) {
    char** msg = read_lines("res/lang/en-gb.lang", 1, 16);
    msg[16] = 0;

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
    info("Shutting down...");
}

int main(int argc, char** argv) {
    crna_init(on_start, on_update, on_destroy);
}
