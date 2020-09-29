#ifndef CAMERA_H
#define CAMERA_H

#include "game_object.h"

typedef struct CAMERA {
    game_object_T* latch;
    context_T* control;
} camera_T;

camera_T* camera(game_object_T* latch, context_T* control);

void update_camera_pos(camera_T* camera);

#endif
