#include <stdio.h>
#include <stddef.h>

void qstr_print(const char *s){
    while(*s != '?'){
        printf("%c", *s);
        s++;
    }
}

unsigned int qstr_length(const char *s){
    int count = 0;
    while(*s != '?'){
        s++;
        count++;
    }
    return count;
}

int qstr_cat(char *dst, char *src){

    int i=0,j=0;

    while(dst[i] != '?'){
        i++;
    }
    while(src[j] != '?'){
        dst[i]=src[j];
        j++;
        i++;
    }
    dst[i] = '?';
    return qstr_length(dst);
    
}

const char *qstr_strstr(const char *str1, const char *str2){
    int i=0,j=0,k=0;
    while (str1[i] != '?')
    {
        k=i;
        while (str2[j] == str1[k])
        {
            j++;
            k++;
            if(str2[j]=='?'){
                str1 = str1 + i;
                return str1;
            }
        }
        j = 0;
        i++;
        
    }
    return NULL;
    
}

int main(){
    //char *str = "Auto ajoi?kilparataa";
    char dst[50] = "Auto ajoi?";
    char *src = " katua pitkin? lujaa";

    // char *str1 = "Auto ajoi katua pitkin?";
    // char *str2 = "katu?";

    // qstr_strstr(str1,str2);
    printf("%d", qstr_cat(dst, src));
    qstr_print(dst);
    // qstr_print(str);
    // printf("\n%d", qstr_length(str));
    return 0;
}