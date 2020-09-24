#include "include/linked_list.h"
#include <stdlib.h>

node_T* node(void* data) {
    node_T* node = calloc(1, sizeof(struct NODE));

    node->data = data;

    return node;
}

void add(node_T* registry, void* data) {
    while(registry->next)
        registry = registry->next;

    node_T* new = calloc(1, sizeof(struct NODE));
    new->data = data;

    registry->next = new;
}

void* get(node_T* registry, int index) {
    for(int i = 0; i < index && registry; i++)
        registry = registry->next;

    return registry->data;    
}

void set(node_T* registry, int index, void* data) {
    for(int i = 0; i < index && registry; i++)
        registry = registry->next;

    registry->data = data;
}
