#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>
#include <ctime>
#include <windows.h>


#define ARR_SIZE 32000

#ifdef _CTIME_
typedef unsigned int size_t;
#endif

void print_array(unsigned short *arr, size_t arr_size);
void bubble_sort(unsigned short *arr, size_t arr_size);

#pragma warning (disable: 4100)
#pragma comment (lib, "opengl32.lib")

int main(int argc, char ** argv) {

	srand((unsigned int)time(NULL));
	unsigned short somearray[ARR_SIZE];
	memset(somearray, 0, sizeof(somearray));

	for (size_t i = 0; i < ARR_SIZE; i++) {
		somearray[i] = rand() % 100;
	}
	//print_array(somearray, ARR_SIZE);
	printf("Sorting!\n");
	double start = clock();
	bubble_sort(somearray, ARR_SIZE);
	printf("%.4lf\n", (clock() - start / CLOCKS_PER_SEC) / 1000);
	//print_array(somearray, ARR_SIZE);
	return 0;
}

void print_array(unsigned short *arr, size_t arr_size) {
	for (size_t i = 0; i < arr_size; i++){
		printf("%4d", arr[i]);
	}
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
