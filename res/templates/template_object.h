#ifndef TEMPLATE_OBJECT_H
#define TEMPLATE_OBJECT_H

#include "../../include/game_object.h"

typedef struct TEMPLATE_OBJECT {
    game_object_T* object;
} template_object_T;

template_object_T* template_object(node_T* registry, int x, int y, int width, int height, animation_T* animation);

#endif