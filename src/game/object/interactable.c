#include "include/interactable.h"
#include "include/player.h"
#include "../include/dialog.h"

void interactable_tick(void* game_object, void* passthrough) {
    interactable_T* this = (interactable_T*) ((game_object_T* ) game_object)->implementor;
}

bool interactable_on_collide(void* game_object, void* other) {
    interactable_T* this = ((game_object_T*) game_object)->implementor;
    if(!this->msg[this->current_msg])
        this->current_msg--;
    show_dialog(this->msg[this->current_msg]);
    this->current_msg++;

    ((player_T*) (((game_object_T*) other)->implementor))->controls_locked = true;

    return true;
}

interactable_T* interactable(node_T** registry, int x, int y, int width, int height, char** msg, animation_T** states) {
    interactable_T* template_object = calloc(1, sizeof(struct INTERACTABLE));

    template_object->object = game_object(registry, x, y, width, height, *states);
    {
        set_ticking_function(template_object->object, interactable_tick);
        set_on_collide_function(template_object->object, interactable_on_collide);
        set_implementor(template_object->object, template_object);
    }

    template_object->states = states;
    template_object->msg = msg;

    return template_object;
}
