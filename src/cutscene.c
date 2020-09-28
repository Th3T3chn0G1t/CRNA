#include "include/cutscene.h"

cutscene_event_T* text_event(int msg) {
    return NULL;
}

cutscene_event_T* wait_event(int duration, animation_T* animation) {
    return NULL;
}

cutscene_event_T* move_event(game_object_T* target, int x, int y) {
    return NULL;
}

void do_event(cutscene_event_T* event) {

}

cutscene_T* cutscene(node_T* registry, bool autostep, bool allow_update, int count, ...) {
    return NULL;
}

void step(cutscene_T* cutscene) {

}
