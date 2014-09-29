#include <stdlib.h>
#include <string.h>

#include "./func.h"


char * replace(const char *str, const char *what, const char *to) {
	char * result = (char*)malloc(3000);
	unsigned int res_len = 0;
	if (!result)
		return NULL;
	for (unsigned int i = 0; i < strlen(str); i++) {
		if (!strncmp(str + i, what, strlen(what))){
			for (unsigned int j = 0; j < strlen(to); j++){
				result[res_len + j] = to[j];
			}
			res_len += strlen(to);
			i += strlen(what) - 1;
		}
		else {
			result[res_len] = str[i];
			res_len++;
		}
	}
	result[res_len] = '\0';
	return result;
}

void delete_string(char * str) {
	if (!str)
		return;
	free(str);
}