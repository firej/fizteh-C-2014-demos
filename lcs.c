#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void get_lcs(char* str1, char* str2);

int main(){
	char str1[2048], str2[2048];
	gets(str1);
	gets(str2);


	get_lcs(str1, str2);

	return 0;
}


void get_lcs(char* str1, char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	unsigned char *matrix = (unsigned char*)calloc(len1, len2);

	for (int i = 0; i < len1; i++){
		for (int j = 0; j < len2; j++){
			unsigned char value = 0;
			if (j > 0)
				value = matrix[i*len2 + j - 1];
			if (i > 0)
				value = max(value, matrix[(i - 1)*len2 + j]);
			if (str1[i] == str2[j]){
				value++;
			}
			matrix[i*len2 + j] = value;
		}
	}

	char res[2048] = {0};
	size_t res_size = matrix[len1*len2 - 1] - 1;

	for (int i = len1 - 1, j = len2 - 1; i >= 0 && j >= 0;) {
		if (str1[i] == str2[j]){
			res[res_size] = str1[i];
			//printf("%c", str1[i]);
			res_size--;
			i--;
			j--;
		}
		else {
			if (matrix[i*len2 + j] == matrix[(i - 1)*len2 + j]){
				i--;
			}
			else {
				j--;
			}
		}
	}
	//printf("%d", res_size);
	printf("Got length: %d\n", matrix[len1*len2 - 1]);
	printf("Got LCS: '%s'\n", res);
}
