#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>

void print_array(char **arr, size_t arr_size, bool carriage = true);
void radixsort(char **arr, size_t arr_size, size_t depth = 0);

int main(int argc, char ** argv) {
	char *strings[1024];
	size_t arr_size = 0;

	FILE *test = fopen("test.txt", "r");
	if (!test){
		printf("Не открылся файл :(\n");
		return 255;
	}
	do {
		strings[arr_size] = (char *)calloc(2048, sizeof(char));
		fgets(strings[arr_size], 2048, test);

		if (strings[arr_size][strlen(strings[arr_size]) - 1] == '\n') {
			strings[arr_size][strlen(strings[arr_size]) - 1] = 0;
		}

		if (!feof(test)){
			arr_size++;
		}
		else {
			break;
		}
	}
	while(1);
	// print_array(strings, arr_size);
	double start = clock();
	printf("\nSorting! %lu strings\n", arr_size);
	radixsort(strings, arr_size);
	// print_array(strings, arr_size);
	// printf("sorting: - %.4lf sec.\n", (clock() - start / CLOCKS_PER_SEC) / 1000000);

	fclose(test);
	printf("\n");
	return 0;
}

void print_array(char **arr, size_t arr_size, bool carriage) {
	for (size_t i = 0; i < arr_size; i++){
		printf("%s\n", arr[i]);
	}
	if (carriage)
		printf("====================\n");
}

void string_swap(char **el1, char **el2) {
	char *tmp = *el2;
	*el2 = *el1;
	*el1 = tmp;
}

void radixsort (char **arr, size_t arr_size, size_t depth){
	// for (int i = 0; i < arr_size; i++){
	// 	printf("%d   ", strlen(arr[i]));
	// }

	// if (depth == 1 && arr[0][1] == 't') {
	// 	print_array(arr, arr_size);
	// }

	if (arr_size < 2)
		return;
	for (int i = 1; i < arr_size; i++){
		for (int j = i; j && arr[j][depth] < arr[j-1][depth]; j--) {
			string_swap(&arr[j], &arr[j-1]);
		}
	}
	int i = 0, j;
	for (char s = 1; s <= 126; s++) {
		if (depth == 0)	{
			printf("\nPocket: #%d (%c) i: %d arr[i]: %s\n", s, s, i, arr[i]);
		}
		if (arr[i][depth] == s){
			j = 1;
			while(arr[i + j][depth] == s)
				j++;
			radixsort(arr + i, j, depth + 1);
			i += j;
		}
		else {
		}
	}
}


int my_compare(const void* p1, const void* p2) {
	if (*((unsigned short*)p1) == *((unsigned short*)p2))
		return 0;
	else if (*((unsigned short*)p1) < *((unsigned short*)p2))
		return -1;
	else
		return 1;
}

void mergesort (unsigned short *arr, size_t arr_size, int (*compar)(const void *, const void *)) {
	if (arr_size == 1)
		return;
	else {
		mergesort(arr, arr_size/2, compar);
		mergesort(arr + arr_size/2, (arr_size - arr_size/2), compar);
	}
	unsigned short *arr2 = arr + arr_size/2;
	unsigned short *buf = (unsigned short*) malloc(sizeof(arr[0]) * arr_size);

	int i=0, j=0;
	for (; i < arr_size/2 && j < (arr_size - arr_size/2);){
		if (compar(&arr[i], &arr2[j]) < 0) {
			buf[i + j] = arr[i];
			i++;
		}
		else {
			buf[i + j] = arr2[j];
			j++;
		}
	}
	while (i < arr_size/2)
		buf[i+j] = arr[i], i++;
	while (j < (arr_size - arr_size/2))
		buf[i+j] = arr2[j], j++;
	memcpy(arr, buf, arr_size * sizeof(arr[0]));
}
