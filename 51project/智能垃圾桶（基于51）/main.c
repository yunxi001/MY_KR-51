#include "REGX52.h"
#include "Timer0.h"
#include "Delay.h"
#include "chaoshenbuocejv.h"


sbit TS90A = P2^2;
unsigned int speed,time=0;
float distence; 
 
 /*
对于MG 996R舵机  20ms
0.5ms--------------0度； 2.5% （0.5ms高电平+19.5低电平）
1.0ms------------45度； 5.0% （1.0ms高电平+19.0低电平）
1.5ms------------90度； 7.5% （1.5ms高电平+18.5低电平）
2.0ms-----------135度；10% （2.0ms高电平+18.0低电平）
2.5ms-----------180度；12.5%（2.5ms高电平+17.5低电平）
*/

void main()
{
	Timer0Init();      //初始化定时器
	chaoshenbo_init(); //初始化超声波
	Delay_1ms(2000);
	while(1)
	{
	
		distence=chaoshenbo_cejv();  //获取数据要约1s
		if(distence<10)
		{
			speed=3;
			Delay_1ms(20000);
		}
		distence=chaoshenbo_cejv();  //获取数据要约1s
		if(distence>20)
		{
			speed=1;
			Delay_1ms(4000);	
		}
		
	}
}
 
void Time0_pwm() interrupt 1
{
	TL0 = 0x33;
	TH0 = 0xFE;
	time++; 
	time%=40;
	if(time < speed)
	{
		TS90A = 1;
	}
	else
	{
		TS90A = 0;
	}
}