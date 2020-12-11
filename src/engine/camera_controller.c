/*
 * Copyright (C) 2005 - Benjamin Banerjee <kyraliancitizen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
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
