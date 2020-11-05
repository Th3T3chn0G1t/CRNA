#include "include/settings.h"
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

    else
        return 0;

    return 1;
}

settings_T* settings_load(const char* file) {
    settings_T* settings = calloc(1, sizeof(struct SETTINGS));

    if(ini_parse(file, handler, settings))
        assert(0);

    return settings;
}
