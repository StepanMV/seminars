#include <stdio.h>
#include "students.h"


int main(int argc, char *argv[]) {
    // get file name from command line
    if (argc < 2) {
        printf("Usage: %s <file_name>\r\n", argv[0]);
        return 1;
    }
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "ab");
    Student *student = createStudent();
    saveStudent(student, file);
    fclose(file);
    return 0;
}
