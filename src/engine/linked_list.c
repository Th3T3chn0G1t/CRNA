/*
 * Copyright (C) 2005 - Benjamin Banerjee <kyraliancitizen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
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
