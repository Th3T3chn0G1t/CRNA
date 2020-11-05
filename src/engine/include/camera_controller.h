#ifndef CAMERA_H
#define CAMERA_H

#include "game_object.h"

typedef struct CAMERA_CONTROLLER {
    game_object_T* latch;
    context_T* control;
} camera_controller_T;

camera_controller_T* camera_controller(game_object_T* latch, context_T* control);

void update_camera_pos(camera_controller_T* camera_controller);

#endif
