#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char ch;
    int lines = 0, chars = 0, spaces = 0;
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while ((ch = getc(fp)) != EOF)
    {
        chars++;
        if (ch == '\n')
            lines++;
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
            spaces++;
    }
    fclose(fp);
    printf("File %s has %d lines, %d characters, %d spaces\n", argv[1], lines, chars, spaces);
    return 0;
}