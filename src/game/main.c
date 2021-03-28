// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include <crna/crna.h>

void on_start(settings_T* settings, node_T** registry, game_T* game) {
    UNUSED(settings);
    UNUSED(registry);
    UNUSED(game);

    info("Game started");
}

void on_update(game_T* game, node_T* registry, camera_controller_T* camera) {
    UNUSED(game);
    UNUSED(registry);
    UNUSED(camera);

    static bool echoed_gamestate = false;
    if(!echoed_gamestate) {
        print_gamestate_info();
        echoed_gamestate = true;
    }
}

void on_destroy(node_T* registry) {
    UNUSED(registry);

    info("Shutting down...");
}

int main(int argc, char** argv, char** envp) {
    crna_init(on_start, on_update, on_destroy);
}
