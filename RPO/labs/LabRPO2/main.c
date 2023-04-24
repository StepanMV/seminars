#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_lab.h"
#include <time.h>

int main() {
    srand(time(NULL));
    while (1) {
        char* str1 = malloc(rand() % 100);
        char* str2 = malloc(rand() % 100);
        char ch = rand() % 94 + ' ';
        for (int i = 0; i < strlen(str1); i++) {
            str1[i] = rand() % 94 + ' ';
        }
        for (int i = 0; i < strlen(str2); i++) {
            str2[i] = rand() % 94 + ' ';
        }
        str1[strlen(str1)] = '\0';
        str2[strlen(str2)] = '\0';

        char* _strremoveRES = _strremove(str1, ch);
        int _strcountcharRES = _strcountchar(str1, ch);
        char* _strdelspacesRES = _strdelspaces(str1);
        char* _strtolowerRES = _strtolower(str1);
        char* _strtoupperRES = _strtoupper(str1);
        int _strcmpRES = _strcmp(str1, str2);
        char* _srereverseRES = _strreverse(str1);
        int _atoiRES = _atoi(str1);
        char* _strchrRES = _strchr(str1, ch);
        char* _strstrRES = _strstr(str1, str2);
        int _strlenRES = _strlen(str1);

        printf("_strremove(\"%s\", '%c') = \"%s\"\n", str1, ch, _strremoveRES);
        printf("_strcountchar(\"%s\", '%c') = %d\n", str1, ch, _strcountcharRES);
        printf("_strdelspaces(\"%s\") = \"%s\"\n", str1, _strdelspacesRES);
        printf("_strtolower(\"%s\") = \"%s\"\n", str1, _strtolowerRES);
        printf("_strtoupper(\"%s\") = \"%s\"\n", str1, _strtoupperRES);
        printf("_strcmp(\"%s\", \"%s\") = %d\n", str1, str2, _strcmpRES);
        printf("_strreverse(\"%s\") = \"%s\"\n", str1, _srereverseRES);
        printf("_atoi(\"%s\") = %d\n", str1, _atoiRES);
        printf("_strchr(\"%s\", '%c') = \"%s\"\n", str1, ch, _strchrRES);
        printf("_strstr(\"%s\", \"%s\") = \"%s\"\n", str1, str2, _strstrRES);
        printf("_strlen(\"%s\") = %d\n", str1, _strlenRES);
        printf("\n");

        free(str1);
        free(str2);
    }
    return 0;
}
