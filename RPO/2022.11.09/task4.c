#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *str = NULL;
    size_t size = 0;
	int len = getline(&str, &size, stdin);
	strtok(str, "\n");
	--len;
	char *buf = malloc(len + 1);
	int j = 0;
	for (int i = 0; i < len; ++i) {
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			buf[j] = str[i];
			++j;
		}
	}
	buf[j] = '\0';
	buf = realloc(buf, j + 1);
	puts(buf);
	free(str);
	free(buf);
	return 0;
}
