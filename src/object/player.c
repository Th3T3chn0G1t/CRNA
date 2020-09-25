#include "include/player.h"

bool check_collide(player_T* player) {
    game_object_T* this = player->object;
    node_T* current = player->registry;
    do {
        game_object_T* o = (game_object_T*) current->data;
        if((unsigned long) o == (unsigned long) this)
            goto next;
                
        if(!o)
            break;

        if(this->x + this->width > o->x)
            if(this->x < o->x + o->width)
                if(this->y + this->height > o->y)
                    if(this->y < o->y + o->height)
                        return on_collide(o, this);

        next:
        if(!current->next)
            break;
            
        current = current->next;
    } while(1);
    return false;
}

void player_tick(void* game_object, void* passthrough) {
    game_object_T* this = (game_object_T*) game_object;
    player_T* implementor = (player_T*) this->implementor;
    game_T* game = (game_T*) passthrough;

    if(get_keydown(game->input, SDL_SCANCODE_W)) {
        this->y -= MOVE_SPEED;
        if(check_collide(implementor))
            this->y += MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_S)) {
        this->y += MOVE_SPEED;
        if(check_collide(implementor))
            this->y -= MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_A)) {
        this->x -= MOVE_SPEED;
        if(check_collide(implementor))
            this->x += MOVE_SPEED;
    }
    if(get_keydown(game->input, SDL_SCANCODE_D)) {
        this->x += MOVE_SPEED;
        if(check_collide(implementor))
            this->x -= MOVE_SPEED;
    }
}

player_T* player(node_T* registry, int x, int y, animation_T** animations) {
    player_T* PLAYER = calloc(1, sizeof(struct PLAYER));

    PLAYER->object = game_object(registry, x, y, 64, 64, animations[0]);
    set_ticking_function(PLAYER->object, player_tick);

    PLAYER->animations = animations;
    PLAYER->registry = registry;

    set_implementor(PLAYER->object, PLAYER);

    return PLAYER;
}
