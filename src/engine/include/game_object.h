#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "animation.h"
#include "linked_list.h"
#include "../vendor/sdl_wrapper/include/context.h"

#include <stdbool.h>

typedef struct GAME_OBJECT {
    int x, y;
    int width, height;
    animation_T* animation;
    bool blacklisted;

    void (*tick) (void*, void*);
    void (*render) (void*, context_T*, void*);
    bool (*on_collide) (void*, void*);

    void* implementor;
    node_T* registry;
} game_object_T;

game_object_T* game_object(node_T** registry, int x, int y, int width, int height, animation_T* animation);

void tick(game_object_T* o, void* passthrough);

void render(game_object_T* o, context_T* context, void* passthrough);

bool check_collide(game_object_T* o);

bool on_collide(game_object_T* o, game_object_T* other);

void set_ticking_function(game_object_T* o, void (*tick) (void*, void*));
void set_render_function(game_object_T* o, void (*render) (void*, context_T*, void*));
void set_on_collide_function(game_object_T* o, bool (*on_collide) (void*, void*));

void set_implementor(game_object_T* o, void* implementor);

#endif
