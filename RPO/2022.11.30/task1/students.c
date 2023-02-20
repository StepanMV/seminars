#include <stdlib.h>
#include <string.h>
#include "students.h"

Student *createStudent() {
    Student *student = malloc(sizeof(Student));
    printf("Enter student data: ");
    scanf("%lu %s %s %s %u",
          &student->id, student->name, student->surname, student->groupName, &student->birthYear);
    return student;
}

void saveStudent(Student *student, FILE *file) {
    fwrite(student, sizeof(Student), 1, file);
}

Student *readStudent(FILE *file) {
    Student *student = malloc(sizeof(Student));

    size_t countStudents = fread(student, sizeof(Student), 1, file);
    return countStudents == 0 ? NULL : student;
}

void printStudent(const Student *student) {
    printf("Student data: %lu %s %s %s %u\n",
           student->id, student->name, student->surname, student->groupName, student->birthYear);
}
