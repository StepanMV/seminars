#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selSort(char*str, size_t len);

int main() {
    char* str = NULL;
    size_t size = 0;
    size_t len = getline(&str, &size, stdin);
    strtok(str, "\n");
    --len;
    selSort(str, len);
    puts(str);
}

void selSort(char* str, size_t len) {
    for (int i = 0; i < len; ++i) {
        int maxC = 0;
        for (int j = 0; j < len - i; ++j) {
            if (str[j] > str[maxC]) {
                maxC = j;
            }
        }
        char temp = str[len - i - 1];
        str[len - i - 1] = str[maxC];
        str[maxC] = temp;
    }
}
