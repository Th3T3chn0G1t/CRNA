#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct NODE {
    void* data;
    void* next;
} node_T;

node_T* node(void* data);

void add(node_T* registry, void* data);

void* get(node_T* registry, int index);

void set(node_T* registry, int index, void* data);

#endif
