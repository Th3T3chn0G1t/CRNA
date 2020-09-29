#include "include/context.h"
#include "include/logger.h"

context_T* context(image_T* image) {
    context_T* context = calloc(1, sizeof(struct CONTEXT));
    
    context->image = image;
    context->offset_x = 0;
    context->offset_y = 0;

    return context;
}

void clear(context_T* context) {
    SDL_FillRect(context->image->surface, NULL, as_uint32(context->clear, context->image->surface->format));
}

void fill_rect(context_T* context, int x, int y, int width, int height) {
    SDL_LockSurface(context->image->surface);

    x += context->offset_x;
    y += context->offset_y;
    for(int i = x; i < x + width; i++)
        for(int j = y; j < y + height; j++)
            set_pixel(context->image, i, j, as_uint32(context->foreground, context->image->surface->format));

    SDL_UnlockSurface(context->image->surface);
}

void draw_image(context_T* context, image_T* image, int x, int y) {
    SDL_LockSurface(context->image->surface);

    x += context->offset_x;
    y += context->offset_y;
    for(int i = x; i < x + image->surface->w; i++)
        for(int j = y; j < y + image->surface->h; j++) {
            uint32_t pixel = get_pixel(image, i - x, j - y);
            if(((uint8_t*) &pixel)[3])
                set_pixel(context->image, i, j, pixel);
            else if(pixel)
                set_pixel(context->image, i, j, as_uint32(context->foreground, context->image->surface->format));
        }   

    SDL_UnlockSurface(context->image->surface);
}

void draw_string(context_T* context, const char* str, int x, int y) {
    image_T* txt = text(context->font, str, context->foreground);

    draw_image(context, txt, x, y);
}

void set_clear(context_T* context, color_T* color) {
    context->clear = color;
}

void set_color(context_T* context, color_T* color) {
    context->foreground = color;
}

void set_font(context_T* context, font_T* font) {
    context->font = font;
}

void set_offset(context_T* context, int x, int y) {
    context->offset_x = x;
    context->offset_y = y;
}
