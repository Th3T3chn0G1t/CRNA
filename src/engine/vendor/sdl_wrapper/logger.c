#include <stdlib.h>
#include "include/logger.h"

logger_T* init_logger(const char* path) {
    logger_T* logger = calloc(1, sizeof(struct LOGGER));
    logger->file = fopen(path, "w+");
    return logger;
}

void log_base(const char* prefix, const char* str, int mode, int target, FILE* file) {
    switch(mode) {
        case VERBOSE:
            fputs(prefix, target == STDOUT ? stdout : stderr);
            fputs(str, target == STDOUT ? stdout : stderr);
            fputs("\n", target == STDOUT ? stdout : stderr);

            if(file) {
            fputs(prefix, file);
            fputs(str, file);
            fputs("\n", file);
            }
            break;
        case SILENT:
            return;
            break;
    }
}

void performance(logger_T* logger, const char* str) {
    if(logger)
        log_base("PERF: ", str, logger->performance_mode, STDOUT, logger->file);
}

void debug(logger_T* logger, const char* str) {
    if(logger)
        log_base("DEBG: ", str, logger->debug_mode, STDOUT, logger->file);
}

void info(logger_T* logger, const char* str) {
    if(logger)
        log_base("INFO: ", str, logger->info_mode, STDOUT, logger->file);
}

void warning(logger_T* logger, const char* str) {
    if(logger)
        log_base("WARN: ", str, logger->warning_mode, STDERR, logger->file);    
}

void error(logger_T* logger, const char* str) {
    if(logger)
        log_base("EROR: ", str, logger->error_mode, STDERR, logger->file);    
}

void fatal(logger_T* logger, const char* str) {
    if(logger)
        log_base("FATL: ", str, logger->fatal_mode, STDERR, logger->file);    
    exit(-1);
}

void test_all(logger_T* logger) {
    logger->performance_mode = SILENT;
    performance(logger, "performance");
    logger->performance_mode = VERBOSE;
    performance(logger, "performance");

    logger->debug_mode = SILENT;
    debug(logger, "debug");
    logger->debug_mode = VERBOSE;
    debug(logger, "debug");

    logger->info_mode = SILENT;
    info(logger, "info");
    logger->info_mode = VERBOSE;
    info(logger, "info");

    logger->warning_mode = SILENT;
    warning(logger, "warning");
    logger->warning_mode = VERBOSE;
    warning(logger, "warning");

    logger->error_mode = SILENT;
    error(logger, "error");
    logger->error_mode = VERBOSE;
    error(logger, "error");

    fatal(logger, "fatal");
}
