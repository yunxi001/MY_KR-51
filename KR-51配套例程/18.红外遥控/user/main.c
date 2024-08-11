
/**************************************************************************************
*功能：红外解码            												  		      *
*说明：在数码管上显示解码值，前两位显示遥控器码值   后两位显示反码                    *
*硬件连接：在J6处插上跳线帽  红外接收头    -->   P3^2         						  *
*		   在J4处插上跳线帽  第一位数码管 位引脚-->P2.0								  *
*							 第二位数码管 位引脚-->P2.1								  *
*							 第三位数码管 位引脚-->P2.2								  *
*							 第四位数码管 位引脚-->P2.3								  *
*							 所有的数码管 段引脚-->P0								  *	
*作者：研发中心																		  *
*公司：科睿电子产品有限公司 														  *
*电话：0530-2897239   15192459227			  										  *
*地址：菏泽市开发区广州路与淮河路交叉口科睿电子产品有限公司 						  *
***************************************************************************************/
/*
红外遥控资源分配：
定时器0负责PWM调速
定时器1负责定时 65ms手动重装
外部中断0与定时器1配合负责红外解码
*/
#include <reg52.h>

#define Dig_Segment	P0
sbit Dig_Seat_1 = P2^0;
sbit Dig_Seat_2 = P2^1;
sbit Dig_Seat_3 = P2^2;
sbit Dig_Seat_4 = P2^3;

unsigned int  Infrared_Time=0;	//红外解码记录的时间
unsigned char Infrared_Step=0; 	//解码步骤
unsigned char Infrared_Code[4];	//存放红外编码
unsigned char Infrared_Num=0;		//记录保存了红外编码的多少位
unsigned char Infrared_Flag=0;	//解码成功标志位

				  /**0、  1、   2、  3、 4、   5、  6、 7、**/
unsigned char code table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
						  /**8、  9、  A、  B、  C、  D、  E、  F*/
                          0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
unsigned char Dig_data[4];

void delay(unsigned char i)
{
  unsigned char j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}


/****** 红外解码代码 begin ******/
void INF_Init(void)
{
	TMOD|=0x10;	//定时器1 16位手动重装
	TH1=0;	//重装值为0  因为定时计数器的数值是累加的
	TL1=0; 	//为红外解码记录时间
	ET1=1;	//开定时器1中断
	TR1=1;	//启动定时器1

	IT0=1; 	//外部中断0低电平触发

	EX0=1;	//外部中断0使能	
	EA=1;	
}

/***********************************
*函数名称：void Time1_isr (void) interrupt 3
*函数功能：定时器1中断服务程序
*参数说明：无
*返回说明：无
*其它说明：无
***********************************/
void Time1_isr (void) interrupt 3
{
	TH1=0;
	TL1=0;	//手动重装
}

/***********************************
*函数名称：void Int0_isr (void) interrupt 0
*函数功能：外部中断0中断服务程序
*参数说明：无
*返回说明：无
*其它说明：无
***********************************/
void Int0_isr (void) interrupt 0
{
    Infrared_Time=TH1*256+TL1;   //中断间隔时长
    TH1=0; 
    TL1=0;            		//定时计数器重新清零

	if (Infrared_Step==0)
	{
		if ((Infrared_Time>12000)&&(Infrared_Time<17000))  //起始码 先确定一个大范围 然后逐次逼近
		{
			Infrared_Step=1;
		}
		else
		{
			Infrared_Step=0;
		}
	}
	else if (Infrared_Step==1)
	{
		if ((Infrared_Time>1450)&&(Infrared_Time<3000))	 //红外编码为比特1 的时间
		{
			Infrared_Code[Infrared_Num/8]<<=1;
			Infrared_Code[Infrared_Num/8]|=0x01;
			Infrared_Num++;
		}
		else if((Infrared_Time>700)&&(Infrared_Time<1450))//红外编码为比特0的时间
		{
			Infrared_Code[Infrared_Num/8]<<=1;
			Infrared_Code[Infrared_Num/8]&=0xfe;
			Infrared_Num++;
		}
		
		if (Infrared_Num>=32)
		{
			Infrared_Num=0;
			Infrared_Step=0;
			if (Infrared_Code[2]==~Infrared_Code[3])
			{
				Infrared_Flag=1;
			}					
		}		
	}
	else
	{				  
		Infrared_Step=0;
	}
}
/****** 红外解码代码  end ******/
/***********************************
*函数名称：void Sys_Init(void)
*函数功能：上电初始化
*参数说明：无
*返回说明：无
*其它说明：对需要的功能进行必要的初始化
***********************************/
void Sys_Init(void)
{
	INF_Init();		//红外解码初始化
}
/***********************************
*函数名称：void Display(unsigned char Dig_data[4])
*函数功能：数码显示函数
*参数说明：Dig_data  显示的数据
*返回说明：无
*其它说明：对需要的功能进行必要的初始化
************************************/
void Display(unsigned char Dig_data[4])
{
   Dig_Segment=table[Dig_data[0]];
   Dig_Seat_1 = 0;
   delay(5);
   Dig_Seat_1 = 1;

   Dig_Segment=table[Dig_data[1]];
   Dig_Seat_2 = 0;
   delay(5);
   Dig_Seat_2 = 1;

   Dig_Segment=table[Dig_data[2]];
   Dig_Seat_3 = 0;
   delay(5);
   Dig_Seat_3 = 1;

   Dig_Segment=table[Dig_data[3]];
   Dig_Seat_4 = 0;
   delay(5);
   Dig_Seat_4 = 1;
}
/***********************************
*函数名称：void main(void)
*函数功能：主函数 
*参数说明：无
*返回说明：无
*其它说明：整个程序的入口
***********************************/
void main(void)
{
	
	Sys_Init();		//上电初始化
	
	while(1)
	{
		if (Infrared_Flag)		//成功接受到红外编码并成功解码
		{
			Infrared_Flag=0;	//清零 防止重复进入
			Dig_data[0]=Infrared_Code[2]>>4;
			Dig_data[1]=Infrared_Code[2]&0x0f;
			Dig_data[2]=Infrared_Code[3]>>4;
			Dig_data[3]=Infrared_Code[3]&0x0f;
		}
		Display(Dig_data);	
	}		
}