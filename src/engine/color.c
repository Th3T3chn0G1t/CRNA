// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/color.h"

color_T* color(float r, float g, float b) {
    color_T* COLOR = calloc(1, sizeof(struct COLOR));

    COLOR->r = r;
    COLOR->g = g;
    COLOR->b = b;

    return COLOR;
}

SDL_Color as_sdlcolor(color_T* color) {
    SDL_Color assdl = {(int) (0xFF * color->r), (int) (0xFF * color->g), (int) (0xFF * color->b), 0xFF};
    return assdl;
}

uint32_t as_uint32(color_T* color, SDL_PixelFormat* format) {
    return SDL_MapRGB(format, color->r * 0xFF, color->g * 0xFF, color->b * 0xFF);
}

