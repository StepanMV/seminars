#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* myGetline();

int main() {
    
    char* str1 = myGetline();
    char* str2 = myGetline();
    int len1 = strlen(str1);
	int len2 = strlen(str2);
    int res = 0;
    for (int i = 0; i < (len1 - len2 + 1); ++i) {
        char* substr = malloc(len2);
        memcpy(substr, str1 + i, len2);
		if (strcmp(substr, str2) == 0) {
			++res;
		}
    }
    printf("Found %d %s in string %s\n", res, str2, str1);
    free(str1);
    free(str2);
    return 0;
}

char* myGetline() { 
    char* str = NULL;
    size_t size = 0;
    getline(&str, &size, stdin);
    strtok(str, "\n");
    return str;
}
