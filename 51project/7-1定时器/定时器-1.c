
#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include <INTRINS.H>
unsigned char KeyNum,LedMode;
void main()
{
	P1=0xFE;
	Timer0Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{		
				LedMode++;
				if(LedMode>=2)
					LedMode=0;
			
			}
		}
	}
}


void Timr0_Routine() interrupt 1
{
	static unsigned int T0Count=0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=300)
	{
		T0Count=0;
		if(LedMode==0)
			P1=_crol_(P1,1);
		if(LedMode==1)
			P1=_cror_(P1,1);
	}

} 
