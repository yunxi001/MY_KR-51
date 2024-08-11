#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Delay.h"
#include "Nixie.h"

//sbit LED=P1^0;
sbit DA=P2^0;
unsigned char Counter,Compare;
unsigned char i;

void main()
{
	Timer0Init();
	while(1)
	{
		for(i=0;i<100;i++)
		{
			Compare=i;
			Delay(10);
		}
		for(i=0;i>0;i--)
		{
			Compare=i;
			Delay(10);
		}
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
//		LED=0;
		DA=1;
	}
	else
	{
//		LED=1;
		DA=0;
	}	
} 