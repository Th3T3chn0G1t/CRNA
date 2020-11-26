#ifndef CAMERA_H
#define CAMERA_H

#include "game_object.h"

/**
 * Controls a context (Which acts as a camera) such that it centres on the latched game object
 */
typedef struct CAMERA_CONTROLLER {
    game_object_T* latch;
    context_T* control;
} camera_controller_T;

/**
 * Creates a camera controller for the context and latches to the object
 */
camera_controller_T* camera_controller(game_object_T* latch, context_T* control);

/**
 * Updates the camera position to the current position of the latch object
 * Needs to be called after updating position of latch object
 */
void update_camera_pos(camera_controller_T* camera_controller);

#endif
