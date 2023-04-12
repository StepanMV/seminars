#include <stdio.h>
#include <stdlib.h>
#include "students.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_name>\r\n", argv[0]);
        return 1;
    }
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "rb");

    for (Student *student = readStudent(file); student != NULL; student = readStudent(file)) {
        printStudent(student);
        free(student);
    }
    fclose(file);
    return 0;
}
