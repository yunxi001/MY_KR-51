#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

#define SPEED 500
//#define P   0
//#define L1  1
//#define L1_ 2
//#define L2  3
//#define L2_ 4
//#define L3  5
//#define L4  6
//#define L4_ 7
//#define L5  8
//#define L5_ 9
//#define L6  10
//#define L6_ 11
//#define L7  12
//#define M1  13
//#define M1_ 14
//#define M2  15
//#define M2_ 16
//#define M3  17
//#define M4  18
//#define M4_ 19
//#define M5  20
//#define M5_ 21
//#define M6  22
//#define M6_ 23
//#define M7  24
//#define H1  25
//#define H1- 26
//#define H2  27
//#define H2- 28
//#define H3  29
//#define H4  30
//#define H4_ 31
//#define H5  32
//#define H5- 33
//#define H6  34
//#define H6_ 35
//#define H7  36

sbit Buzzer=P2^5;
unsigned int FreTable[]={0,
63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,
64580,64633,64684,64732,64777,64820,64860,64898,64934,64987,65000,65030,
65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,};

unsigned char FreSelect,MusicSelect;
unsigned char Music[]={
	
	      
			13,4,
			13,4,
			20,4,
			20,4,
			22,4,
			22,4,
			20,4+4,
			0,4,
			18,4,
			18,4,
			17,4,
			17,4,
			15,4,
			15,4,
			13,4+4,
	
			0xff,
};
void main()
{
	Timer0Init();
	while(1)
	{
		if(FreSelect=Music[MusicSelect]!=0xff)
		{
		 FreSelect=Music[MusicSelect];
		MusicSelect++;
		Delay( SPEED/4*Music[MusicSelect]);
		MusicSelect++;
		TR0=0;
		Delay(5);
		TR0=1;
		}
		else
		{
		TR0=0;
		while(1);
		}		
	}
}
void Timr0_Routine() interrupt 1
{
	if(FreTable[FreSelect])
	TL0 = FreTable[FreSelect]%256;		//设置定时初值
	TH0 = FreTable[FreSelect]/256;		//设置定时初值
	
	Buzzer=!Buzzer;
	
} 
