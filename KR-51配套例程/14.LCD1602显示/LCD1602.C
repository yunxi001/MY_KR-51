/**************************************************************************************
*功能：LCD1602液晶显示       												  		  *
*说明：第一行显示：Crazy Electronic 第二行显示： TEL:0530-2897239					  *
         1	   ----> 	16															  *
	   -------------------------------												  *
	   - ****************			 - LCD1602引脚									  *
	   - Crazy Electronic			 - 第一行										  *
	   - TEL:0530-2897239			 - 第二行										  *
	   -------------------------------												  *
*注意：液晶屏过暗或过亮，请调节R6电位器												  *
*硬件连接：		LCD1602  RS		 -->P2.0											  *
*						 RW		 -->P2.1						  					  *
*						 E		 -->P2.2						  					  *
*						 D0--D7  -->P0	 							                  *
*							 								                          *
*作者：研发中心																		  *
*公司：科睿电子产品有限公司 														  *
*电话：0530-2897239   15192459227			  										  *
*地址：菏泽市开发区广州路与淮河路交叉口科睿电子产品有限公司 						  *
***************************************************************************************/
#include "reg52.h"
#define uchar unsigned char 
#define uint unsigned int
#define LCD1602_PORT P0
#define Timer0Value 50000

sbit K1=P1^4;
sbit K2=P1^5;

sbit J1=P1^0;
sbit J2=P1^1;
sbit J3=P1^2;
sbit Y1=P1^6;
sbit Y2=P1^7;
sbit Y3=P3^0;
sbit beep=P2^4;


//uchar Q_j=1;
uchar J_value=0;
uchar Y_value=0;
//uchar RestartFlag=1;
uint check_Win=0;

char counter24=0;
char hour=0;
char second=0;
char min=0,num=0;

sbit rs=P2^6;//H数据，L命令
sbit lcden=P2^7;//高脉冲使能，使能脉宽最小150ns
sbit rw=P2^5;

