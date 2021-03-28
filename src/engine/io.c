// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

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
