#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int myprint(const char *str, ...){
    int c=0;
    const char *ptr = str;
    while (*ptr != 0){
        if(*ptr == '&') c++;
        ptr++;
    }
    va_list args;
    va_start(args, str);
    while(*str != 0){
        if(*str == '&'){
            printf("%d", va_arg(args, int));
        } else
            printf("%c",*str);
        str++;
    }
    va_end(args);

    return c;
}


int main(void)
{
    myprint("Hello!\n");
    myprint("Number: &\n", 5);
    myprint("Number one: &, number two: &\n", 120, 1345);
    int ret = myprint("Three numbers: & & &\n", 12, 444, 5555);
    myprint("I just printed & integers\n", ret);
}