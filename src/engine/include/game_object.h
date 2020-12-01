#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/**
 * Common object initialization function type
 */
#define object_update_function_T void (*tick) (void*, void*)
/**
 * Common object update function type
 */
#define object_render_function_T void (*render) (void*, context_T*, void*)
/**
 * Common object deconstruction function type
 */
#define object_collide_function_T bool (*on_collide) (void*, void*)

#include "animation.h"
#include "linked_list.h"
#include "../vendor/sdl_wrapper/include/context.h"

#include <stdbool.h>

/**
 * Contains the basic data to handle updating and rendering for a basic sprite object
 * Allows for implementing types which define custom behaviours
 */
typedef struct GAME_OBJECT {
    /**
     * The absolute x position of the object in the scene, may be translated by context or camera controller
     */
    int x;
    /**
     * The absolute y position of the object in the scene, may be translated by context or camera controller
     */
    int y;
    /**
     * The absolute x scale of the object
     */
    int width;
    /**
     * The absolute y scale of the object
     */
    int height;
    /**
     * The animation to use for sprite rendering of the object
     */
    animation_T* animation;
    /**
     * Whether this object should be ignored for calls to tick and render
     */
    bool blacklisted;
    /**
     * Overriding ticking function
     */
    object_update_function_T;
    /**
     * Overriding rendering function
     */
    object_render_function_T;
    /**
     * @deprecated DO NOT USE - new userspace physics soon
     */
    object_collide_function_T;
    /**
     * A pointer to the implementing struct 
     */
    void* implementor;
    /**
     * The registry this object is a part of
     */
    node_T* registry;
} game_object_T;

/**
 * Checks if the provided game object is colliding with any existing game objects in the provided object's stored registry
 * Automatically calls on_collide
 * @param o The object to check against
 * @return Whether there was a collision
 * @deprecated DO NOT USE - new userspace physics soon
 */
bool check_collide(game_object_T* o);

/**
 * Creates a new game object and adds it to the specified registry
 * @note Registry must point to your local storage of the base registry node. E.g. game_object(&my_reg_pointer, ...);
 * @param registry A pointer to the local storage of the base node of a registry - will initialize a null registry with the base node as the created object
 * @param x X position for the object
 * @param y Y position for the object
 * @param width X extent for the object
 * @param height Y extent for the object
 * @param animation Animation frame-by-frame rendering - nullable if overriden render function does not use 
 * @return A heap pointer to the created struct
 */
game_object_T* game_object(node_T** registry, int x, int y, int width, int height, animation_T* animation);

/**
 * Updates the object if a ticking function has been specified
 * @note Does not need to be called manually
 * @param o The game object to perform the operation on
 * @param passthrough The passthrough object to be called on the function
 */
void tick(game_object_T* o, void* passthrough);

/**
 * Renders the object to the context
 * Calls alternative render function if specified, otherwise uses basic sprite rendering
 * @param o The game object to perform the operation on
 * @param context The drawing context to render to
 * @param passthrough The passthrough object to be called on the function
 */
void render(game_object_T* o, context_T* context, void* passthrough);

/**
 * Calls collision handler if an on_collide function has been specified
 * @param o The game object to perform the operation on
 * @param other The game object colliding
 * @return whether the object should behave as solid
 * @deprecated DO NOT USE - new userspace physics soon
 */
bool on_collide(game_object_T* o, game_object_T* other);

#endif
