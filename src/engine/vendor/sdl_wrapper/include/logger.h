#ifndef LOGGER_H
#define LOGGER_H

#define VERBOSE 0
#define SILENT 1

#define STDOUT 0
#define STDERR 1

#include <stdio.h>

typedef struct LOGGER {
    FILE* file;
    int performance_mode;
    int debug_mode;
    int info_mode;
    int warning_mode;
    int error_mode;
    int fatal_mode;
} logger_T;

void shutdown_logger();

void init_logger(const char* path);

void log_base(const char* prefix, const char* str, int mode, int target, FILE* file);

void performance(const char* str);
void debug(const char* str);
void info(const char* str);
void warning(const char* str);
void error(const char* str);
void fatal(const char* str);

#endif
