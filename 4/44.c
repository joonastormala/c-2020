#include <string.h>
#include <stdio.h>
#include <ctype.h>

char *my_toupper(char *dest, const char *src){
       
    int j=0;
    for(int i = 0;i<=(strlen(src) + (j-i));i++,j++){
        dest[j] = toupper(src[i]);
        if(dest[j] == '?'){
            dest[j] = '!';
        }
        if (dest[j] == '.'){
            dest[j] = '!';
            j++;
            dest[j] = '!';
            j++;
            dest[j] = '!';
        }
        
    }
    return dest;
}

int main(void)
{
	char dest[200];

	/* The following helps detecting string errors, e.g. missing final nil */
	memset(dest, '#', 199);
	dest[199] = 0;

	printf("%s",
	my_toupper(dest,
		"Would you like to have a sausage? It will be two euros. Here you are.\n"));

        printf("%s",
	my_toupper(dest,
		"Madam, where are you going? The health care center is over there.\n"));

	return 0;
}