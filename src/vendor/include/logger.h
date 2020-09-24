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

logger_T* init_logger(const char* path);

void log_base(const char* prefix, const char* str, int mode, int target, FILE* file);

void performance(logger_T* LOGGER, const char* str);
void debug(logger_T* LOGGER, const char* str);
void info(logger_T* LOGGER, const char* str);
void warning(logger_T* LOGGER, const char* str);
void error(logger_T* LOGGER, const char* str);
void fatal(logger_T* LOGGER, const char* str);

void test_all(logger_T* LOGGER);

#endif
