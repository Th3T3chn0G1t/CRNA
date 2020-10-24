#include "include/player.h"
#include "../include/dialog.h"

void player_tick(void* game_object, void* passthrough) {
    game_object_T* this = (game_object_T*) game_object;
    player_T* implementor = (player_T*) this->implementor;
    game_T* game = (game_T*) passthrough;

    if(get_keydown(game->input, SDL_SCANCODE_N)) {
        implementor->controls_locked = false;
        hide_dialog();
    }

    if(implementor->controls_locked)
        return;

    if(get_keydown(game->input, SDL_SCANCODE_W)) {
        this->y -= MOVE_SPEED;
        if(check_collide(implementor->object))
            this->y += MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_S)) {
        this->y += MOVE_SPEED;
        if(check_collide(implementor->object))
            this->y -= MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_A)) {
        this->x -= MOVE_SPEED;
        if(check_collide(implementor->object))
            this->x += MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_D)) {
        this->x += MOVE_SPEED;
        if(check_collide(implementor->object))
            this->x -= MOVE_SPEED;
    }

}

void player_render(void* game_object, context_T* context, void* passthrough) {
    draw_image(context, get_frame(((game_object_T*) game_object)->animation), ((game_object_T*) game_object)->x, ((game_object_T*) game_object)->y);
    advance_frame(((game_object_T*) game_object)->animation);
}

player_T* player(node_T** registry, int x, int y, animation_T** animations) {
    player_T* PLAYER = calloc(1, sizeof(struct PLAYER));

    PLAYER->object = game_object(registry, x, y, 64, 64, animations[0]);
    set_ticking_function(PLAYER->object, player_tick);
    set_render_function(PLAYER->object, player_render);

    PLAYER->animations = animations;

    set_implementor(PLAYER->object, PLAYER);

    return PLAYER;
}
