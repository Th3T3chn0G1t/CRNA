// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/game_object.h"

game_object_T* game_object(node_T** registry, int x, int y, int width, int height, animation_T* animation) {
    game_object_T* object = calloc(1, sizeof(struct GAME_OBJECT));

    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    object->animation = animation;
    object->blacklisted = false;

    if(*registry) {
        add(*registry, object);
        object->registry = *registry;
    } 
    else
        *registry = node(object);
    
    return object;
}

bool check_collide(game_object_T* object) {
    node_T* current = object->registry;
    do {
        game_object_T* o = (game_object_T*) current->data;
        if((unsigned long) o == (unsigned long) object)
            goto next;
                
        if(!o)
            break;

        if(object->x + object->width > o->x)
            if(object->x < o->x + o->width)
                if(object->y + object->height > o->y)
                    if(object->y < o->y + o->height)
                        return on_collide(o, object);

        next:
        if(!current->next)
            break;
            
        current = current->next;
    } while(1);
    return false;
}

void tick(game_object_T* o, void* passthrough) {
    if(o->tick)
        o->tick(o, passthrough);
}

void render(game_object_T* o, context_T* context, void* passthrough) {
    if(o->render)
        o->render(o, context, passthrough);
    else {
        if(o->animation) {
            draw_image(context, get_frame(o->animation), o->x, o->y);
            advance_frame(o->animation);
        }
    }
}

bool on_collide(game_object_T* o, game_object_T* other) {
    if(o->on_collide)
        return o->on_collide(o, other);
    return false;
}
