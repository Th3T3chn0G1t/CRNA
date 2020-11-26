#ifndef IO_H
#define IO_H

#ifndef MAX_LINE_LEN
    #define MAX_LINE_LEN 255
#endif

#include <stdio.h>

/**
 * Opens the requested file and returns a line, automatically cloing the file
 */
char* read_line(const char* file, int line);

/**
 * Returns a line from the specified file
 */
char* read_line_file(FILE* file, int line);

/**
 * Opens the requested file and returns an array of lines in range start -> count, automatically cloing the file
 */
char** read_lines(const char* file, int start, int count);

/**
 * Returns an array of lines in range start -> count from the specified file
 */
char** read_lines_file(FILE* file, int start, int count);

#endif
