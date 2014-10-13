#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>

#define ARR_SIZE 640000

void print_array(unsigned short *arr, size_t arr_size);
void bubble_sort(unsigned short *arr, size_t arr_size);
void qsort(unsigned short *arr, size_t arr_size);
void qsort_o(unsigned short *arr, size_t arr_size);

int main(int argc, char ** argv) {
	srand((unsigned int)time(NULL));
	unsigned short somearray[ARR_SIZE], somearray2[ARR_SIZE];
	for (size_t i = 0; i < ARR_SIZE; i++) {
		somearray[i] = rand() % 100000;
	}
	memcpy(somearray2, somearray, sizeof(somearray));
	printf("\nSorting!\n");
	
	double start = clock();
	qsort(somearray, ARR_SIZE);
	printf("Обычный qsort - %.4lf sec.\n", (clock() - start / CLOCKS_PER_SEC) / 1000000);

	double start2 = clock();
	qsort_o(somearray2, ARR_SIZE);
	printf("Оптимизированный qsort - %.4lf sec.\n", (clock() - start2 / CLOCKS_PER_SEC) / 1000000);
	printf("\n");
	return 0;
}

void print_array(unsigned short *arr, size_t arr_size) {
	for (size_t i = 0; i < arr_size; i++){
		printf("%4d", arr[i]);
	}
	printf("\n");
}

void swap(unsigned short *el1, unsigned short *el2) {
	*el2 ^= *el1;
	*el1 ^= *el2;
	*el2 ^= *el1;
}

void qsort(unsigned short *arr, size_t arr_size) {
	// sleep(1);
	if (arr_size <= 1)
		return;
	int central = arr_size / 2;

	int i = 0, j = arr_size;
	for (; i < j ;) {
		while ((arr[i] <= arr[central]) && (i < central)) i++;
		while ((arr[j] >= arr[central]) && (j > central)) j--;
		if (i < j){
			if (i == central)
				central = j;
			else if (j == central)
				central = i;
			swap(arr + i, arr + j);
			if (i < central)
				i++;
			if (j > central)
				j--;
		}
	}
	// printf("central element #%d, value - %d, i = %d, j = %d\n", central, arr[central], i, j);
	// if
	if (j > 0)
		qsort(arr, j);
	if (i < arr_size)
		qsort(arr + i, arr_size - i);
}

void qsort_o(unsigned short *arr, size_t arr_size) {
	do {
		if (arr_size <= 1)
			return;
		int central = arr_size / 2;

		int i = 0, j = arr_size;
		for (; i < j ;) {
			while ((arr[i] <= arr[central]) && (i < central)) i++;
			while ((arr[j] >= arr[central]) && (j > central)) j--;
			if (i < j){
				if (i == central)
					central = j;
				else if (j == central)
					central = i;
				swap(arr + i, arr + j);
				if (i < central)
					i++;
				if (j > central)
					j--;
			}
		}
		if (j < arr_size - i){
			if (j > 0)
				qsort(arr, j);
			arr = arr + i;
			arr_size -= i;
		}
		else {
			if (i < arr_size)
				qsort(arr + i, arr_size - i);
			arr_size = j;
		}
	} while (arr_size > 1);
}

void bubble_sort(unsigned short *arr, size_t arr_size) {
	for (unsigned int i = 0; i < arr_size; i++){
		for (unsigned int j = i; j < arr_size; j++){
			if (arr[i] > arr[j]){
				//int tmp = arr[j];
				//arr[j] = arr[i];
				//arr[i] = tmp;

				arr[j] ^= arr[i];
				arr[i] ^= arr[j];
				arr[j] ^= arr[i];

				//arr[j] += arr[i];
				//arr[i] = arr[j] - arr[i];
				//arr[j] -= arr[i];
			}
		}
	}
}
