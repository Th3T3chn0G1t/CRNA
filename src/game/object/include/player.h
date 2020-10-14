#ifndef PLAYER_H
#define PLAYER_H

#include "../../../engine/include/game_object.h"
#include "../../../engine/vendor/sdl_wrapper/include/game.h"

#define MOVE_SPEED 4

typedef struct PLAYER {
    game_object_T* object;
    animation_T** animations;
} player_T;

player_T* player(node_T* registry, int x, int y, animation_T** animations);

#endif
