#ifndef IO_H
#define IO_H

#ifndef MAX_LINE_LEN
    /**
     * The maximum length of a line
     * @note Default length is 255
     */
    #define MAX_LINE_LEN 255
#endif

#include <stdio.h>

/**
 * Opens a file and returns a line
 * @note Automatically closes the file. Do not use for repeated reading
 * @param file The path to the file to read from
 * @param line The line to read
 * @return The line read from the file
 */
char* read_line(const char* file, int line);

/**
 * Returns a line from the file
 * @param file The file to read from
 * @param line The line to read
 * @return The line read from the file
 */
char* read_line_file(FILE* file, int line);

/**
 * Opens the requested file and returns an array of lines
 * @note Automatically closes the file. Do not use for repeated reading
 * @param file The path to the file to read from
 * @param start The first line to start reading from
 * @param count The number of lines to read
 * @return The lines read from the file
 */
char** read_lines(const char* file, int start, int count);

/**
 * Returns an array of lines from the file
 * @param file The file to read from
 * @param start The first line to start reading from
 * @param count The number of lines to read
 * @return The lines read from the file
 */
char** read_lines_file(FILE* file, int start, int count);

#endif
