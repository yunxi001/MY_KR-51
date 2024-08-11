#include <REGX52.H>
#include "Delay.h"
unsigned char NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


void Nixie(unsigned char location,unsigned char number)
{
 switch(location)
 {
  case 1:P2_0=0;break;
  case 2:P2_1=0;break;
  case 3:P2_2=0;break;
  case 4:P2_3=0;break;
  
 }
 P0=NixieTable[number];
 Delay(1);
 P0=0x00;
}