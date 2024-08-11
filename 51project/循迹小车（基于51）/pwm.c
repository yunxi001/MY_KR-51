//#include <REGX52.H>
//#include "Timer0.h"

//sbit IN1=P1^0;
//sbit IN2=P1^1;
//sbit IN3=P1^2;
//sbit IN4=P1^3;

//unsigned char Counter;

//void speed_left(unsigned char speed0) //定义占空比，电机左转调速
//{
//	if(Counter<speed0)
//	{IN2=1;}
//	else
//	{IN2=0;}
//}
//void speed_right(unsigned char speed1) //定义占空比，电机右转调速
//{
//	if(Counter<speed1)
//	{IN4=1;}
//	else
//	{IN4=0;}
//}
//void qianjin() //小车前进
//{
//	Timer0Init();
//	speed_left(3);
//	speed_right(5);
////	IN2=1;
////	IN4=1;
//}
//void zuozhuan() //小车左转
//{
//	Timer0Init();
//	speed_right(5);
//	IN2=0;

//}
//void youzhuan() //小车右转
//{
//	Timer0Init();
//	speed_left(5);
//	IN4=0;

//}
//void tingzhi() //小车停止
//{
//	IN2=0;
//	IN4=0;
//}

//void Timer0_Pwm() interrupt 1
//{
//	TL0 = 0xF7;		//设置定时初值
//	TH0 = 0xFF;		//设置定时初值
//	Counter++;
//	Counter%=100;
//} 
////void Timer0_Pwm1()	interrupt 1	
////{
////	TL0 = 0x00;		//设置定时初值
////	TH0 = 0x4C;		//设置定时初值
////	Counter1++;
////	Counter1%=1000;
////}

