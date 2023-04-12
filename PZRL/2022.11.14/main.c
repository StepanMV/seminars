#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void foo(int a, int b);

int main() {
	int a, b, c;
    a = 10;
	b = 3;
	c = 5;

	foo(a, b);

	printf("a = %3d, b = %3d, c = %3d\n", a, b, c);
	printf("a = %3d, b = %3d, c = %3d\n", a, b, c);
	printf("a = %3d, b = %3d, c = %3d\n", a, b, c);
	return 0;
}

void foo(int a, int b) {
	printf("%d:%d\n", a, b);
	malloc(30);
	malloc(30);
	malloc(30);
}
