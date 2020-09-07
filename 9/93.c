#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int line_count(const char *filename){
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int i = 0;
    char buffer[10000];
    char *ptr;

    while(1){
        ptr = fgets(buffer, 10000, f);
        if(ptr == NULL) break;
        i++;
        if(feof(f)) break;
    }
    fclose(f);
    return i;
}

int word_count(const char *filename){
    char a;
    int w=0,c=0;
    FILE *f = fopen(filename, "r");
    if (!f){
        return -1;
    }
    while(1){
        a=fgetc(f);
        if (feof(f)) break;
        if(isalpha(a)) c++;
        if(isspace(a) && c!=0){
            w++;
            c=0;
        }
    }
    if(c) w++;
    fclose(f);
    return w;
}

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is included. */
    char *filename = "testi.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    printf("Line count: %d\n", line_count(filename));
    
    //printf("Word count: %d\n", word_count(filename));
}