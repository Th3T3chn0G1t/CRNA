#include "include/player.h"

void player_tick(void* game_object, void* passthrough) {
    game_object_T* o = (game_object_T*) game_object;
    game_T* game = (game_T*) passthrough;

    if(get_keydown(game->input, SDL_SCANCODE_W))
        o->y -= MOVE_SPEED;
    if(get_keydown(game->input, SDL_SCANCODE_S))
        o->y += MOVE_SPEED;
    if(get_keydown(game->input, SDL_SCANCODE_A))
        o->x -= MOVE_SPEED;
    if(get_keydown(game->input, SDL_SCANCODE_D))
        o->x += MOVE_SPEED;
}

player_T* player(node_T* registry, int x, int y, animation_T** animations) {
    player_T* PLAYER = calloc(1, sizeof(struct PLAYER));

    PLAYER->object = game_object(registry, x, y, 64, 64, animations[0]);
    set_ticking_function(PLAYER->object, player_tick);

    PLAYER->animations = animations;

    return PLAYER;
}
