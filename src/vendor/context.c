#include "include/context.h"
#include "include/logger.h"

context_T* context(image_T* image) {
    context_T* context = calloc(1, sizeof(struct CONTEXT));
    
    context->image = image;

    return context;
}

void clear(context_T* context) {
    SDL_FillRect(context->image->surface, NULL, as_uint32(context->clear, context->image->surface->format));
}

void set_context_pixel(context_T* context, int x, int y, uint32_t pixel) {
    uint8_t* target_pixel = (uint8_t*) context->image->surface->pixels + y * context->image->surface->pitch + x * sizeof(uint32_t);
    *(uint32_t*) target_pixel = pixel;
}

void fill_rect(context_T* context, int x, int y, int width, int height) {
    SDL_LockSurface(context->image->surface);

    for(int i = x; i < x + width; i++)
        for(int j = y; j < y + height; j++)
            if(i > -1 && i < context->image->surface->w)
                if(j > -1 && j < context->image->surface->h)
                    set_context_pixel(context, i, j, as_uint32(context->foreground, context->image->surface->format));

    SDL_UnlockSurface(context->image->surface);
}

void draw_image(context_T* context, image_T* image, int x, int y) {
    SDL_LockSurface(context->image->surface);

    for(int i = x; i < x + image->surface->w; i++)
        for(int j = y; j < y + image->surface->h; j++)
            if(i > -1 && i < context->image->surface->w)
                if(j > -1 && j < context->image->surface->h) {
                    uint32_t pixel = get_pixel(image, i - x, j - y);
                    if(((uint8_t*) &pixel)[3])
                        set_context_pixel(context, i, j, pixel);
                    else if(pixel) {
                        set_context_pixel(context, i, j, as_uint32(context->foreground, context->image->surface->format));
                    }
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