uchar code table1[]= "12:00  SEC-1  24";
uchar code table[]="Ta: 000:000 :Tb ";
/********************************************************************
* 名称 : delay(uchar x)
* 功能 : 延时函数
* 输入 : x 
* 输出 : 无
***********************************************************************/
void delay(uchar x)
{	uint y;
	for(;x>0;x--)
	 {									 
		for(y=70;y>0;y--)
				{};
	 }
}
/********************************************************************
* 名称 : lcdwrcom(uchar cdat)
* 功能 : LCD1602写数据到LCD1602
* 输入 : cdat 
* 输出 : 无
***********************************************************************/
void lcdwrdata(uchar dat)
{
   // dat = ((dat&0x01)<<7)|((dat&0x02)<<5)|((dat&0x04)<<3)|((dat&0x08)<<1)|((dat&0x10)>>1)|((dat&0x20)>>3)|((dat&0x40)>>5)|((dat&0x80)>>7);
	rs=1;//写数据时RS拉高
	lcden=1;
	P0=dat;
	delay(6);
	lcden=0;
	delay(6);
}
/********************************************************************
* 名称 : lcdwrcom(uchar cdat)
* 功能 : LCD1602写命令到LCD1602
* 输入 : cdat 
* 输出 : 无
***********************************************************************/
void lcdwrcom(uchar cdat)//写指令数据到LCD  
{	
   // cdat = ((cdat&0x01)<<7)|((cdat&0x02)<<5)|((cdat&0x04)<<3)|((cdat&0x08)<<1)|((cdat&0x10)>>1)|((cdat&0x20)>>3)|((cdat&0x40)>>5)|((cdat&0x80)>>7);
    rs=0;//写指令时RS拉低
	lcden=1;
    P0=cdat;//
	delay(6);//不加此延时将导致不能写入指令，但能写入显示数据
	lcden=0;
	delay(6);
}
/********************************************************************
* 名称 : lcd_init()
* 功能 : LCD1602初始化
* 输入 : 无
* 输出 : 无
***********************************************************************/
void lcd_init()
{
	uchar n;
	hour=0;
	TMOD=0x11;
	TL1=0x00;
	TH1=0x4c;
	
	TL0=(65536-Timer0Value)%256;
	TH0=(65536-Timer0Value)/256;
	ET0=1;
	PT0=1;
	TR0=0;
	PX0=1;
	EA=1;
	ET1=1;
	TR1=0;
	EX1=1;
	IT0=1;
	IT1=1;
	lcden=0;
	//beep=1;
	second=0;
	min=12;
	num=1;
	counter24=24;
	lcdwrcom(0x38);//0x38设置显示模式为：16X2 显示,5X7 点阵,8 位数据接口
	lcdwrcom(0x0c);//打开显示光标闪烁
	lcdwrcom(0x06);//
	lcdwrcom(0x01);//
	
	lcdwrcom(0x00|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table[n]);
		delay(100);
	}
  
	lcdwrcom(0x40|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table1[n]);
		delay(100);
	}
}
/********************************************************************
* 名称 : main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
//

void delay_ms(uint value)
{
uint x=0,y=0;
	for(x=value;x>0;x--)
	for(y=118;y>0;y--);
}

void write_com(uchar command)
{
  rs=0;
	LCD1602_PORT=command;
	delay_ms(5);
	lcden=1;
	delay_ms(5);
	lcden=0;
}
void write_date(uchar dat)
{
  rs=1;
	LCD1602_PORT=dat;
	delay_ms(5);
	lcden=1;
	delay_ms(5);
	lcden=0;
}

void Counter24_Down(void)
{
	uchar i;

	
	if(hour==20)  //every 1s daojishi zuo -1 caozuo
	{
	
		second--;
		counter24--;
		write_com(0x80+0x4e);  //24s daojishi xianshi
		write_date(0x30+counter24/10);
		write_date(0x30+counter24%10);
		write_com(0x80+0x4e);
		if(counter24==0)  //24s end fachu 3s lianxu baojing
		{
			beep=0;
			delay_ms(1000);
			beep=1;
			counter24=24;
		}
		if((second==0) && (min==0))  //jiance yijie compete shifou end
		{
			TR1=0;   //dingshiqi 1 stop
			write_com(0x80+0x44);
			write_date(0x30);
			num++;
			counter24=24;  //24s jishi fuwei
			write_com(0x80+0x4e); //24s daojishi xianshi
			write_date(0x30+counter24/10);
			write_date(0x30+counter24%10);
			write_com(0x80+0x4e);
			if(num<5)  //meijie end fengmingqi fachu 8s de jianduan baojing
			{
				for(i=80;i>0;i--)
				{
					beep=0;
					delay_ms(500);
					beep=1;
					delay_ms(500);
				}
			}
			if(num==5)  //chongchang end,fengmingqi fachu 10s de lianxujingbao
			{
				beep=0;
				delay_ms(10000);
				num=1;
			}
			beep=1;  //fengmingqi close
			write_com(0x80+0x4b); //gengxin"SEC-?"
			write_date(0x30+num);
			write_com(0x80+0x4b);
			second=0;   //daojishi fuwei
			min=12;
		}
		
	if(second==-1)
		{
			second=59; 
			min--;
		}
		write_com(0x80+0x43);
		write_date(0x30+second/10);
		write_date(0x30+second%10);
		write_com(0x80+0x43);
		
		write_com(0x80+0x40);  //gengxin daojishi xianshi
		write_date(0x30+min/10);
		write_date(0x30+min%10);
		write_com(0x80+0x40);
			hour=0;
	}
}


void Timer0(void) interrupt 1
{
check_Win++; //50*200=10s
	TL0=(65536-Timer0Value)%256;
	TH0=(65536-Timer0Value)/256;
	write_com(0x80+0x40);
	write_date(0x30+check_Win/1000);
	write_date(0x30+(check_Win%1000)/100);
	write_date(0x30+(check_Win%100)/10);
	write_date(0x30+check_Win%10);
	write_com(0x80+0x40);
}

void INT1_Handler(void) interrupt 2 //24s daojishi reagain
{
	uchar RestartFlag=1;
	if(K1==0)
	{
		if(RestartFlag==1)
		{
			RestartFlag=0;
			lcd_init();
		}
		EX0=1;
		TR1=~TR1;  //dingshiqi 1 work or stop
		if(TR1==1)  //when the dingshiqi working,The s1 can stop the dingshiqi working
		{
			PT1=0;
		}
		else //When daojishi cannot working,The s1 can work quickly
		{
			PT1=1;
		}			
		if(K1==0) // songshoujiance
		{
			while(K1==0);
			Counter24_Down();
		}
	}
	else if(K2==0)
	{
		counter24=24;
		write_com(0x80+0x4e); //24s daojishi xianshi
		write_date(0x30+counter24/10);
		write_date(0x30+counter24%10);
		write_com(0x80+0x4e);
		if(K2==0)  //songshou jiance
		{
			while(K2==0)
			{
				Counter24_Down();
			}
			delay_ms(20);
		}
	}
	else;
}



//dingshiqi 1 zhongduan zihanshu
void Timer1(void) interrupt 3 //dingshiqi 1 zhongduan 20 ci wei 1s
{
	hour++;
	TL1=0x00;
	TH1=0X4C;
	Counter24_Down();  //daojishi
}	

//compete daojishi / 24s daojishi


//


void Renew_Point(uchar add,uchar dat)
{
  write_com(0x80+add);
	write_date(0x30+dat/100);
  write_date(0x30+(dat%100)/10);
	write_date(0x30+dat%10);
	write_com(0x80+add);	
}

//void Renew_Pointl(uchar add,uchar dat)
//{
  //write_com(0x80+add);
	//write_date(0x30+dat%10);
	//write_com(0x80+add);
//}

void Button_Scan(void)
{
if(J1==0)
{
while(J1==0);
	J_value++;
	Renew_Point(0x04,J_value);
	if(J1==0)
	{
	while(J1==0);
		delay_ms(20);
	}
}
else if(J2==0)
{
while(J2==0);
	J_value=J_value+2;
	Renew_Point(0x04,J_value);
	if(J2==0)
	{
	while(J2==0);
		delay_ms(20);
	}
}
else if(J3==0)
{
while(J3==0);
	J_value++;
	Renew_Point(0x04,J_value);
	if(J3==0)
	{
	while(J3==0);
		delay_ms(20);
	}
}
else if(Y1==0)
{
while(Y1==0);
	J_value++;
	Renew_Point(0x08,J_value);
	if(Y1==0)
	{
	while(Y1==0);
		delay_ms(20);
	}
}
else if(Y2==0)
{
while(Y2==0);
	J_value=J_value+2;
	Renew_Point(0x08,J_value);
	if(Y2==0)
	{
	while(Y2==0);
		delay_ms(20);
	}
}
else if(Y3==0)
{
while(Y3==0);
	Y_value=Y_value+3;
	Renew_Point(0x08,Y_value);
	if(Y3==0)
	{
	while(Y3==0);
		delay_ms(20);
	}
}
 
//else 
	//if(Q_jie==0)
 //{
 //while(Q_jie==0);
	// Q_j++;
	 //Renew_Pointl(0x0F,Q_j);
	 //if(Q_jie==0)
	 //{
	 //while(Q_jie==0);
		 //delay_ms(20);
	 //}
 //}
}

void main()
{
    rw=0;
	delay(200);
	lcden=0;
	lcd_init();
/****************************	
	lcdwr_com(0x00|0x80)
 //write_com(0x00+0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table[n]);
		delay(100);
	}
  
	lcdwrcom(0x40|0x80);
	//write_com(0x40+0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table1[n]);
		//write_date(table1[n]);
		delay(100);
	}
***********/
	while(1)
	{
    //delay(100);
		Button_Scan();
	}
}
