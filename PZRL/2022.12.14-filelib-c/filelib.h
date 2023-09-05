#ifndef STUDYING_FILELIB_H
#define STUDYING_FILELIB_H

#include <stdio.h>

void filePrint(FILE *file);

void fileAppend(FILE *file, const char *str);

void fileSearch(FILE *file, const char *needle);

void fileRemoveLine(const char *filename, FILE **file, size_t linenum);

void fileInsertLine(const char *filename, FILE **file, const char *str, size_t linenum);

#endif //STUDYING_FILELIB_H
