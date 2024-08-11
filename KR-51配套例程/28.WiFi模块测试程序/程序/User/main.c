/**************************************************************************************
*功能：ESP8266连接热点并发送数据												               									*
*特别说明：																																						*
*         	  MCU：STC89C52     																											*
*							晶振：11.0592MHz																													*
*作者：科睿研发中心																		  															*
*公司：科睿电子产品有限公司 																														*	
*电话：0530-2897239   15192459227			  										  												*
*最后修改时间：2018年1月18日																														*
***************************************************************************************/

#include "reg51.h"

unsigned char RST[]="AT+RST\r\n";//重启模块
unsigned char LYMS[]="AT+CWMODE=1\r\n";//设置WIFI模块为station模式
unsigned char SZLY[]="AT+CWJAP=\"MERCURY_C1D7\",\"12345678\"\r\n";/*设置WIFI模块连接WIFI的名称与密码*/
unsigned char KQFU[]="AT+CIPSTART=\"TCP\",\"192.168.0.111\",8000\r\n";//连接服务器
unsigned char TCMS[]="AT+CIPMODE=1\r\n";//透传模式
unsigned char FSSJ[]="AT+CIPSEND\r\n";//发送数据	 

void Delay_Xms(unsigned int x)
{	
	unsigned char i, j;

	while(x--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Init_Uart(void)
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD = 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES=1;
	EA=1;
}

void SendByte(unsigned char dat)
{
	TI=0;
	SBUF=dat;
	while(!TI);
}

void SendArry(unsigned char *p,unsigned char num)
{
	while(num--)
	{
		SendByte(*p++);
	}
}

void SendString(unsigned char *p)
{
	while(*p)
	{
		SendByte(*p++);
	}
}

void Online(void)
{
	Delay_Xms(1500);//等待WIFI上电初始化
	SendString(LYMS);//AT+CWMODE=1 设置station模式，只能连接无线热点
	Delay_Xms(100);
	SendString(SZLY);//设置WIFI模块连接WIFI的名称与密码
	Delay_Xms(2000);//等待连接WIFI以及获取IP地址
	SendString(KQFU);//连接服务器
	Delay_Xms(2000);//等待连接成功
	SendString(TCMS);//设置为透传模式
	Delay_Xms(100);
	SendString(FSSJ);//准备发送数据
	Delay_Xms(100);
}

void main()
{
	Init_Uart();
	while(1)
	{
		Online();//上线过程的代码 需要具体测试
		
		while(1)
		{	
			SendString("This is a test!");
			SendByte(0x0D);
			SendByte(0x0A);
			Delay_Xms(500);
		}
	}
}

void Uart_isr () interrupt 4
{
	if (RI)
	{
		RI=0;
	}
}