#include <stdio.h>

void concat(char *file1, char *file2, char *file3) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *f3 = fopen(file3, "w");

    char c;
    while ((c = (char) fgetc(f1)) != EOF) {
        fputc(c, f3);
    }
    while ((c = (char) fgetc(f2)) != EOF) {
        fputc(c, f3);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int main(int argc, char *argv[]) {
    char *file1 = argv[1];
    char *file2 = argv[2];
    char *file3 = argv[3];
    return 0;
}