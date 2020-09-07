
#include <string.h>
#include <stdio.h>


void addname(char *buffer, const char *addme, unsigned int maxsize)
{
    const char *b = ",";
    if(strlen(buffer) < maxsize - 1){
        int a = maxsize - 1 - strlen(buffer);       
        strncat(buffer, addme, a);   
    }
    if(strlen(buffer) < maxsize - 1){
        strcat(buffer, b);
    }
}


int main(void)
{
    char result[30] = { 0 }; // fills result with all zeros

    addname(result, "Reiska", 30);
    addname(result, "Bilbo Reppuli", 30);
    addname(result, "Henri Hinaaja", 30);
    addname(result, "Urpo Turpo", 30);

    printf("We have: %s\n", result);
    const char *expected = "Reiska,Bilbo Reppuli,Henri Hi";
    printf("We expected: %s\n", expected);
    if (!strcmp(result, expected)) {
	printf("Looking good!\n");
    } else {
	printf("Not quite right...\n");
    }

    return 0;
}


