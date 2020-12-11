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

