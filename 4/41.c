#include <stdio.h>
#include <ctype.h>

int count_isalpha(const char *str){
    int count = 0;
    while(*str != '\0'){
        if(isalpha(*str)){
            count++;
        }
        str++;
    }
    return count;

}

int main(){

    // char abc[] = {'a','b','c','1','2','\0'};
    // printf("%d", count_isalpha(abc));
    return 0;
}