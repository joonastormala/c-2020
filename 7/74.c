#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Split string by another string, return split parts + NULL in array.
 *
 * Parameters: 
 *  str: the string to split
 *  split: the string to split str with
 *
 * Returns:
 *  A dynamically reserved array of dynamically reserved string parts.
 *
 * For example called with "Test string split" and " ",
 * returns ["Test", "string", "split", NULL].
 * Or called with "Another - test" and " - ",
 * returns ["Another", "test", NULL].
 */

char** split_string(const char *str, const char* split) {
    char** arr = NULL;
    int i = 0;

    while (str[0]){
        const char* end = strstr(str,split);
        int len = end-str;

        if(!end) len = strlen(str);
        if(len > 0){
            arr = realloc(arr,(i+2)*sizeof(char*));
            arr[i] = malloc(len+1);
            strncpy(arr[i],str,len);
            arr[i][len]='\0';
            i++;
        }        
        str+=(len+(end?strlen(split):0)); //if(end) strlen(split); else 0;
    }
    arr[i]=NULL;
    return arr;
}

void print_split_string(char **split_string) {
    for(int i = 0; split_string[i] != NULL; i++){
        printf("%s\n", split_string[i]);
    }
}

void free_split_string(char **split_string) {
    char** s = split_string;
    while (*s){
        free(*s);
        s++;
    }
    free(split_string);
}

int main() {
    char str1[] = "Test string split with this test string";
    char str2[] = "Another - test - for - string - split";
    char str3[] = "Split_ab!#this_ab!#case_ab!#correctly_ab!#too!";

    char** str1_split = split_string(str1, " ");
    char** str2_split = split_string(str2, " - ");
    char** str3_split = split_string(str3, "_ab!#");
    
    printf("\"%s\" split:\n", str1);
    print_split_string(str1_split);

    printf("\n\"%s\" split:\n", str2);
    print_split_string(str2_split);

    printf("\n\"%s\" split:\n", str3);
    print_split_string(str3_split);
    
    free_split_string(str1_split);
    free_split_string(str2_split);
    free_split_string(str3_split);

    return 0;
}
