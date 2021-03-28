// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/camera_controller.h"

camera_controller_T* camera_controller(game_object_T* latch, context_T* control) {
    camera_controller_T* CAMERA_CONTROLLER = calloc(1, sizeof(struct CAMERA_CONTROLLER));

    CAMERA_CONTROLLER->latch = latch;
    CAMERA_CONTROLLER->control = control;

    return CAMERA_CONTROLLER;
}

void update_camera_pos(camera_controller_T* camera_controller) {
    int x = camera_controller->latch->x;
    int y = camera_controller->latch->y;

    int width = camera_controller->control->image->surface->w;
    int height = camera_controller->control->image->surface->h;

    if(x + camera_controller->control->offset_x < width / 2)
        camera_controller->control->offset_x += (width / 2) - (x + camera_controller->control->offset_x);
    else
        camera_controller->control->offset_x -= (x + camera_controller->control->offset_x) - (width / 2);
    if(y + camera_controller->control->offset_y < height / 2)
        camera_controller->control->offset_y -= (height / 2) - (y + camera_controller->control->offset_y);
    else
        camera_controller->control->offset_y -= (y + camera_controller->control->offset_y) - (height / 2);
}
