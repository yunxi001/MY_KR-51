#include <REGX52.h>
#include "Delay.h"
#include "LCD1602.h"

//sbit TRIG=P2^0;
//sbit ECHO=P2^1;
sbit TRIG=P1^0;
sbit ECHO=P1^1;

    float dis;

    unsigned int time[10];
	unsigned int time0;
	unsigned long time_sum;
	unsigned char i,j;
	float time_out;

void timer1_init()  //定时器1初始化
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TH1=0x00;           //设置定时初值为0
	TL1=0x00;			//设置定时初值为0
	TF1 = 0;		//清除TF1标志
	TR1 = 0;		//定时器1开始计时
	ET1 = 0;		//禁止定时器1中断
	EA  = 1;		//打开总中断EA
}

void chaoshenbo_init() //超声波初始化
{
	TRIG=0;
	ECHO=1;
	timer1_init();
}

void main()  //超声波测距
{

	
	LCD_Init();
	chaoshenbo_init();
	Delay_1ms(1000);
	while(1)
	{
		
		for(i=0;i<10;i++)        //测量十次数据
		{
			TRIG=1;
			Delay_10us(2);
			TRIG=0;
			
			while(ECHO==0);    //等高电平
			
				TH1=0x00;           //设置定时初值为0
				TL1=0x00;			//设置定时初值为0
				TR1=1;				//打开定时器
			
			while(ECHO==1);    //等低电平
			TR1=0;              //关闭定时器
			time[i]=TL1+TH1*256;
			Delay_1ms(80);	
		}
		for(i=0;i<9;i++)
		{
			for(j=i+1;j<10;j++)  //进行升序排序
			{
				if(time[i]>time[j])
				{
					time0=time[i];
					time[i]=time[j];
					time[j]=time0;
				}
			}	
		}
		time_sum=0;
		for(i=2;i<8;i++)     //除去干扰数据
			{
				time_sum+=time[i];
			}
		time_out=(float)time_sum/6;
		dis=time_out*0.017;
			LCD_ShowString(1,2,"dis");
			LCD_ShowNum(2,1,dis,4);
			Delay_1ms(1000);
	}	
		
}
