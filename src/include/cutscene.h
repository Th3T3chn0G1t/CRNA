#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "game_object.h"
#include "../vendor/include/game.h"

enum event_type {
    TEXT,
    WAIT,
    MOVE
};

struct event_data {
    game_object_T* target;
    animation_T* animation;
    int duration;
    int x;
    int y;
};

typedef struct CUTSCENE_EVENT {
    enum event_type type;
    void* data;
    bool executed;
} cutscene_event_T;

cutscene_event_T* text_event(int msg);
cutscene_event_T* wait_event(int duration, animation_T* animation);
cutscene_event_T* move_event(game_object_T* target, int x, int y);

void do_event(cutscene_event_T* event);

typedef struct CUTSCENE {
    cutscene_event_T** events;
    bool autostep;
    bool allow_update;
} cutscene_T;

cutscene_T* cutscene(node_T* registry, bool autostep, bool allow_update, int count, ...);

void step(cutscene_T* cutscene);

#endif
