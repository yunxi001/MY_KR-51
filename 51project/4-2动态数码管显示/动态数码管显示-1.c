#include <REGX52.H>
#include <INTRINS.H>

unsigned char nixietable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


void Delay(unsigned int xms)  //@11.0592MHz
{
 while(xms)
 {
  unsigned char i, j;
  
  _nop_();
  i = 2;
  j = 199;
  do
  {
   while (--j);
  } while (--i);
  xms--;
 }
 
}

void nixie(unsigned char location,unsigned char number)
{
 switch(location)
 {
  case 1:P2_0=0;break;
  case 2:P2_1=0;break;
  case 3:P2_2=0;break;
  case 4:P2_3=0;break;
  
 }
 P0=nixietable[number];
 
}

void main()
{
	 unsigned int x=0;
 while(1)
 {
  //nixie(1,0);
  //Delay(2);
  //nixie(2,1);
  //Delay(2);
  //nixie(3,2);
  //Delay(2);
	 nixie(1,0);
	 nixie(2,0);
	 nixie(3,0);
	 nixie(4,0);
//	 if(x<=9)
//	 {
//  nixie(4,x++);
//  Delay(1000);
//	 }
//	 else{
//		  nixie(4,0);
//  Delay(1000);
//	 x=1;}
 }
}