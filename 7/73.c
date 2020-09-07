#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** allocate_memory(int* xdim, int ydim){
    char **arr;
    arr = malloc(ydim * (sizeof(char*)));
    for(int i = 0;i<ydim;i++){
        arr[i] = malloc(sizeof(char) * (xdim[i]+1));
    }
    return arr;
}

void free_array(char** w, int ydim){
    for(int i = 0; i < ydim; i++){
        free((w[i]));
    }
    free(w);
}

void print_array(char** words, int num) {
	for (int j = 0; j < num; j++) {
		printf("%s\n", words[j]);
	}
}

void copy_to_array(char** dest, char** src, int num) {
	for (int j = 0; j < num; j++) {
		strcpy(dest[j], src[j]);
	}
}

int main(void)
{

	char *static_words_1[] = {"dynamically", "allocated", "multidimensional", "arrays"};
	char *static_words_2[] = {"are", "FUN", "!"};

	int ydim_1 = 4;
	int xdim_1[] = {strlen(static_words_1[0]), strlen(static_words_1[1]), strlen(static_words_1[2]), strlen(static_words_1[3])};

	int ydim_2 = 3;
	int xdim_2[] = {strlen(static_words_2[0]), strlen(static_words_2[1]), strlen(static_words_2[2])};

	char** words = allocate_memory(xdim_1, ydim_1);

	copy_to_array(words, static_words_1, ydim_1);
	print_array(words, ydim_1);
	free_array(words, ydim_1);

	words = allocate_memory(xdim_2, ydim_2);

	copy_to_array(words, static_words_2, ydim_2);
	print_array(words, ydim_2);
	free_array(words, ydim_2);

	return 0;
}


