#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* join_arrays(unsigned int x, int *a, unsigned int y, int *b, unsigned int z, int *c){
    int *array;
    array = malloc(1000 * sizeof(int));
    array = memcpy(array, a, x * sizeof(int));
    memmove(array + x, b, y * sizeof(int));
    memmove(array + y + x, c, z * sizeof(int));
    return array;
}


int main(){
    /* testing exercise. Feel free to modify */
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    int a3[] = { 20, 21, 22 };

    int *joined = join_arrays(5, a1, 8, a2, 3, a3);

    for (int i = 0; i < 5 + 8 + 3; i++) {
        printf("%d  ", joined[i]);
    }
    printf("\n");
    
    free(joined);
    return 0;
}