#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int print_file_and_count(const char *filename){
    int c, bytes = 0;
    FILE *f = fopen(filename, "r");
    
    if(!f)
    return -1;
    
    do {
        c=fgetc(f);
        if(feof(f))
            break;
        bytes++;
        printf("%c", c);
    } while(1);
    
    fclose(f);
    return bytes;   
}

char *difference(const char* file1, const char* file2){
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if(!f1 || !f2) return 0;

    char buf1[100];
    char buf2[100];
    char *str1;
    char *str2;

    while(1){
        str1=fgets(buf1, 100, f1);
        str2=fgets(buf2, 100, f2);
        
        if(!str1 || !str2) return NULL;
        if (strcmp(str1,str2)) break;
    }

    int size1 = strlen(str1);
    int size2 = strlen(str2);
    char *space = "----\n";
    char *ret = malloc(sizeof(char) * size1 + size2 + 6);
    
    strcpy(ret, str1); strcat(ret, space); strcat(ret, str2);
    
    fclose(f1); fclose(f2);
    return ret;

}

int main(void)
{
    printf("--- Printing file:\n");
    int t = print_file_and_count("testifile.c");
    if(t<0)
        printf("Opening failed!\n");

    printf("\n--- Printed %d characters\n", t);

    char* diff = difference("testifile.c", "testifile2.c");
    printf("\n--- Difference:\n");
    printf("%s", diff);

    free(diff);

    return 0;
}
