#include <string.h>
#include <stdio.h>

int num_substr(const char *str, const char *sub){
    int count = 0;
    const char *ptr, *l = NULL;
    for(ptr=str; (l=strstr(ptr, sub)); ptr=l+1){
        count++;
    }
    return count;
}

int main(){
    num_substr("one two one twotwo three", "two");
    return 0;
}