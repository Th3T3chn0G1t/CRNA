#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

#define foreach_func bool (*func) (void*, void*), void* pass

/**
 * An object in a linked list
 * Also serves as base pointer type for a list
 */
typedef struct NODE {
    void* data;
    void* next;
} node_T;

/**
 * Creates a new node with the specified data
 */
node_T* node(void* data);

/**
 * Adds a new node with the specified data
 */
void add(node_T* list, void* data);

/**
 * Returns a node's data
 */
void* get(node_T* list, int index);

/**
 * Sets a node's data
 */
void set(node_T* list, int index, void* data);

/**
 * Executes the provided function for each item in the list
 */
void foreach(node_T* list, foreach_func);

/**
 * Calculates the length of the list
 */
int length(node_T* list);

#endif
