#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "../../../engine/include/game_object.h"

typedef struct INTERACTABLE {
    game_object_T* object;
    animation_T** states;

    char** msg;
    int current_msg;
} interactable_T;

interactable_T* interactable(node_T* registry, int x, int y, int width, int height, char** msg, animation_T** animation);

#endif
