#include <stdio.h>
#include <string.h>

unsigned int arraylen(const char *array){
    // int j = 0;
    // for (int i = 0; array[i] != 0; i++, j++){}
    // return j;
    return strlen(array);
}

void countchars(const char *array, unsigned int *counts) {
    int x = 0;
    int j = 0;
    for(int i = 0; i < 256 ; i++)
    {
        for(j; j<strlen(array);j++,((i == array[j]) ? x++ : x));
        j = 0;
        counts[i] = x;
        x=0;
    } 
}

void printcounts(int min, int max, const unsigned int *counts) {
    for (int i = min; i <= max; i++) {
        printf("%c: %u  ---  ", i, counts[i]);
        if ((i - min + 1) % 6 == 0)
            printf("\n");
    } 
}

void printarray(const char *array) {
    printf("{ ");
    while (*array) {
        printf("'%c',", *array);
        array++;
    }
    printf("0 }");
}

int main()
{
    unsigned int counts[256] = { 0 };

    char sample[] = { 'a','b','r','a','c','a','d','a','b','r','a',0 };

    printf("%s, length: %u\n", sample, arraylen(sample));
    countchars(sample, counts);
    printcounts('a', 'z', counts);

    return 0;
}