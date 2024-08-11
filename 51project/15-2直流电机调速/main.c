#include <REGX52.H>
#include "Timer0.h"
//#include "Key.h"
//#include "Delay.h"
//#include "Nixie.h"

sbit LED=P1^0;
//sbit Motor=P2^0;
unsigned char Counter,Compare;
//unsigned char KeyNum;
//unsigned int Speed;

void main()
{
	Timer0Init();
	Compare=5;
	while(1)
	{
//		KeyNum=Key();
//		if(KeyNum==1)
//		{
//			Speed++;
//			Speed%=4;
//			if(Speed==0){Compare=0;}
//			if(Speed==1){Compare=50;}
//			if(Speed==2){Compare=75;}
//			if(Speed==2){Compare=100;}
//		}
//		Nixie(4,Speed);
	}
}
void Timr0_Routine() interrupt 1
{
	
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;
	if(Counter<Compare)
	{
		LED=0;
//		Motor=1;
	}
	else
	{
		LED=1;
//		Motor=0;
	}	
} 