#include "include/interactable.h"

void interactable_tick(void* game_object, void* passthrough) {
    interactable_T* this = (interactable_T*) ((game_object_T* ) game_object)->implementor;
}

bool interactable_on_collide(void* game_object, void* other) {
    return true;
}

interactable_T* interactable(node_T* registry, int x, int y, int width, int height, animation_T** states) {
    interactable_T* template_object = calloc(1, sizeof(struct INTERACTABLE));

    template_object->object = game_object(registry, x, y, width, height, *states);
    {
        set_ticking_function(template_object->object, interactable_tick);
        set_on_collide_function(template_object->object, interactable_on_collide);
        set_implementor(template_object->object, template_object);
    }

    template_object->states = states;

    return template_object;
}