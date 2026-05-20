#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

size_t countChars(FILE*);
size_t countLines(FILE*);
size_t countWords(FILE*);
size_t countMultiByteWords(FILE*);

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: ccwc <filename> ...flags\n");
        return 1;
    }

    if (setlocale(LC_CTYPE, "") == NULL) {
        fprintf(stderr, "Failed to set the default locale\n");
        return 1;
    }

    char* filename = NULL;
    char* arg = NULL;
    char output[2000] = {0}; // Initialize to empty string
    char flag = 0;

    if (argc == 2) {
        filename = argv[1];
        flag = 1;
    } else {
        filename = argv[2];
        arg = argv[1];
    }

    // open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return 1;
    }
    
    size_t count = 0;

    // Logic for -c or default (no flag)
    if (flag || (arg && !strcmp(arg, "-c"))) {
        char str_count[21];
        count = countChars(file);
        snprintf(str_count, sizeof(str_count), "%zu", count);
        int len = strlen(output);
        snprintf(output + len, sizeof(output) - len, " %s", str_count);
        rewind(file);
    }

    // Logic for -l or default (no flag)
    if (flag || (arg && !strcmp(arg, "-l"))) {
        char str_count[21];
        count = countLines(file);
        snprintf(str_count, sizeof(str_count), "%zu", count);
        int len = strlen(output);
        snprintf(output + len, sizeof(output) - len, " %s", str_count);
        rewind(file);
    }

    // Logic for -w or default (no flag)
    if (flag || (arg && !strcmp(arg, "-w"))) {
        char str_count[21];
        count = countWords(file);
        snprintf(str_count, sizeof(str_count), "%zu", count);
        int len = strlen(output);
        snprintf(output + len, sizeof(output) - len, " %s", str_count);
        rewind(file);
    }

    // Logic for -m
    if (arg && !strcmp(arg, "-m")) {
        char str_count[21];
        count = countMultiByteWords(file);
        snprintf(str_count, sizeof(str_count), "%zu", count);
        int len = strlen(output);
        snprintf(output + len, sizeof(output) - len, " %s", str_count);
        rewind(file);
    }

    // Final filename append
    int len = strlen(output);
    snprintf(output + len, sizeof(output) - len, " %s", filename);
    fprintf(stdout, "%s\n", output);

    fclose(file);
    return 0;
}

size_t countChars(FILE* file) {
    size_t count = 0;
    while (getc(file) != EOF) count++;
    return count;
}

size_t countLines(FILE* file) {
    size_t count = 0;
    int ch; // int is better for EOF comparison
    while ((ch = getc(file)) != EOF) {
        if (ch == '\n') count++;
    }
    return count;
}

size_t countWords(FILE* file) {
    size_t count = 0;
    int flag = 0;
    int ch;
    while((ch = getc(file)) != EOF) {
        if (!isspace(ch)) {
            if (!flag) {
                flag = 1;
                count++;
            }
        } else flag = 0;
    }
    return count;
}

size_t countMultiByteWords(FILE* file) {
    size_t count = 0;
    wint_t ch;
    while ((ch = getwc(file)) != WEOF) {
        count++;
    }
    return count;
}
