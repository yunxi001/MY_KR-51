#include <REGX52.H>
#include "infrared.h"
#include "Delay.h"
#include "Timer0.h"

sbit IN1=P1^3;
sbit IN2=P1^2;
sbit IN3=P1^1;
sbit IN4=P1^0;

unsigned char Counter,speed1,speed2,speed3,speed4;

void qianjin() //小车前进
{
 IN2=1;
 IN4=1;
 IN1=0;
 IN3=0;
 speed1=10;
 speed2=13;
}
void zuozhuan() //小车左转
{
 IN4=1;
 IN1=1;
 IN2=0;
 IN3=0; 
 speed2=3;
 speed3=2;
}

void youzhuan() //小车右转
{
 IN2=1;
 IN3=1;
 IN1=0;
 IN4=0;
 speed1=2;
 speed4=3;
}

void tingzhi() //小车停止
{
 IN1=0;
 IN3=0;
 IN2=0;
 IN4=0;
}

void  main()
{
 Timer0Init();
 while(1)
  {  
 unsigned char i;
 i=infrared();
 switch(i)
 {
  case 0:  qianjin(); break;  //前进
  case 1:  youzhuan(); break;  //右转
  case 2:  zuozhuan(); break;  //左转
  case 3:  tingzhi();break;  //停止
  default: tingzhi();    //停止
 }
  }
}

void Timer0_Pwm() interrupt 1
{
 TL0 = 0xF7;  //设置定时初值·
 TH0 = 0xFF;  //设置定时初值
 Counter++;
 Counter%=1000;
 if(Counter<speed1)//左电机正转调速
 {IN2=1;}
 else
 {IN2=0;}
 
 if(Counter<speed2)//右电机正转调速
 {IN4=1;}
 else
 {IN4=0;}
 
 if(Counter<speed3)//左电机反转调速
 {IN1=1;}
 else
 {IN1=0;}
 
 if(Counter<speed4)//右电机反转调速
 {IN3=1;}
 else
 {IN3=0;}
}