#include <stdio.h>
#include <stdlib.h>

FILE* myfile = NULL;

int main(int argc, char ** argv) {
	myfile = fopen("testfile.txt", "w+");
	// fprintf(myfile, "%s\n", "Hello world!");
	// fseek(myfile, 0, SEEK_SET);
	// char buf[1024];
	// // fscanf(myfile, "%s", buf);
	// fgets(buf, 1023, myfile);
	// printf("Прочтенная строка: %s\n", buf);

	// double arr[] = {100,0.5,0.666,20845798246598.0};
	// double res[] = {0,0,0,0};

	// fwrite(arr, sizeof(double), 4, myfile);

	// fseek(myfile, 0, SEEK_SET);

	// fread(res, sizeof(double), 2, myfile);

	// printf("%lf %lf\n", res[0], res[1]);

	fprintf(stdout, "Some!\n");

	fclose(myfile);
	return 0;
}
