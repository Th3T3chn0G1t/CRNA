// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include "include/settings.h"
#include "include/logger.h"
#include <assert.h>
#include "vendor/inih/ini.h"

#define MATCH_KEYPAIR(s, k) strcmp(section, s) == 0 && strcmp(key, k) == 0
#define atob(str) !strcasecmp(str, "TRUE") ? true : false
#define btoa(b) b ? "true" : "false"

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

    else {
        printf("Pre-Load: Invalid keypair [%s].%s: %s\n", section, key, value);
        return 0;
    }

    return 1;
}

settings_T* settings_load(const char* file) {
    settings_T* settings = calloc(1, sizeof(struct SETTINGS));

    int result = ini_parse(file, handler, settings);
    if(result) {
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

        printf("Pre-Load: Failed to parse ini file %s. ", file);
        if(result == -1) {
            printf("File open error, writing new file\n");
            settings_save(settings, file);
        }
        else if(result == -2)
            printf("Memory allocation error\n");
        else
            printf("Parse error at line %i\n", result);
        
    }

    return settings;
}

void settings_save(settings_T* settings, const char* file) {
    FILE* settings_file = fopen(file, "w");
    fprintf(settings_file, " \
[user] \n\
title=%s \n\
version=%s \n\
 \n\
[window] \n\
resX=%i \n\
resY=%i \n\
posX=%i \n\
posY=%i \n\
framerate=%i \n\
fullscreen=%s \n\
decorated=%s \n\
 \n\
[rendering] \n\
font=%s \n\
font_size=%i \n\
 \n\
[debug] \n\
log_output_pattern=%s \n\
    ", 
        settings->title, 
        settings->version, 
        settings->resX, 
        settings->resY, 
        settings->posX, 
        settings->posY,
        settings->framerate,
        btoa(settings->fullscreen),
        btoa(settings->decorated),
        settings->font,
        settings->font_size,
        settings->log_output_pattern
    );
    fflush(settings_file);
    fclose(settings_file);
}
