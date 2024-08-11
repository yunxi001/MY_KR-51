#include <REGX52.H>

/**
  * @brief  对定时器初始化（定时器1） 
  * @param  无
  * @retval 无
  */
void Timer0Init()		//1毫秒@11.0592MHz
{

	TMOD &= 0xF0;		//设置定时器模式  把TMOD的低四位清零，高四位不变
	TMOD |= 0x01;		//设置定时器模式  把TMOD的最低位置1，高四位不变
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

/* 模板
/**
  * @brief  定时器使用模板
  * @param  无
  * @retval 无
  */
void Timr0_Routine() interrupt 1
{
	static unsigned int T0Count=0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=100)
	{
		T0Count=0;
		P1_0=~P1_0;
	}

} 
*/