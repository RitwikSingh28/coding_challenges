#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "USAGE: ccwc -<flag> <filename>\n");
        return 1;
    }

    if (setlocale(LC_CTYPE, "") == NULL) {
        fprintf(stderr, "Failed to set the default locale\n");
        return 1;
    }

    const char* flag = argv[1];
    const char* filename = argv[2];

    // open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s", filename);
        return 1;
    }
    
    if (!strcmp(flag, "-c")) {
        // Count number of bytes in the provided file
        size_t count = 0;
        while (getc(file) != EOF) count++;

        fprintf(stdout, " %zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-l")) {
        // Count number of lines in the file
        size_t count = 0;
        char ch;
        while ((ch = getc(file)) != EOF) {
            if (ch == '\n') count++;
        }

        fprintf(stdout, " %zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-w")) {
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

        fprintf(stdout, "%zu\t %s\n", count, filename);
    }

    else if (!strcmp(flag, "-m")) {
        size_t count = 0;
        wint_t ch;
        while ((ch = getwc(file)) != WEOF) {
            count++;
        }

        fprintf(stdout, "%zu\t %s\n", count, filename);
    }

    fclose(file);
    return 0;
}
