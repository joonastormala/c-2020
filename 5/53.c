#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *create_dyn_array(unsigned int n){
    int *table;
    table = malloc((n + 1) * sizeof(int));
    for(unsigned int i = 0; i < n; i++){
        scanf("%d", &table[i]);
    }
    return table;
}

int *add_dyn_array(int *arr, unsigned int num, int newval){
    num++;
    int *rarr = realloc(arr, num * sizeof(int));
    num--;
    rarr[num] = newval;
    return rarr;
}

int main(){
    
    //create_dyn_array(5);

    return 0;
}