// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

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

void foreach(node_T* registry, bool (*func) (void*, void*), void* pass) {
    node_T* current = registry;
    do {
        if(!func(current->data, pass))
            break;

        if(!current->next)
            break;
            
        current = current->next;
    } while(1);
}

int length(node_T* registry) {
    node_T* current = registry;

    for(int i = 1; ; i++) {
        if(!current->next)
            return i;

        current = current->next;
    }
}
