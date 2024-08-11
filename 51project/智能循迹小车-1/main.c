#include <REGX52.H>
//#include "infrared.h"
#include "Delay.h"
//#include "Timer0.h"

sbit IN1=P1^3;  
sbit IN2=P1^2;  	//IN2=0;IN1=1;  右轮正转
sbit IN3=P1^1;
sbit IN4=P1^0;      //IN3=1;IN4=0;  左轮正转

sbit  hw1=P3^0;    	//左传感器
sbit  hw2=P3^1;    	//右传感器
sbit  hw3=P3^2;    	//中间传感器

unsigned char speed_left_z,speed_right_z,speed_left_f,speed_right_f;
unsigned int i=0,Counter=0;

void qianjin() 	//小车前进
{
	speed_left_f=0;
	speed_right_f=0;
	speed_left_z=60;
	speed_right_z=45;
	IN2=0;
	IN1=1;    	//右轮正转
	IN3=1;
	IN4=0;    	//左轮正转
}
void zuozhuan() //小车左转
{
	speed_right_f=0;
	speed_left_z=0;
	speed_right_z=70;
	speed_left_f=80;
	IN2=0;
	IN1=1;   	 //右轮正转
	IN3=0;
	IN4=1;    	 //左轮倒转
}

void youzhuan() //小车右转
{
	speed_left_f=0;
	speed_right_z=0;
	speed_left_z=80;
	speed_right_f=60;
	IN3=1;
	IN4=0;    //左轮正转
	IN2=1;
	IN1=0;    //右轮倒转
}

void tingzhi() //小车停止
{
	speed_left_z=0;
    speed_right_f=0;
	speed_right_z=0;
	speed_left_f=0;
	IN1=0;
	IN3=0;
	IN2=0;
	IN4=0;
}


//void Timer0Init(void)		//1微秒@11.0592MHz
//{
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0xFF;		//设置定时初始值
//	TH0 = 0xFF;		//设置定时初始值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//	ET0=1;
//	EA=1;
//}
void Timer0Init(void)		//10微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xF7;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
}


void Timer0() interrupt 1
{
	TL0 = 0xFF;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;
	if(Counter<speed_left_z)//左电机正转调速
	{IN3=1;}
	else
	{IN3=0;}
	
	if(Counter<speed_right_z)//右电机正转调速
	{IN1=1;}
	else
	{IN1=0;}
	
	if(Counter<speed_left_f)//左电机反转调速
	{IN4=1;}
	else
	{IN4=0;}
	
	if(Counter<speed_right_f)//右电机反转调速
	{IN2=1;}
	else
	{IN2=0;}
}

void  main()
{
	Timer0Init();
	while(1)
  {  
	 Delay(1);
	  	if((hw1==0)&&(hw2==0)&&(hw3==1))
		{
			i=1;		//前进
		}
	    else if((hw1==0)&&(hw2==1))
		{
			i=2;		//右转
		}
	    else if((hw1==1)&&(hw2==0))
		{
			i=3;		//左转
		}
	    else {i=4;}
	switch(i)
	{
		case 1:  qianjin();	break;		//前进
		case 2:  youzhuan(); break;		//右转
		case 3:  zuozhuan(); break;		//左转
		case 4:	 tingzhi();break;		//停止
		default: tingzhi();break;		//停止
	}
  }
}