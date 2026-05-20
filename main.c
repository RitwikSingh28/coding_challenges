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
    char* flag = NULL;
    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = argv[2];
        flag = argv[1];
    }

    // open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s", filename);
        return 1;
    }
    
    if (!strcmp(flag, "-c")) {
        const size_t count = countChars(file);
        fprintf(stdout, " %zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-l")) {
        const size_t count = countLines(file);
        fprintf(stdout, " %zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-w")) {
        const size_t count = countWords(file);
        fprintf(stdout, "%zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-m")) {
        const size_t count = countMultiByteWords(file);
        fprintf(stdout, "%zu\t %s\n", count, filename);
    }

    fclose(file);
    return 0;
}

size_t countChars(FILE* file) {
    // Count number of bytes in the provided file
    size_t count = 0;
    while (getc(file) != EOF) count++;
    return count;
}

size_t countLines(FILE* file) {
    // Count number of lines in the file
    size_t count = 0;
    char ch;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\n') count++;
    }
    return count;
}

size_t countWords(FILE* file) {
    // Count number of words in the file
    size_t count = 0;
    char flag = 0;
    char ch;
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
