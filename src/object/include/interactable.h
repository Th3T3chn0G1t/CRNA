#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "../../include/game_object.h"
#include "../../vendor/include/game.h"

typedef struct INTERACTABLE {
    game_object_T* object;
    animation_T** animations;
    node_T* registry;
} interactable_T;

#endif