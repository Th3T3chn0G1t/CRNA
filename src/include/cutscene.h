#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "game_object.h"
#include "../vendor/include/game.h"

struct event_data {
    bool (*event) (game_T*, node_T*);
    bool complete;
};

typedef struct CUTSCENE {
    struct event_data** events;
    bool autostep;
    bool allow_update;
} cutscene_T;

cutscene_T* cutscene(node_T* registry, bool autostep, bool allow_update, int count, ...);

void step(cutscene_T* cutscene);

#endif
