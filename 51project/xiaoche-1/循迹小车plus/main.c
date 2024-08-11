#include <REGX52.H>
#include "RED.h"
#include "Delay.H"

sbit IN1=P1^1;
sbit IN2=P1^0;
sbit IN3=P1^2;
sbit IN4=P1^3;

unsigned char Left_zkb;  	//左电机转速设定
unsigned char Right_zkb;    //右电机转速设定

unsigned char Left_turning_zkb;  	//左电机反转转速设定
unsigned char Right_turning_zkb;    //右电机反转转速设定
unsigned int i=0;

unsigned int F;

void forward_move()
{
    Left_zkb=1;//PWM调速，值越大，电机速度越快
    Right_zkb=1;
    IN1=0;   	//两个电机均正转
    IN2=1; 
    IN3=0;
    IN4=1;
}
//小车左转速度赋值（用于左边传感器检测到黑线）
void Left_turning()
{
    Left_zkb=15;
    Right_turning_zkb=10;
    IN1=0;       //两个电机一个正转一个反转（或者一个正转一个不转） 
    IN2=1;//改
    IN3=1;		  
    IN4=0;
}
 
//小车右转速度赋值（用于右边传感器检测到黑线）
void Right_turning()
{
    Left_turning_zkb=10;
    Right_zkb=15;
    IN1=1;	  //两个电机一个正转一个反转（或者一个正转一个不转） 
    IN2=0;
    IN3=0;	  
    IN4=1;//改
}
void Delay_forward_move()
{
	Delay(1000);
	Left_zkb=1;//PWM调速，值越大，电机速度越快
    Right_zkb=1;
    IN1=0;   	//两个电机均正转
    IN2=1; 
    IN3=0;
    IN4=1;
}
void stop()
{
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=0;
}

void Timer0Init(void)		//1微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xFF;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
}

//void Timer0Init(void)		//10微秒@11.0592MHz
//{
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0xF7;		//设置定时初始值
//	TH0 = 0xFF;		//设置定时初始值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//}

 
//定时器中断服务产生pwm信号
void Timer0() interrupt 1
{
	TH0 = 0xF7;//初始化便于后续计时 
	TL0 = 0xFF;//初始化便于后续计时 
	i++;
	i%=1000;
	if(i<Left_zkb)
	{
	IN2=1;
	}
	else
	{
	IN2=0;
	}//左轮调速
	if(i<Right_zkb)
	{
		IN4=1;
	}
	else 
	{
		IN4=0;
	}//右轮调速
	
//	  IN1=0;   	//两个电机均正转
//    IN2=1; 
//    IN3=0;
//    IN4=1;
	if(i<Left_turning_zkb)//左电机反转调速
	{
	IN1=1;
	}
	 else
	 {
	 IN1=0;
	 }
	 
	if(i<Right_turning_zkb)//右电机反转调速
	 {
	 IN3=1;
	 }
	 else
	 {
	 IN3=0;
	 }
}
void main()
{	
	
	//黑色为1 白色为0
	
	Timer0Init();	
	while (1)
	{   
		F=RED();
		switch(F)
	{
		case 0:  Right_turning();break;
		case 1:  Left_turning();break;
		case 3:  forward_move();break;
		case 4:  Delay_forward_move();break;
		default: stop();break;
	}
	}
}
