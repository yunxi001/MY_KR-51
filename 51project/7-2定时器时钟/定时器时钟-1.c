#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"

unsigned char sec,min,hour;

void main()
{

	LCD_Init();
	LCD_ShowString(1,1,"Clock:");
	
	LCD_ShowChar(2,3,':');
	LCD_ShowChar(2,6,':');
	Timer0Init();	
	while(1)
	{

		LCD_ShowNum(2,1,hour,2);
		LCD_ShowNum(2,4,min,2);
		LCD_ShowNum(2,7,sec,2);
	}
}

void Timr0_Routine() interrupt 1
{
	static unsigned int T0Count=0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		
		T0Count=0;
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			
		}
		if(min>=60)
		{
			min=0;
			hour++;
		}
		if(hour>=24)
		{
			hour=0;
		}
	}

} 