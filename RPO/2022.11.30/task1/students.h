#ifndef STUDYING_STUDENTS_H
#define STUDYING_STUDENTS_H

#include <stdio.h>

#define SIZE 32

typedef struct {
    unsigned long id;
    char name[SIZE];
    char surname[SIZE];
    char groupName[SIZE];
    unsigned birthYear;
} Student;

Student *createStudent();

void saveStudent(Student *student, FILE *file);

Student *readStudent(FILE *file);

void printStudent(const Student *student);

#endif //STUDYING_STUDENTS_H
