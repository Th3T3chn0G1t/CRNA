#include "template_object.h"

void template_object_tick(void* game_object, void* passthrough) {
    template_object_T* this = (template_object_T*) ((game_object_T* ) game_object)->implementor;
}

bool object_on_collide(void* game_object, void* other) {
    return check_collide(game_object);
}

template_object_T* template_object(node_T* registry, int x, int y, int width, int height, animation_T* animation) {
    template_object_T* template_object = calloc(1, sizeof(struct TEMPLATE_OBJECT));

    template_object->object = game_object(registry, x, y, width, height, animation);

    return template_object;
}
