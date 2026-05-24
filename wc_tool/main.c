#include "counter.h"
#include <locale.h>
#include <stdio.h>
#include <unistd.h>

void print_counts(const WcCounts *counts, int l, int w, int b, int m,
                  const char *name) {
  if (l)
    printf(" %7zu", counts->lines);
  if (w)
    printf(" %7zu", counts->words);
  if (b)
    printf(" %7zu", counts->bytes);
  if (m)
    printf(" %7zu", counts->chars);
  if (name)
    printf(" %s", name);
  printf("\n");
}

int main(int argc, char **argv) {
  setlocale(LC_CTYPE, "");

  int opt;
  int show_lines = 0, show_words = 0, show_bytes = 0, show_chars = 0;

  while ((opt = getopt(argc, argv, "clwm")) != -1) {
    switch (opt) {
    case 'c':
      show_bytes = 1;
      break;
    case 'l':
      show_lines = 1;
      break;
    case 'w':
      show_words = 1;
      break;
    case 'm':
      show_chars = 1;
      break;
    default:
      fprintf(stderr, "Usage: %s [-clwm] [file ...]\n", argv[0]);
      return 1;
    }
  }

  if (!show_lines && !show_words && !show_bytes && !show_chars) {
    show_lines = show_words = show_bytes = 1;
  }

  WcCounts total = {0, 0, 0, 0};
  int file_count = argc - optind;

  if (file_count == 0) {
    WcCounts counts;
    count_file(stdin, &counts);
    print_counts(&counts, show_lines, show_words, show_bytes, show_chars, NULL);
  } else {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        perror(argv[i]);
        continue;
      }
      WcCounts counts;
      count_file(file, &counts);
      fclose(file);

      print_counts(&counts, show_lines, show_words, show_bytes, show_chars,
                   argv[i]);

      total.lines += counts.lines;
      total.words += counts.words;
      total.bytes += counts.bytes;
      total.chars += counts.chars;
    }

    if (file_count > 1) {
      print_counts(&total, show_lines, show_words, show_bytes, show_chars,
                   "total");
    }
  }

  return 0;
}
