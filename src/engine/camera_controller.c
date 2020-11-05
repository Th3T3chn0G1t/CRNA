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

    int ox = camera_controller->control->offset_x;
    int oy = camera_controller->control->offset_y;

    int width = camera_controller->control->image->surface->w;
    int height = camera_controller->control->image->surface->h;

    if(x + ox < width / 2)
        set_offset(camera_controller->control, ox + ((width / 2) - (x + ox)), oy);
    else if(x + ox > width / 2)
        set_offset(camera_controller->control, ox - ((x + ox) - (width / 2)), oy);

    if(y + oy < height / 2)
        set_offset(camera_controller->control, ox, oy + ((height / 2) - (y + oy)));
    else if(y + oy > height / 2)
        set_offset(camera_controller->control, ox, oy - ((y + oy) - (height / 2)));
}
