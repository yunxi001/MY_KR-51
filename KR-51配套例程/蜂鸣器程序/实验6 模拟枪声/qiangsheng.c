/*********************************************************************************

* 【声    明】： 此程序仅用于学习与参考，引用请注明版权和作者信息！
* 【函数功能】： 蜂鸣器测试-模拟枪声			   			            			    
* 【使用说明】： 短接蜂鸣器J5跳帽，按下K1按键
**********************************************************************************/

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

sbit  BEEP= P2^5;
sbit  K1  = P3^5;

uchar  H_count,L_count;

/*********************************************************/
void  main()
{	
 	P0=0;
	BEEP=1;
    TMOD=0x01; 
    TH0=0xff; 
    TL0=0xa0;
    H_count=0xff;
    L_count=0xa0;      
    EA=1;
    ET0=1; 
    
    while(1)
    {
       while(K1);
       TR0=1;
    }
}

/*********************************************************
  Time0中断函数
**********************************************************/
void Time0(void) interrupt 1 using 0
{
	BEEP=~BEEP;
	if( L_count!=0x00 )
	{
	   L_count--;
	   TH0=H_count; 
       TL0=L_count;
       return;
     }else  H_count--;
		
	if( H_count!=0xfc )
	{
	   L_count--;
	   TH0=H_count; 
       TL0=L_count;
       return;
	}
	else
     {
        H_count=0xff;
        L_count=0xa0;
        TH0=H_count;
        TL0=L_count;
        BEEP=1;
        TR0=0;
     }   
}
   
/*********************************************************/

