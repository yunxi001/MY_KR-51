#include <REGX52.H>
#include "Key.h"
#include "Timer0.h"
#include "LCD1602.h"
#include "Delay.h"
#include "I2C.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned int Min,Sec,MinSec;
unsigned char RunFlag;

void Sec_Clock(void)
{
	if(RunFlag)
	{
		MinSec++;
		if(MinSec>=100)
		{
			MinSec=0;
			Sec++;
			if(Sec>=60)
			{
				Sec=0;
				Min++;
				if(Min>=60)
					Min=0;
			}
		}
	}
}
	
void main()
{
	LCD_Init();
	Timer0Init();
	
	while(1)
	{
		KeyNum=Key();
		LCD_ShowString(1,1,"miao biao");
		if(KeyNum==1)
		{
			RunFlag=!RunFlag;
	  }
		if(KeyNum==2)
		{
			 Min=0;Sec=0;MinSec=0;
	  }
			if(KeyNum==3)
		{
			 AT24C02_WriteByte(0,Min);
			 Delay(5);
			 AT24C02_WriteByte(1,Sec);
			 Delay(5);
			 AT24C02_WriteByte(2,MinSec);
			 Delay(5);
	  }
			if(KeyNum==4)
		{
			 Min=AT24C02_ReadByte(0);
			 Sec=AT24C02_ReadByte(1);
			 MinSec=AT24C02_ReadByte(2);
	  }
			LCD_ShowNum(2,1,Min,2);
			LCD_ShowChar(2,3,':');
			LCD_ShowNum(2,4,Sec,2);
			LCD_ShowChar(2,6,':');
			LCD_ShowNum(2,7,MinSec,2);
	}
}

void Timr0_Routine() interrupt 1
{
	static unsigned int T0Count1=0,T0Count2=0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count1++;
	if(T0Count1>=20)
	{
		T0Count1=0;
		Key_Loop();
	}
	T0Count2++;
	if(T0Count2>=10)
	{
		T0Count2=0;
		Sec_Clock();
	}

}
