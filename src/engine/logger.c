// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2021 TTG <prs.ttg+crna@pm.me>

#include <stdlib.h>
#include "include/logger.h"

static logger_T* LOGGER;

void init_logger(const char* path) {
    LOGGER = calloc(1, sizeof(struct LOGGER));
    LOGGER->file = fopen(path, "w+");
}

void log_base(const char* prefix, const char* str, int mode, int target, FILE* file) {
    if(mode != VERBOSE)
        return;

    fputs(prefix, target == STDOUT ? stdout : stderr);
    fputs(str, target == STDOUT ? stdout : stderr);
    fputs("\n", target == STDOUT ? stdout : stderr);

    if(file) {
        fputs(prefix, file);
        fputs(str, file);
        fputs("\n", file);
    }
}

void performance(const char* str) {
    log_base("PERFORMANCE: ", str, LOGGER->performance_mode, STDOUT, LOGGER->file);
}

void debug(const char* str) {
    log_base("DEBUG: ", str, LOGGER->debug_mode, STDOUT, LOGGER->file);
}

void info(const char* str) {
    log_base("INFO: ", str, LOGGER->info_mode, STDOUT, LOGGER->file);
}

void warning(const char* str) {
    log_base("WARNING: ", str, LOGGER->warning_mode, STDERR, LOGGER->file);    
}

void error(const char* str) {
    log_base("ERROR: ", str, LOGGER->error_mode, STDERR, LOGGER->file);    
}

void fatal(const char* str) {
    log_base("FATAL: ", str, LOGGER->fatal_mode, STDERR, LOGGER->file);    
    exit(-1);
}
