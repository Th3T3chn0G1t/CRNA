/*
 * Copyright (C) 2020 - Benjamin Banerjee <kyraliancitizen@gmail.com>
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
#include "include/font.h"
#include "include/logger.h"

font_T* font(const char* path, int size) {
    font_T* FONT = calloc(1, sizeof(struct FONT));

    FONT->font = TTF_OpenFont(path, size);

    if(FONT->font) {
        FONT->metrics = calloc(1, sizeof(struct FONT_METRICS));
        TTF_GlyphMetrics(FONT->font, 'a', &FONT->metrics->minx, &FONT->metrics->maxx, &FONT->metrics->miny, &FONT->metrics->maxy, &FONT->metrics->advance);
    }
    else {
        char msg[127];
        sprintf(msg, "Failed to load font %s: %s\n", path, TTF_GetError());
        error(msg);
    }
    
    return FONT;
}
