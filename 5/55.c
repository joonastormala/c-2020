#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delete_comments(char *input){
    
    char *cStart, *cEnd;
    char *ptr2, *l=NULL, *ptr;

    for(ptr2 = input; (l=strstr(ptr2, "//")); ptr2 = l+1){
        ptr=strstr(input, "//");
        cStart = ptr;
        while(*ptr != '\n'){
            ptr++;
        }
        ptr++;
        // printf("pituus s: %d\n", strlen(cStart));
        // printf("pituus p: %d\n", strlen(ptr));  
        memmove(cStart, ptr, (strlen(ptr)+1)*sizeof(char));

    }    

    for(ptr2 = input; (l=strstr(ptr2, "/*")); ptr2 = l+1){
        ptr = strstr(input, "/*");
        cStart = ptr;
        cEnd = strstr(input, "*/");    
        memmove(cStart, cEnd+2, (strlen(cEnd))*sizeof(char));
    }
    return input;

}


/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    
    char *buf = NULL;
    unsigned int count = 0;
    const unsigned int ReadBlock = 100;
    unsigned int n;
    do {
        buf = realloc(buf, count + ReadBlock + 1);
        n = fread(buf + count, 1, ReadBlock, f);
        count += n;
    } while (n == ReadBlock);
    
    buf[count] = 0;
    
    fclose(f);
    return buf;
}


int main(void)
{
    char *code = read_file("testfile.c");
    if (!code) {
        printf("No code read");
        return -1;
    }
    printf("-- Original:\n");
    fputs(code, stdout);

    code = delete_comments(code);
    printf("-- Comments removed:\n");
    fputs(code, stdout);
   
    free(code);

    return 0;
}