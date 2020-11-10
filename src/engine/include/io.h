#ifndef IO_H
#define IO_H

#ifndef MAX_LINE_LEN
    #define MAX_LINE_LEN 255
#endif

#include <stdio.h>

char* read_line(const char* file, int line);
char* read_line_file(FILE* file, int line);
char** read_lines(const char* file, int start, int count);
char** read_lines_file(FILE* file, int start, int count);

#endif
