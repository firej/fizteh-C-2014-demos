#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./func.h"

int main(int argc, char ** argv) {
	char userbuffer[2048] = { 0 };
	puts("Please, enter some string:\n");
	gets(userbuffer);

	char* replaced = replace(userbuffer, "=", "****");

	printf("Replaced string: %s\n", replaced);

	delete_string(replaced);

	return 0;
}
