/*
 * Copyright (C) 2020 - Benjamin Banerjee <kyraliancitizen@gmail.com>
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
#include "include/io.h"
#include <stdlib.h>

char* read_line(const char* file, int line) {
    FILE* f = fopen(file, "r");

    char* msg = calloc(MAX_LINE_LEN, sizeof(char));
    size_t len;
    for(int i = 0; i < line; i++)
        getline(&msg, &len, f);

    fclose(f);
    return msg;
}

char* read_line_file(FILE* file, int line) {
    char* msg = calloc(MAX_LINE_LEN, sizeof(char));
    size_t len;
    for(int i = 0; i < line; i++)
        getline(&msg, &len, file);

    return msg;
}

char** read_lines(const char* file, int start, int count) {
    FILE* f = fopen(file, "r");

    char** msg = calloc(count - start, sizeof(char*));
    for(int i = 0; i < count - start; i++)
        msg[i] = calloc(MAX_LINE_LEN, sizeof(char));

    size_t len;
    for(int i = start; i < count; i++)
        getline(&msg[i - start], &len, f);

    fclose(f);
    return msg;
}

char** read_lines_file(FILE* file, int start, int count) {
    char** msg = calloc(count - start, sizeof(char*));
    for(int i = 0; i < count - start; i++)
        msg[i] = calloc(MAX_LINE_LEN, sizeof(char));

    size_t len;
    for(int i = start; i < count; i++)
        getline(&msg[i - start], &len, file);

    return msg;
}
