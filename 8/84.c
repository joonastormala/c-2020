#include <stdio.h>
#include <stdlib.h>


void op_bit_set(unsigned char* data, int i) {
    if (i>7){
        data += (i/8); // move pointer
        i= i % 8;
    }
    unsigned char bits=1;
    if (i!=7){
        while(i!=7){
            bits= bits * 2;
            i++;
        }
    }
    data[0]=(data[0]|bits);
}

void op_bit_unset(unsigned char* data, int i){
    if (i>7){
        data += (i/8);
        i= i % 8;
    }
    unsigned char bits=1;
    if (i!=7){
        while(i!=7){
            bits= bits * 2;
            i++;
        }
    }
    data[0]=~((~data[0])|bits);
}

int op_bit_get(const unsigned char* data, int i){
    if (i>7){
        data += (i/8);
        i = i % 8;
    }
    unsigned char bits=1;
    if (i!=7){
        while(i!=7){
        bits= bits * 2;
        i++;
        }
    }
    if (data[0]==(data[0]|bits)){
        return 1;
    }
    return 0;
}
void op_print_byte(unsigned char b){
    unsigned char a[0];
    a[0]=b;
    for(int i=0;i<8;i++){
        if(op_bit_get(a,i)) printf("1");
        else printf("0");
    }
}
unsigned char op_bit_get_sequence(const unsigned char* data, int i, int how_many){
    // if (i>7){
    //     data += (i/8);
    //     i = i % 8;
    // }
    // if (i+how_many<8 || i==0){
    //     unsigned char boi= data[0]<< (i-1);
    //     boi=(boi>>(i-1));
    //     boi=(boi>>(8-how_many));
    //     return boi;
    // }
    // else {
    //     unsigned char yeet=(data[0]<<(i));
    //     unsigned char ye=(data[1]>>(8-i));
    //     yeet = (yeet | ye);
    //     yeet=yeet>>(8-how_many);
    //     return yeet;
    // }

    unsigned char result = 0;
    for(int bit = 0; bit < how_many; ++bit){
        result <<= 1;
        result |= op_bit_get(data,i+bit);
    }
    return result;
}
