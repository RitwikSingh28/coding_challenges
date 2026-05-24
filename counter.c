#include "counter.h"
#include <ctype.h>

void count_file(FILE *stream, WcCounts *counts) {
  if (!stream || !counts)
    return;

  counts->lines = 0;
  counts->words = 0;
  counts->bytes = 0;
  counts->chars = 0;

  int in_word = 0;
  int ch;

  while ((ch = fgetc(stream)) != EOF) {
    counts->bytes++;

    // Basic character counting: in UTF-8, continuation bytes start with
    // 10xxxxxx (0x80 to 0xBF) We only increment chars if it's NOT a
    // continuation byte.
    if ((ch & 0xC0) != 0x80) {
      counts->chars++;
    }

    if (ch == '\n') {
      counts->lines++;
    }

    if (isspace(ch)) {
      in_word = 0;
    } else if (!in_word) {
      in_word = 1;
      counts->words++;
    }
  }
}
