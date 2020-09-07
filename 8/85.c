#include <stdio.h>
#include <stdlib.h>

int getSourcePort(const unsigned char *tcp_hdr){
  int a=tcp_hdr[0];
  int b=tcp_hdr[1];
  a = (a<<8);
  a = (a | b);
  return a;

}
int getDestinationPort(const unsigned char *tcp_hdr){
  int a=tcp_hdr[2];
  int b=tcp_hdr[3];
  a = (a<<8);
  a = (a | b);
  return a;
}
int getAckFlag(const unsigned char *tcp_hdr){
  unsigned char a= tcp_hdr[13];
  a=a>>4;
  a=a<<7;
  a=a>>3;
  if(a)
  return 1;
  else
  return 0;
}
int getDataOffset(const unsigned char *tcp_hdr){
int ret=(tcp_hdr[12]>>4);
return ret;
}
void setSourcePort(unsigned char *tcp_hdr, int port){
  unsigned char a=(port>>8);
  unsigned char b=((port<<8)>>8);
  tcp_hdr[0]=a;
  tcp_hdr[1]=b;
}
void setDestinationPort(unsigned char *tcp_hdr, int port){
  unsigned char a=(port>>8);
  unsigned char b=((port<<8)>>8);
  tcp_hdr[2]=a;
  tcp_hdr[3]=b;
}
void setAckFlag(unsigned char *tcp_hdr, int flag){
  unsigned char p;
  switch (flag) {
    case 1:
      tcp_hdr[13]=(tcp_hdr[13]| 16 );
      break;
    case 0:
    p=(tcp_hdr[13]| 16 );
    tcp_hdr[13]=(p^16);
    break;
  }
}
void setDataOffset(unsigned char *tcp_hdr, int offset){
  tcp_hdr[12]=(tcp_hdr[12]<<4);
  tcp_hdr[12]=(tcp_hdr[12]>>4);
  tcp_hdr[12]=(tcp_hdr[12] | (offset<<4));
}
