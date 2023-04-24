//Написать функцию, упорядочивающую символы каждой строки в заданном файле по алфавиту.
//Записать результат в другой файл.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char *str, int len)
{
    int i, j;
    char temp;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main()
{
    FILE *f;
    FILE *f2;
    char str[100];
    f = fopen("file.txt", "r");
    f2 = fopen("temp.txt", "w");
    if (f == NULL || f2 == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    while (fgets(str, 100, f) != NULL)
    {
        sort(str, strlen(str));
        fputs(str, f2);

    }
    fclose(f);
    rename("temp.txt", "file.txt");
    fclose(f2);
    return 0;
}