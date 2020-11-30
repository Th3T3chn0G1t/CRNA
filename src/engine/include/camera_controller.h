#ifndef CAMERA_H
#define CAMERA_H

#include "game_object.h"

/**
 * Controls a context such that it centres on the latched game object
 */
typedef struct CAMERA_CONTROLLER {
    /**
     * The context to be controlled
     */
    context_T* control;
    /**
     * The object to center on
     */
    game_object_T* latch;
} camera_controller_T;

/**
 * Creates a new camera controller
 * @param latch The object which the context should center on
 * @param control The context to be controlled
 * @return A heap pointer to the created struct
 */
camera_controller_T* camera_controller(game_object_T* latch, context_T* control);

/**
 * Updates the camera position to the current position of the latch object
 * @note Needs to be called after updating position of latch object
 * @param camera_controller The camera_controller to perform the operation on
 */
void update_camera_pos(camera_controller_T* camera_controller);

#endif
