#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filelib.h"

void filePrint(FILE *file) {
    unsigned int countLines = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        printf("%u %s", ++countLines, line);
    }
    free(line);
    rewind(file);
}

void fileAppend(FILE *file, const char *str) {
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s\n", str);
}

void fileSearch(FILE *file, const char *needle) {
    unsigned int countLines = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        char *substr = strstr(line, needle);
        if (substr != NULL) {
            for (int i = 0; i < strlen(needle); ++i) {
                substr[i] = toupper(substr[i]);
            }
            printf("%u %s", ++countLines, line);
        }
    }
    free(line);
    rewind(file);
}

void fileRemoveLine(const char *filename, FILE **file, size_t linenum) {
    char *line = NULL;
    size_t len = 0;
    FILE *temp = fopen("temp.txt", "w");
    unsigned int countLines = 0;
    while (getline(&line, &len, *file) != -1) {
        if (++countLines != linenum) {
            fprintf(temp, "%s", line);
        }
    }
    free(line);
    fclose(*file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
    *file = fopen(filename, "r");
}

void fileInsertLine(const char *filename, FILE **file, const char *str, size_t linenum) {
    char *line = NULL;
    size_t len = 0;
    FILE *temp = fopen("temp.txt", "w");
    unsigned int countLines = 0;
    while (getline(&line, &len, *file) != -1) {
        if (++countLines == linenum) {
            fprintf(temp, "%s\n", str);
        }
        fprintf(temp, "%s", line);
    }
    free(line);
    fclose(*file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
    *file = fopen(filename, "r");
}
