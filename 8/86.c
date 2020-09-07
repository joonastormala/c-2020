#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void confidentiality_xor(uint32_t key, void* data, int len){
  for(int i=0;i<len;i++){
    ((uint32_t*)data)[i]=(((uint32_t*)data)[i]^key);
  }
}
void confidentiality_xor_shift(uint32_t key, void* data, int len)
{
  uint32_t a=key;
  for(int i=0;i<len;i++){
    ((uint32_t*)data)[i]=(((uint32_t*)data)[i]^key);
    a=key;
    a=a>>31;
    key = ((key<<1)|a);
  }
}
