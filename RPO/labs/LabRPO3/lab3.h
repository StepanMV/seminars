#ifndef LAB3_H
#define LAB3_H

#include <stdbool.h>
#include <stdlib.h>

#define SIZE 128
// unsigned long g_Id = 1;  // переменная, присваиваемая каждому новому студенту, после чего инкрементируемая
// то есть у каждого нового будет уникальный id
// после вызова initUniversity(..) необходимо присвоить значению максимальный Id среди всех считанных студентов
// должна быть определена в lab3.c

// Структура описывающая студента
typedef struct
{
    unsigned long id;       // Уникальный id, получаемый из g_Id
    char name[SIZE];        // Имя
    char surname[SIZE];     // Фамилия
    char groupName[SIZE];   // Название группы
    unsigned birthYear;     // Год рождения
} Student;

// Структура описывающая группу
// Cоздается при чтении, если getGroup() вернула NULL; название группы берется из структуры студента
typedef struct
{
    char name[SIZE];        // Название группы
    unsigned studentsCount; // Количество студентов в группе (размер динамического массива)
    Student *students;      // Динамический массив со студентами
} Group;

// Структура описывающая университет
typedef struct
{
    unsigned groupsCount;   // Количество групп в университете (размер динамического массива)
    Group *groups;          // Динамический массив с группами
} University;

/*
- Функция, инициализирующаяя структуру университета
- Читаем бинарный файл с последовательно записанными студентами, и заполняем университет
группами (взятыми из поля groupName студента) и самими студентами
- При любых ошибках чтения файла, все равно возвращается указатель на структуру университета
- При добавлении студентов, должна меняться глобальная переменная, отвечающая за Id (максимальный id + 1),
чтобы не было пересечений при добавлении новых студентов
*/
University* initUniversity(const char *fileName);

/*
- Функция, добавляющая новую группу в университет
- Перераспределяет память по указателю groups, инкрементирует счетчик
- Возвращает признак успешного добавления
*/
bool addNewGroup(University *university, const Group group);

/*
- Функция, добавляющая нового студента в массив студентов, отсортировав по фамилии
- Работает аналогично addNewGroup
- Должна назначать Id переданному студенту если он не задан (id == 0)
- Возвращает признак успешного добавления
*/
bool addNewStudent(Group *group, Student student);

/*
- Функция, удаляющая группу из университета по заданному имени
- Возвращает признак успешного удаления
*/
bool removeGroup(University *university, const char *name);

/*
- Функция, удаляющая студента из университета по заданному Id
- Возвращает признак успешного удаления
*/
bool removeStudent(University *university, const unsigned long id);

/*
- Функция, возвращающая указатель на группу по заданному имени
- Если такой группы нет в университете, возвращается NULL
*/
Group* getGroup(const University *university, const char *name);

/*
- Функция, возвращающая указатель на студента по заданному Id
- Если такого студента нет в университете, возвращается NULL
*/
Student* getStudent(const University *university, const unsigned long id);

/*
- Функция, печатающая информацию об университете в следующем формате:
-------------------------------------------------------------------------------
НАЗВАНИЕ ГРУППЫ
    Id
        Фамилия Имя
        Дата рождения
    Id
        ...
-------------------------------------------------------------------------------
НАЗВАНИЕ ГРУППЫ
    Id
        ...
-------------------------------------------------------------------------------
- Если в университете нет ни групп, ни студентов выводить сообщение об этом
*/
void printUniversity(const University *university);

/*
- Функция, печатающая информацию о группе в следующем формате:
НАЗВАНИЕ ГРУППЫ
    Id
        Фамилия Имя
        Дата рождения
    Id
        ...
- Если в группе нет студентов, выводить сообщение об этом
*/
void printGroup(const Group group);

/*
- Функция, печатающая информацию о студенте в следующем формате:
    Id
        Фамилия Имя
        Дата рождения
*/
void printStudent(const Student student);

/*
- Функция, освобождающая всю выделенную память для университета
*/
void freeUniversity(University *university);

/*
- Функция, сохраняющая информацию о студентах университа в бинарный файл
- Студенты записываются в файл последовательно
- Файл полностью перезаписывается
- Возвращает признак успешного сохранения
*/
bool saveToFile(const char *fileName, const University *university);

#endif