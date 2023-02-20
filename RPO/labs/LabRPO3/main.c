#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab3.h"

typedef enum {
    E_ADD_GROUP = 1,
    E_ADD_STUDENT,
    E_DEL_GROUP,
    E_DEL_STUDENT,
    E_PRINT_UNI,
    E_PRINT_GROUP,
    E_PRINT_STUDENT,
    E_END
} EAction;

const char *Enum2Str(EAction eAct) {
    switch (eAct) {
        case E_ADD_GROUP:
            return " - Add a group";
        case E_ADD_STUDENT:
            return " - Add a student";
        case E_DEL_GROUP:
            return " - Remove a group";
        case E_DEL_STUDENT:
            return " - Remove a student";
        case E_PRINT_UNI:
            return " - Print information about the university";
        case E_PRINT_GROUP:
            return " - Print information about the group";
        case E_PRINT_STUDENT:
            return " - Print information about the student";
        case E_END:
            return " - End of work";
        default:
            return " - Invalid command";
    }
}

int main(int argc, char *argv[]) {
    char *filename = (char *) malloc(SIZE);
    if (argc == 2) {
        strcpy(filename, argv[1]);
    } else {
        printf("Enter datafile path: ");
        scanf("%s", filename);
    }

    University *uni = initUniversity(filename);
    char *input = (char *) malloc(SIZE);
    EAction eAction = -1;

    while (eAction != E_END) {
        printf("\n");
        for (int i = 1; i <= E_END; i++) {
            printf("%d%s\n", i, Enum2Str((EAction) i));
        }

        printf("Enter command: ");
        scanf("%s", input);
        eAction = (EAction) strtol(input, NULL, 10);

        switch (eAction) {
            case E_ADD_GROUP: {
                char groupName[SIZE];
                printf("Enter group name: ");
                scanf("%s", groupName);

                Group group = {{0}, 0, 0};
                strcpy(group.name, groupName);
                group.students = (Student *) malloc(sizeof(Student));

                addNewGroup(uni, group);
                break;
            }

            case E_ADD_STUDENT: {
                char groupName[SIZE];
                char name[SIZE];
                char surname[SIZE];
                int year = 0;

                printf("Enter group name: ");
                scanf("%s", groupName);
                printf("Enter student surname: ");
                scanf("%s", surname);
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter student birth year: ");
                scanf("%d", &year);

                Student student = {0, {0}, {0}, {0}, year};
                strcpy(student.name, name);
                strcpy(student.surname, surname);
                strcpy(student.groupName, groupName);

                addNewStudent(getGroup(uni, groupName), student);
                break;
            }

            case E_DEL_GROUP: {
                char groupName[SIZE];
                printf("Enter group name: ");
                scanf("%s", groupName);

                removeGroup(uni, groupName);
                break;
            }

            case E_DEL_STUDENT: {
                int id = -1;
                printf("Enter student id: ");
                scanf("%d", &id);

                if (id == -1) {
                    printf("Invalid id\n");
                    break;
                }

                removeStudent(uni, id);
                break;
            }

            case E_PRINT_UNI: {
                printUniversity(uni);
                break;
            }

            case E_PRINT_GROUP: {
                char groupName[SIZE];
                printf("Enter group name: ");
                scanf("%s", groupName);

                Group *group = getGroup(uni, groupName);
                if (group == NULL) {
                    printf("Group not found\n");
                } else {
                    printGroup(*group);
                }
                break;
            }

            case E_PRINT_STUDENT: {
                int id;
                printf("Enter student id: ");
                scanf("%d", &id);

                Student *student = getStudent(uni, id);
                if (student == NULL) {
                    printf("Student not found\n");
                } else {
                    printStudent(*student);
                }
                break;
            }

            default: {
                printf("Invalid command\n");
                break;
            }
        }
    }

    saveToFile(filename, uni);
    freeUniversity(uni);
    free(input);
    free(filename);
    return 0;
}