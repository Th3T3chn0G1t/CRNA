#include "include/image.h"
#include "include/logger.h"

#include <assert.h>
#include <SDL2/SDL_image.h>

image_T* surface_image(SDL_Surface* surface) {
    image_T* IMAGE = calloc(1, sizeof(struct IMAGE));

    IMAGE->surface = surface;
    if(!IMAGE->surface) {
        char msg[127];
        sprintf(msg, "Failed to create image from surface: %s", IMG_GetError());
        error(msg);
    }

    return IMAGE;   
}

image_T* image(const char* path, SDL_PixelFormat* format) {
    SDL_Surface* surface = IMG_Load(path);
    if(!surface) {
        char msg[127];
        sprintf(msg, "Failed to load image %s: %s", path, IMG_GetError());
        error(msg);
    }

    return surface_image(SDL_ConvertSurface(surface, format, 0));
}

image_T* text(font_T* font, const char* str, color_T* color) {
    return surface_image(TTF_RenderText_Solid(font->font, str, as_sdlcolor(color)));
}

uint32_t get_pixel(image_T* image, int x, int y) {
    int bpp = image->surface->format->BytesPerPixel;
    uint8_t *p = (uint8_t *) image->surface->pixels + y * image->surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(uint16_t *) p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(uint32_t *) p;
            break;

        default:
            return 0;
    }
}


void set_pixel(image_T* image, int x, int y, uint32_t pixel) {
    if(x > -1 && x < image->surface->w)
        if(y > -1 && y < image->surface->h) {
            uint8_t* target_pixel = (uint8_t*) image->surface->pixels + y * image->surface->pitch + x * sizeof(uint32_t);
            *(uint32_t*) target_pixel = pixel;
        }
}
