#include "../engine/include/settings.h"
#include "../engine/include/crna.h"

void on_start(settings_T* settings, node_T** registry, game_T* game) {
    info("Started!");
}

bool on_update(game_T* game, node_T* registry, camera_controller_T* camera) {
    static bool echoed_gamestate = false;
    if(!echoed_gamestate) {
        print_gamestate_info();
        echoed_gamestate = true;
    }
    return true;
}

void on_destroy(node_T* registry) {
    printf("Shutting down...");
}

int main(int argc, char** argv) {
    crna_init(on_start, on_update, on_destroy);
}
