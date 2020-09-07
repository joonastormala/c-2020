#include <stdio.h>

int main(void)
{

// paska tapa tehä, keksi parempi ratkaisu
int taulu[6][6] = {
    {0,0,0,0,0,0},
    {0,1,2,3,4,5},
    {0,2,4,6,8,10},
    {0,3,6,9,12,15},
    {0,4,8,12,16,20},
    {0,5,10,15,20,25},  
};


    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%2d ", taulu[j][i]);
        }
        printf("\n");
    }
}


