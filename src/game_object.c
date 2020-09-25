#include "include/game_object.h"

game_object_T* game_object(node_T* registry, int x, int y, int width, int height, animation_T* animation) {
    game_object_T* object = calloc(1, sizeof(struct GAME_OBJECT));

    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    object->animation = animation;
    object->blacklisted = false;

    if(registry)
        add(registry, object);

    return object;
}

void tick(game_object_T* o, void* passthrough) {
    if(o->tick)
        o->tick(o, passthrough);
}

void render(game_object_T* o, context_T* context, void* passthrough) {
    if(o->render)
        o->render(o, context, passthrough);
    else {
        draw_image(context, get_frame(o->animation), o->x, o->y);
        advance_frame(o->animation);
    }
}

bool on_collide(game_object_T* o, game_object_T* other) {
    if(o->on_collide)
        return o->on_collide(o, other);
    return false;
}

void set_ticking_function(game_object_T* o, void (*tick) (void*, void*)) {
    o->tick = tick;
}

void set_render_function(game_object_T* o, void (*render) (void*, context_T*, void*)) {
    o->render = render;
}

void set_on_collide_function(game_object_T* o, bool (*on_collide) (void*, void*)) {
    o->on_collide = on_collide;
}

void set_implementor(game_object_T* o, void* implementor) {
    o->implementor = implementor;
}
