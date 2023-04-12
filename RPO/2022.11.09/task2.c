#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* myGetLine();
int myStrcmp(char* str1, char* str2);

int main() {
    char* str1 = myGetLine();
    char* str2 = myGetLine();
    
    printf("Result of handmade strcmp(): %d\n", myStrcmp(str1, str2));
    return 0;
}

int myStrcmp(char* str1, char* str2) {
    for (int i = 0; ; ++i) {
        int c1 = (int) *(str1 + i);
        int c2 = (int) *(str2 + i);
        if (c1 != c2 || (char) c1 == '\0' || (char) c2 == '\0') {
            return c1 - c2;
        }
    }
}

char* myGetLine() {
    char* str = NULL;
    size_t size = 0;
    getline(&str, &size, stdin);
    strtok(str, "\n");
    return str;
}
