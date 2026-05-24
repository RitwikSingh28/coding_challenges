#ifndef COUNTER_H
#define COUNTER_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t lines;
    size_t words;
    size_t bytes;
    size_t chars;
} WcCounts;

/**
 * Processes a file stream and populates the WcCounts struct.
 * This function performs a single pass over the stream.
 */
void count_file(FILE* stream, WcCounts* counts);

#endif // COUNTER_H
