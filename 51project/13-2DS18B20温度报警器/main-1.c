#include <REGX52.H>
#include "Delay.h"
#include "I2C.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "key.h"
#include "Timer0.h"

float T;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	while(1)
	{
	
		/*温度读取及显示*/
		DS18B20_ConvertT();
		T=DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			T=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			
		}
		LCD_ShowNum(1,4,T,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(T*100)%100,2);
	}
}


//float T,TShow;
//char TLow,THigh;
//unsigned char KeyNum;

//void main()
//{
//	LCD_Init();
//	LCD_ShowString(1,1,"T:");
//	LCD_ShowString(2,1,"TH:");
//	LCD_ShowString(2,9,"TL:");
//	LCD_ShowSignedNum(2,4,THigh,3);
//	LCD_ShowSignedNum(2,12,TLow,3);
//	Timer0Init();
//	while(1)
//	{
//		KeyNum=Key();
//		/*温度读取及显示*/
//		DS18B20_ConvertT();
//		T=DS18B20_ReadT();
//		if(T<0)
//		{
//			LCD_ShowChar(1,3,'-');
//			TShow=-T;
//		}
//		else
//		{
//			LCD_ShowChar(1,3,'+');
//			TShow=T;
//		}
//		LCD_ShowNum(1,4,TShow,3);
//		LCD_ShowChar(1,7,'.');
//		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
//		/*阈值判断及显示*/
//		if(KeyNum)
//		{
//				if(KeyNum==1)
//			{
//				THigh++;
//				if(THigh>125){THigh=125;}
//			}
//			if(KeyNum==2)
//			{
//				THigh--;
//				if(THigh<=TLow){THigh++;}
//			}
//			if(KeyNum==3)
//			{
//				TLow++;
//				if(TLow>=THigh){TLow--;}
//			}
//			if(KeyNum==4)
//			{
//				TLow--;
//				if(TLow<-55){TLow=-55;}
//			}
//			LCD_ShowSignedNum(2,4,THigh,3);
//			LCD_ShowSignedNum(2,12,TLow,3);
//		}
//		if(T>THigh)
//		{
//			LCD_ShowString(1,13,"OV:H");
//		}
//		else if(T<TLow)
//		{
//			LCD_ShowString(1,13,"OV:L");
//		}
//		else
//		{
//			LCD_ShowString(1,13,"     ");
//		}
//	}
//}
//void Timr0_Routine() interrupt 1
//{
//	static unsigned int T0Count=0;
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	T0Count++;
//	if(T0Count>=20)
//	{
//		T0Count=0;
//		Key_Loop();
//	}

//} 