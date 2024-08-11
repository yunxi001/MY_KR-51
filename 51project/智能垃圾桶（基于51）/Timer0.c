#include <REGX52.H>

void Timer0Init(void)		//500微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x33;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;		//打开定时器0中断
	EA  = 1;		//打开总中断EA
}




/* 模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count=0;
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	T0Count++;
	if(T0Count>=100)
	{
		T0Count=0;
		P1_0=~P1_0;
	}

} 
*/