#ifndef LOGGER_H
#define LOGGER_H

/**
 * Log will output this mode
 */
#define VERBOSE 0
/**
 * Log will not output this mode
 */
#define SILENT 1

/**
 * Use stdout for output
 */
#define STDOUT 0
/**
 * Use stderr for output
 */
#define STDERR 1

#include <stdio.h>

/**
 * Contains an open file handle for file logging and a group of integer values for handling the verbose state of the modes
 */
typedef struct LOGGER {
    /**
     * A handle for the log file
     */
    FILE* file;
    /**
     * The verbose state of performance logging
     */
    int performance_mode;
    /**
     * The verbose state of debug logging
     */
    int debug_mode;
    /**
     * The verbose state of info logging
     */
    int info_mode;
    /**
     * The verbose state of warning logging
     */
    int warning_mode;
    /**
     * The verbose state of error logging
     */
    int error_mode;
    /**
     * The verbose state of fatal logging
     */
    int fatal_mode;
} logger_T;

/**
 * Close file pointer and clean-up 
 */
void shutdown_logger();

/**
 * Create a new logger with optional file logging
 * @note You must close the logger in order to close its file handle to prevent resource leakage
 * @param path The path to the logfile
 */
void init_logger(const char* path);

/**
 * Base logging functionality
 * @note Do not use directly - use top level logging functions instead
 * @param prefix A piece of text to be placed preceding the log
 * @param str The string to be logged
 * @param mode The log mode's current state
 * @param target The STDOUT or STDERR macros
 * @param file The log file to output to
 */
void log_base(const char* prefix, const char* str, int mode, int target, FILE* file);

/**
 * Log performance information
 * @param str The string to be logged
 */
void performance(const char* str);
/**
 * Log debug information
 * @param str The string to be logged
 */
void debug(const char* str);
/**
 * Log info information
 * @param str The string to be logged
 */
void info(const char* str);
/**
 * Log warning information
 * @param str The string to be logged
 */
void warning(const char* str);
/**
 * Log error information
 * @param str The string to be logged
 */
void error(const char* str);
/**
 * Log fatal information
 * @param str The string to be logged
 */
void fatal(const char* str);

#endif
