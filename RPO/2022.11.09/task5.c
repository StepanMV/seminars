#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str = NULL;
    size_t size = 0;
    int len = getline(&str, &size, stdin);
    strtok(str, "\n");
    --len;
    char *maxWord = malloc(len);
    char *minWord = malloc(len);
    char *tok = strtok(str, " ");
    memcpy(maxWord, tok, strlen(tok));
    memcpy(minWord, tok, strlen(tok));
    for (; tok != NULL; tok = strtok(NULL, " ")) {
        if (strlen(tok) > strlen(maxWord)) {
            memcpy(maxWord, tok, strlen(tok));
        }
        else if (strlen(tok) < strlen(minWord)) {
            memcpy(minWord, tok, strlen(tok));
        }
    }
    printf("Max word: %s\n", maxWord);
    printf("Min word: %s\n", minWord);
    free(str);
    free(maxWord);
    free(minWord);
    return 0;
}
