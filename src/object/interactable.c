#include "include/interactable.h"

void interactable_tick(void* game_object, void* passthrough) {
    interactable_T* this = (interactable_T*) ((game_object_T* ) game_object)->implementor;
}

bool object_on_collide(void* game_object, void* other) {
    return check_collide(game_object);
}

interactable_T* interactable(node_T* registry, int x, int y, int width, int height, animation_T* animation) {
    interactable_T* template_object = calloc(1, sizeof(struct INTERACTABLE));

    template_object->object = game_object(registry, x, y, width, height, animation);

    return template_object;
}
