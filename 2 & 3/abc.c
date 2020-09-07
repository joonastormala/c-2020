#include <stdio.h>

int array_sum(int *array, int count){
    int temp = 0;
    for (int i = 0; i < count; i++){
        temp = temp + array[i];
    }
    return temp;
}

unsigned int array_reader(int *vals, int n){
    int count = 0;
    int b = 0;
    while (scanf("%d", &b) == 1 && count < n){
        vals[count] = b;
        count++;       
    }
    return count;
}

unsigned int arraylen(const char *array){
    
}

int main(){
    // int valarray[] = { 10, 100, 1000 };
    // int ret = array_sum(valarray, 3);
    // printf("%d", ret);

    int array[10];
    unsigned int n = array_reader(array, 10);
    printf("%d numbers read\n", n);
    int i;
    for (i = 0; i < n; i++) {
    printf("%d ", array[i]);
    }

    return 0;
}