#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Function, that copies the string str as reversed to the buffer copy.
 * The copied string should be a valid string in C, i.e. it ends with '\0'.
 * During the copying, all characters are converted to uppercase characters
 * with the toupper function.
 */
void copy_reversed_as_upper(const char* str, char* copy) {
    
    int c = 0, i = 0;;
    char ph;
    while(str[c] != '\0') c++;
    int last = c - 1;
    for(; i < c; i++){
        copy[i] = toupper(str[last]);
        last--;
    }
    copy[i]=0;
}

void my_tests(void)
{
    char str[] = "45s7or3011km7t50bwg";
    char copy[13];
    copy_reversed_as_upper(str, copy);
    printf("%s", copy);
}

int main(void)
{
    /* You may implement your own tests in my_tests function */
    my_tests();

    /* To enable automatic grading, uncomment the below
    function call for hidden function grading_tests */
    //grading_tests();
}