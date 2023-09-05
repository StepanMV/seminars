#include <stdio.h>
#include <string.h>

#include "lab3.h"

unsigned long g_Id = 1;

static bool isCorrectFilename(const char* filename)
{
    char *dot = strrchr(filename, '.');
    if (dot == NULL || strcmp(dot, ".dat") != 0) {
        return false;
    }
    return true;
}

static Student *sortedStudents(Student *students, unsigned int count) {
    for (int i = 0; i < count; i++) {
        int min = i;
        for (int j = i + 1; j < count; j++) {
            if (strcasecmp(students[j].surname, students[min].surname) < 0) {
                min = j;
            }
        }
        Student temp = students[i];
        students[i] = students[min];
        students[min] = temp;
    }
    return students;
}

University *initUniversity(const char *fileName) {
    University *university = (University *) malloc(sizeof(University));
    university->groups = (Group *) malloc(sizeof(Group));
    university->groupsCount = 0;
    FILE *file = fopen(fileName, "rb");
    if (!isCorrectFilename(fileName) || file == NULL) {
        fclose(file);
        return university;
    }
    Student *student = (Student *) malloc(sizeof(Student));
    while (fread(student, sizeof(Student), 1, file) != 0) {
        Group *group = getGroup(university, student->groupName);
        if (group == NULL) {
            Group newGroup = {{0}, 0, NULL};
            strcpy(newGroup.name, student->groupName);
            addNewGroup(university, newGroup);
            group = getGroup(university, student->groupName);
        }
        addNewStudent(group, *student);
    }
    free(student);
    fclose(file);
    return university;
}

bool addNewGroup(University *university, const Group group) {
    if (university == NULL) {
        return false;
    }
    university->groupsCount++;
    university->groups = (Group *) realloc(university->groups, university->groupsCount * sizeof(Group));
    university->groups[university->groupsCount - 1] = group;
    return true;
}

bool addNewStudent(Group *group, Student student) {
    if (group == NULL || strcmp(student.groupName, group->name) != 0) {
        return false;
    }
    if (student.id == 0) {
        student.id = g_Id++;
    } else if (student.id >= g_Id) {
        g_Id = student.id + 1;
    }
    group->studentsCount++;
    group->students = (Student *) realloc(group->students, group->studentsCount * sizeof(Student));
    group->students[group->studentsCount - 1] = student;
    group->students = sortedStudents(group->students, group->studentsCount);
    return true;
}

bool removeGroup(University *university, const char *name) {
    if (university == NULL) {
        return false;
    }
    Group *group = getGroup(university, name);
    if (group == NULL) {
        return false;
    }
    free(group->students);
    memmove(group, group + 1, (university->groupsCount - 1 - (group - university->groups)) * sizeof(Group));
    university->groupsCount--;
    university->groups = realloc(university->groups, (university->groupsCount) * sizeof(Group));
    return true;
}

bool removeStudent(University *university, const unsigned long id) {
    if (university == NULL) {
        return false;
    }
    Student *student = getStudent(university, id);
    if (student == NULL) {
        return false;
    }
    Group *group = getGroup(university, student->groupName);
    memmove(student, student + 1, (group->studentsCount - 1 - (student - group->students)) * sizeof(Student));
    group->studentsCount--;
    group->students = realloc(group->students, (group->studentsCount) * sizeof(Student));
    return true;
}

Group *getGroup(const University *university, const char *name) {
    if (university == NULL) {
        return NULL;
    }
    for (unsigned int i = 0; i < university->groupsCount; i++) {
        if (strcmp(university->groups[i].name, name) == 0) {
            return &university->groups[i];
        }
    }
    return NULL;
}

Student *getStudent(const University *university, const unsigned long id) {
    if (university == NULL) {
        return NULL;
    }
    for (int i = 0; i < university->groupsCount; i++) {
        for (int j = 0; j < university->groups[i].studentsCount; j++) {
            if (university->groups[i].students[j].id == id) {
                return &university->groups[i].students[j];
            }
        }
    }
    return NULL;
}

void printUniversity(const University *university) {
    if (university == NULL) {
        return;
    }
    if (university->groupsCount == 0) {
        printf("University is empty\n");
        return;
    }
    for (int group = 0; group < university->groupsCount; group++) {
        printf("-------------------------------------------------------------------------------\n");
        printGroup(university->groups[group]);
    }
    printf("-------------------------------------------------------------------------------\n");
}

void printGroup(const Group group) {
    if (group.studentsCount == 0) {
        printf("Group %s is empty\n", group.name);
        return;
    }
    printf("%s\n", group.name);
    for (int student = 0; student < group.studentsCount; student++) {
        printStudent(group.students[student]);
    }
}

void printStudent(const Student student) {
    printf("\t%lu\n\t\t%s %s\n\t\t%u\n", student.id, student.surname, student.name, student.birthYear);
}

void freeUniversity(University *university) {
    if (university == NULL) {
        return;
    }
    for (int i = 0; i < university->groupsCount; i++) {
        free(university->groups[i].students);
    }
    free(university->groups);
    free(university);

}

bool saveToFile(const char *fileName, const University *university) {
    if (university == NULL) {
        return false;
    }
    FILE *file = fopen(fileName, "wb");
    if (!isCorrectFilename(fileName) || file == NULL) {
        fclose(file);
        return false;
    }
    for (int i = 0; i < university->groupsCount; i++) {
        for (int j = 0; j < university->groups[i].studentsCount; j++) {
            fwrite(&university->groups[i].students[j], sizeof(Student), 1, file);
        }
    }
    fclose(file);
    return true;
}