#include "include/camera.h"

camera_T* camera(game_object_T* latch, context_T* control) {
    camera_T* CAMERA = calloc(1, sizeof(struct CAMERA));

    CAMERA->latch = latch;
    CAMERA->control = control;

    update_camera_pos(CAMERA);

    return CAMERA;
}

void update_camera_pos(camera_T* camera) {
    int x = camera->latch->x;
    int y = camera->latch->y;

    int ox = camera->control->offset_x;
    int oy = camera->control->offset_y;

    int width = camera->control->image->surface->w;
    int height = camera->control->image->surface->h;

    if(x + ox < width / 2)
        set_offset(camera->control, ox + ((width / 2) - (x + ox)), oy);
    else if(x + ox > width / 2)
        set_offset(camera->control, ox - ((x + ox) - (width / 2)), oy);

    if(y + oy < height / 2)
        set_offset(camera->control, ox, oy + ((height / 2) - (y + oy)));
    else if(y + oy > height / 2)
        set_offset(camera->control, ox, oy - ((y + oy) - (height / 2)));
}
