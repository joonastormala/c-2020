#include <stdio.h>
#include <string.h>

int file_to_hex(const char *filename){
  int c,bytes=0,tab=0;

  FILE *f=fopen(filename,"r");
  if (!f)
    return -1;
  do{
    c=fgetc(f);
    if (feof(f))
    break;
    bytes++;
    if (c < 0x10)
    printf("%02x ", c);
    else
    printf("%x ", c);
    tab++;
    if (tab % 16 == 0)
    printf("\n");
  }while (1);

  fclose(f);
  return bytes;
}

int main(void)
{
    if (file_to_hex("91.c") == -1) {
         fprintf(stderr, "Could not open 91.c\n");
    }
    return 0;
}