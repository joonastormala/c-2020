#include <stdio.h>
#include <ctype.h>


void draw_triangle(unsigned int size){
    int j,k;
    for (int i = size; i >= 1; i--){
        for(j = 1; j<=i-1; j++){
            printf(". ");
        }
        for(k= size; k>i-1; k--){
            printf("# ");
        }

    printf("\n");    
    }
    
}

void ascii_chart(char min, char max){
    for (int i = min; i <= max; ++i) {
        printf("%3d 0x%02x %c%s", i, i, (isprint(i) ? i : '?'), ((i % 4 == 3) ? "\n" : "\t"));
    }
}

int main(){
    draw_triangle(6);
    ascii_chart(28,38);
    return 0;
}
