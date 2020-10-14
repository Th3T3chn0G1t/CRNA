#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct NODE {
    void* data;
    void* next;
} node_T;

node_T* node(void* data);

void add(node_T* registry, void* data);

void* get(node_T* registry, int index);

void set(node_T* registry, int index, void* data);

void foreach(node_T* registry, bool (*func) (void* data));

#endif
