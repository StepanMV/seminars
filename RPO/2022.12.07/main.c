#include <stdio.h>
#include "filelib.h"

int main() {
    FILE *file = fopen("file.txt", "r");
    filePrint(file);
    printf("\n");
    fileSearch(file, "London");
    printf("\n");
    fileRemoveLine("file.txt", &file, 2);
    fileInsertLine("file.txt", &file, "**** *** ** **** ** ** *** *** * ** * * ***", 2);
    filePrint(file);
    fclose(file);
    return 0;
}
