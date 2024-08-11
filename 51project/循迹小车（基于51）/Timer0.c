
#include <REGX52.H>
//电机频率过慢会产生抖动，此次用频率较高的
//void Timer0Init(void)  //100微秒@11.0592MHz
//{
// TMOD &= 0xF0;  //设置定时器模式
// TMOD |= 0x01;  //设置定时器模式
// TL0 = 0xA4;  //设置定时初值
// TH0 = 0xFF;  //设置定时初值
// TF0 = 0;  //清除TF0标志
// TR0 = 1;  //定时器0开始计时
//}

void Timer0Init(void)  //10微秒@11.0592MHz
{

 TMOD &= 0xF0;  //设置定时器模式
 TMOD |= 0x01;  //设置定时器模式
 TL0 = 0xF7;  //设置定时初值
 TH0 = 0xFF;  //设置定时初值
 TF0 = 0;  //清除TF0标志
 TR0 = 1;  //定时器0开始计时
	
	ET0=1;
	EA=1;

}



//void Timer1Init1(void)  //50000微秒@11.0592MHz
//{

// TMOD &= 0x0F;  //设置定时器模式
// TMOD |= 0x10;  //设置定时器模式
// TL1 = 0x00;  //设置定时初值
// TH1 = 0x4C;  //设置定时初值
// TF1 = 0;  //清除TF1标志
// TR1 = 1;  //定时器1开始计时
//}






/* 模板
void Timer0_Routine() interrupt 1
{
 static unsigned int T0Count=0;
 TL0 = 0xA4;  //设置定时初值
 TH0 = 0xFF;  //设置定时初值
 T0Count++;
 if(T0Count>=100)
 {
  T0Count=0;
  P1_0=~P1_0;
 }

} 
*/