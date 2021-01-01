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
#include "include/settings.h"
#include "include/logger.h"
#include "assert.h"
#include "vendor/inih/ini.h"

#define MATCH_KEYPAIR(s, k) strcmp(section, s) == 0 && strcmp(key, k) == 0
#define atob(str) !strcasecmp(str, "TRUE") ? true : false

static int handler(void* pass, const char* section, const char* key, const char* value) {
    settings_T* settings = (settings_T*) pass;

    if(MATCH_KEYPAIR("user", "title"))
        settings->title = strdup(value);
    else if(MATCH_KEYPAIR("user", "version"))
        settings->version = strdup(value);

    else if(MATCH_KEYPAIR("window", "resX"))
        settings->resX = atoi(value);
    else if(MATCH_KEYPAIR("window", "resY"))
        settings->resY = atoi(value);
    else if(MATCH_KEYPAIR("window", "posX"))
        settings->posX = atoi(value);
    else if(MATCH_KEYPAIR("window", "posY"))
        settings->posY = atoi(value);
    else if(MATCH_KEYPAIR("window", "framerate"))
        settings->framerate = atoi(value);
    else if(MATCH_KEYPAIR("window", "fullscreen"))
        settings->fullscreen = atob(value);
    else if(MATCH_KEYPAIR("window", "decorated"))
        settings->decorated = atob(value);

    else if(MATCH_KEYPAIR("rendering", "font"))
        settings->font = strdup(value);
    else if(MATCH_KEYPAIR("rendering", "font_size"))
        settings->font_size = atoi(value);

    else if(MATCH_KEYPAIR("debug", "log_output_pattern"))
        settings->log_output_pattern = strdup(value);

    else
        return 0;

    return 1;
}

settings_T* settings_load(const char* file) {
    settings_T* settings = calloc(1, sizeof(struct SETTINGS));

    int result = ini_parse(file, handler, settings);
    if(result) {
        printf("Failed to parse ini file %s. ", file);
        if(result == -1)
            printf("File open error\n");
        else if(result == -2)
            printf("Memory allocation error\n");
        else
            printf("Parse error at line %i\nm", result);
        
        settings->title = "Error";
        settings->version = "Error";
        settings->resX = 640;
        settings->resY = 480;
        settings->posX = 0;
        settings->posY = 0;
        settings->framerate = 60;
        settings->fullscreen = false;
        settings->decorated = false;
        settings->font = "res/font/BPdotsSquareBold.ttf";
        settings->font_size = 16;
        settings->log_output_pattern = "logs/%s-%d-%02d-%02d %02d:%02d:%02d.log";
    }

    return settings;
}
