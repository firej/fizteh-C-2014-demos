#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>

#define ARR_SIZE 20

// typedef unsigned int size_t;

void print_array(unsigned short *arr, size_t arr_size, bool carriage = true);
void bubble_sort(unsigned short *arr, size_t arr_size);
void qsort(unsigned short *arr, size_t arr_size);
void qsort_o(unsigned short *arr, size_t arr_size);
void heapsort(unsigned short *arr, size_t arr_size);
void mergesort (unsigned short *arr, size_t arr_size, int (*compar)(const void *, const void *));
int my_compare(const void* p1, const void* p2);

int main(int argc, char ** argv) {
	srand((unsigned int)time(NULL));
	unsigned short somearray[ARR_SIZE], somearray2[ARR_SIZE];
	for (size_t i = 0; i < ARR_SIZE; i++) {
		somearray[i] = rand() % 100;
	}
	// memcpy(somearray2, somearray, sizeof(somearray));
	print_array(somearray, ARR_SIZE);
	printf("\nSorting!\n");
	mergesort(somearray, ARR_SIZE, my_compare);
	print_array(somearray, ARR_SIZE);
	// double start = clock();
	// qsort(somearray, ARR_SIZE);
	// printf("Обычный qsort - %.4lf sec.\n", (clock() - start / CLOCKS_PER_SEC) / 1000000);

	// double start2 = clock();
	// qsort_o(somearray2, ARR_SIZE);
	// printf("Оптимизированный qsort - %.4lf sec.\n", (clock() - start2 / CLOCKS_PER_SEC) / 1000000);
	printf("\n");
	return 0;
}

void print_array(unsigned short *arr, size_t arr_size, bool carriage) {
	for (size_t i = 0; i < arr_size; i++){
		printf("%4d", arr[i]);
	}
	if (carriage)
		printf("\n");
}

void swap(unsigned short *el1, unsigned short *el2) {
	*el2 ^= *el1;
	*el1 ^= *el2;
	*el2 ^= *el1;
}

void sift(unsigned short *arr, size_t i, size_t j);

void heapsort(unsigned short *arr, size_t arr_size){
	for (int i = arr_size/2-1; i >=0 ;i--){
		sift(arr, (size_t)i, arr_size);
	}
	for (size_t i = arr_size-1; i >= 1; i--){
		swap(&arr[0], &arr[i]);
		sift(arr, 0, i-1);
	}
}

void sift(unsigned short *arr, size_t i, size_t j){
	bool end = false;
	size_t max;
	while((i*2 < j) && (!end)){
		if (arr[i*2] > arr[i*2 + 1])
			max = i*2;
		else
			max = i*2 + 1;

		if (arr[i] < arr[max]){
			swap(&arr[i], &arr[max]);
			i = max;
		}
		else
			end = true;
	}
}

// typedef int (*comparator)(const void *, const void *);

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
