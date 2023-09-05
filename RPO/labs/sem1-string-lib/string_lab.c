#include <stdlib.h>
#include <string.h>
#include "string_lab.h"

int _strlen(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int _strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] > str2[i]) {
            return 1;
        } else if (str1[i] < str2[i]) {
            return -1;
        }
        i++;
    }
    if (str1[i] > str2[i]) {
        return 1;
    } else if (str1[i] < str2[i]) {
        return -1;
    } else {
        return 0;
    }
}

char* _strchr(char* str, int ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            return &str[i];
        }
    }
    return NULL;
}

char* _strstr(const char* str, const char* substr) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
        if (str[i] == substr[j]) {
            j++;
        } else {
            j = 0;
        }
        if (substr[j] == '\0') {
            return &str[i - j + 1];
        }
        i++;
    }
    return NULL;
}

int _atoi(const char* str) {
    int i = 0;
    int result = 0;
    int sign = 1;
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + str[i] - '0';
        i++;
    }
    return result * sign;
}

char* _strtolower(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
    return str;
}

char* _strtoupper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
    return str;
}

int _strcountchar(const char* str, const char ch) {
    char* strcpy = malloc(_strlen(str) + 1);
    memcpy(strcpy, str, _strlen(str) + 1);
    int count = 0;
    for (char* chptr = _strchr(strcpy, ch); chptr != NULL; chptr = _strchr(strcpy, ch)) {
        memmove(strcpy, chptr + 1, _strlen(chptr + 1) + 1);
        count++;
    }
    free(strcpy);
    return count;
}

char* _strremove(char* str, const char ch) {
    for (char* chptr = _strchr(str, ch); chptr != NULL; chptr = _strchr(str, ch)) {
        memmove(chptr, chptr + 1, _strlen(chptr + 1) + 1);
    }
    return str;
}

char* _strdelspaces(char* str) {
    int flag = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            if (flag == 0) {
                flag = 1;
            } else {
                memmove(&str[i], &str[i + 1], _strlen(&str[i + 1]) + 1);
                i--;
            }
        } else if (flag == 1) {
            flag = 0;
        }
    }
    return str;
}

char* _strreverse(const char* str) {
    char* result = malloc(_strlen(str) + 1);
    for (int i = 0; str[i] != '\0'; i++) {
        result[i] = str[_strlen(str) - i - 1];
    }
    result[_strlen(str)] = '\0';
    return result;
}