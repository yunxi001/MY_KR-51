
//定义正反转和占空比
void Motor_left(bit ReverOrCoro,uchar DutyCycle)    //正反转 占空比
{
	if(ReverOrCoro == 1)
	{
		IN1=1;
		if(cnt <= DutyCycle)
		{
			IN2=0;
		}
		else
		{
			IN2=1;
		}
	}
	 else
	 {
		IN2=1;
		if(cnt <= DutyCycle)
		{
			IN1=0;
		}
		else
		{
			IN1=1;
		}
	 }
}

void Motor_right(bit ReverOrCoro,uchar DutyCycle)    //正反转 占空比
{
	if(ReverOrCoro == 1)
	{
		IN3=1;
		if(cnt <= DutyCycle)
		{
			IN4=0;
		}
		else
		{
			IN4=1;
		}
	}
	 else
	 {
		IN4=1;
		if(cnt <= DutyCycle)
		{
			IN3=0;
		}
		else
		{
			IN3=1;
		}
	 }
}
//选择定时器
void init()		//定时器T1工作方式1
{
	TMOD=0x10;
	TH1 = 0xff;
	TL1 = 0x9c;
	EA=1;
	ET1=1;
	TR1=1;
}
//中断
void InterruptTime0() interrupt 3
{
	TH1=0xff;
	TL1=0x9c;
	cnt++;
	if(cnt>=220)
	{
		cnt=0;
	}
}
//前进，左转，右转
void qianjin()       //前进
{
    Motor_left(1,80);
	Motor_right(1,80);
}


void turn_left()     //左转
{
    Motor_left(1,70);
	Motor_right(0,30);
}

void turn_right()    //右转
{
    Motor_left(0,30);
	Motor_right(1,70);
}
//四个传感器判断前进或者转向？？？
/*void xunji()   //四个传感器
{
  uchar flag;
	if((rsen1==0)&&(lsen1==0)||(rsen2==0)&&(lsen2==0))
	{
	  flag=0;
	}
	else
   if((rsen1==1)&&(lsen1==0)||(rsen2==1)&&(lsen2==0))
	{
	  flag=1;
	}
	else
	if((rsen1==0)&&(lsen1==1)||(rsen2==0)&&(lsen2==1))
	{
	  flag=2;
	}
*/
//两个传感器判断状态
void xunji()   //两个传感器
{
  uchar flag;
	if((rsen1==0)&&(lsen1==0))
	{
	  flag=0;
	}
	else
   if((rsen1==1)&&(lsen1==0))
	{
	  flag=1;
	}
	else
	if((rsen1==0)&&(lsen1==1))
	{
	  flag=2;
	}
	//通过信号检测不同情况执行不同函数
		switch(flag)
	{
		case 0:qianjin();break;
		case 1:turn_right();break;
		case 2:turn_left();break;
		default:break;
	}
//主函数
	void main()
{
    init();
	while(1)
	{
	  xunji();
	}
}
//全函数
#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit IN1=P1^0;
sbit IN2=P1^1;
sbit IN3=P1^2;
sbit IN4=P1^3;
sbit ENA=P1^4;
sbit ENB=P1^5;

sbit lsen1=P2^0;
sbit rsen1=P2^1;
/*
sbit lsen2=P2^2;
sbit rsen2=P2^3;
*/


void  Motor_right();   //声明函数
void  Motor_left();

uchar ReverOrCoro;
uchar cnt=0;

/*void delayms(uchar xms)
{
  int x,y;
	for(x=xms;x>0;x--)
	for(y=110;y>0;y--);
}*/

void Motor_left(bit ReverOrCoro,uchar DutyCycle)    //正反转 占空比
{
	if(ReverOrCoro == 1)
	{
		IN1=1;
		if(cnt <= DutyCycle)
		{
			IN2=0;
		}
		else
		{
			IN2=1;
		}
	}
	 else
	 {
		IN2=1;
		if(cnt <= DutyCycle)
		{
			IN1=0;
		}
		else
		{
			IN1=1;
		}
	 }
}

void Motor_right(bit ReverOrCoro,uchar DutyCycle)    //正反转 占空比
{
	if(ReverOrCoro == 1)
	{
		IN3=1;
		if(cnt <= DutyCycle)
		{
			IN4=0;
		}
		else
		{
			IN4=1;
		}
	}
	 else
	 {
		IN4=1;
		if(cnt <= DutyCycle)
		{
			IN3=0;
		}
		else
		{
			IN3=1;
		}
	 }
}

void init()		//定时器T1工作方式1
{
	TMOD=0x10;
	TH1 = 0xff;
	TL1 = 0x9c;
	EA=1;         //打开总中断
	ET1=1;
	TR1=1;
}

void InterruptTime0() interrupt 3
{
	TH1=0xff;
	TL1=0x9c;
	cnt++;
	if(cnt>=220)
	{
		cnt=0;
	}
}

void qianjin()
{
    Motor_left(1,80);
	Motor_right(1,80);
}


void turn_left()
{
    Motor_left(1,70);
	Motor_right(0,30);
}

void turn_right()
{
    Motor_left(0,30);
	Motor_right(1,70);
}

/*void xunji()   //四个传感器
{
  uchar flag;
	if((rsen1==0)&&(lsen1==0)||(rsen2==0)&&(lsen2==0))
	{
	  flag=0;
	}
	else
   if((rsen1==1)&&(lsen1==0)||(rsen2==1)&&(lsen2==0))
	{
	  flag=1;
	}
	else
	if((rsen1==0)&&(lsen1==1)||(rsen2==0)&&(lsen2==1))
	{
	  flag=2;
	}
*/

void xunji()   //两个传感器
{
  uchar flag;
	if((rsen1==0)&&(lsen1==0))
	{
	  flag=0;
	}
	else
   if((rsen1==1)&&(lsen1==0))
	{
	  flag=1;
	}
	else
	if((rsen1==0)&&(lsen1==1))
	{
	  flag=2;
	}
	
	switch(flag)
	{
		case 0:qianjin();break;
		case 1:turn_right();break;
		case 2:turn_left();break;
		default:break;
	}
		
}

void main()
{
    init();
	while(1)
	{
	  xunji();
	}
}


