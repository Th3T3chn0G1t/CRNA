#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "include/game_object.h"

typedef struct INTERACTABLE {
    game_object_T* object;
} interactable_T;

interactable_T* interactable(node_T* registry, int x, int y, int width, int height, animation_T* animation);

#endif