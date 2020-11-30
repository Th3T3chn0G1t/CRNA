#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

/**
 * Userspace function type for foreach() 
 */
#define foreach_func bool (*func) (void*, void*), void* pass

/**
 * An object in a linked list
 * Also serves as base pointer type for a list
 */
typedef struct NODE {
    /**
     * The data contained by this node
     */
    void* data;
    /**
     * The next node in the list
     */
    void* next;
} node_T;

/**
 * Creates a new node
 * @param data The data to be stored
 * @return A heap pointer to the created struct
 */
node_T* node(void* data);

/**
 * Creates a new node and adds it to a list
 * @param list The base pointer of the list to add to
 * @param data The data to be stored
 */
void add(node_T* list, void* data);

/**
 * Fetches a node's data from a list
 * @param list The base pointer of the list to get from
 * @param index The index to fetch
 * @return The data of the fetched node
 */
void* get(node_T* list, int index);

/**
 * Sets a node's data in a list
 * @param list The base pointer of the list to set into
 * @param index The index to set at
 * @param data The data to set
 */
void set(node_T* list, int index, void* data);

/**
 * Executes the a function for each item in the list
 * @param list The base pointer of the list
 * @param func The function to be called for each object
 */
void foreach(node_T* list, foreach_func);

/**
 * Calculates the length of the list
 * @param list The base pointer of the list
 * @return The length of the list
 */
int length(node_T* list);

#endif
