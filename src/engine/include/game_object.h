#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "animation.h"
#include "linked_list.h"
#include "../vendor/sdl_wrapper/include/context.h"

#include <stdbool.h>

/**
 * Contains the basic data to handle collision and rendering for a basic sprite object
 * Allows for implementing types which define custom behaviours
 */
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

/**
 * Checks if the provided game object is colliding with any existing game objects in the provided object's stored registry
 * Automatically calls on_collide
 */
bool check_collide(game_object_T* o);

/**
 * Creates a new game object and adds it to the specified registry
 */
game_object_T* game_object(node_T** registry, int x, int y, int width, int height, animation_T* animation);

/**
 * Updates the object if a ticking function has been specified
 */
void tick(game_object_T* o, void* passthrough);

/**
 * Renders the object to the context
 * Calls alternative render function if specified, otherwise uses basic sprite rendering
 */
void render(game_object_T* o, context_T* context, void* passthrough);

/**
 * Calls collision handler if an on_collide function has been specified
 */
bool on_collide(game_object_T* o, game_object_T* other);

/**
 * Set the ticking function that will be called on each frame
 */
void set_ticking_function(game_object_T* o, void (*tick) (void*, void*));

/**
 * Override the rendering function that will be called on each frame
 */
void set_render_function(game_object_T* o, void (*render) (void*, context_T*, void*));

/**
 * Set the function that will be called on object collide
 */
void set_on_collide_function(game_object_T* o, bool (*on_collide) (void*, void*));

/**
 * Used by implementing types to allow for two-way referencing
 */
void set_implementor(game_object_T* o, void* implementor);

#endif
