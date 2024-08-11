#include "main.h"

/*TS12864A-3 �˿ڶ���*/
#define LCD_data  P0             //���ݿ�
sbit LCD_RS  =  P2^0;            //�Ĵ���ѡ������ 
sbit LCD_RW  =  P2^1;            //Һ����/д����
sbit LCD_EN  =  P2^2;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P2^3;            //��/����ʽ����



/*******************************************************************/
/*                                                                 */
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
/*                                                                 */
/*******************************************************************/
void LCD_wcmd(unsigned char cmd)
{                          
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    Delay_1US(4); 
    P0 = cmd;
    Delay_1US(8);
    LCD_EN = 1;
    Delay_1US(8);
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
/*                                                                 */
/*******************************************************************/
void LCD_wdat(unsigned char dat)
{                          
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    Delay_1US(8);
    LCD_EN = 1;
    Delay_1US(8);
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void LCD_Init()
{ 

    LCD_PSB = 1;         //���ڷ�ʽ
    
    LCD_wcmd(0x34);      //����ָ�����
    Delay_1MS(5);
    LCD_wcmd(0x30);      //����ָ�����
    Delay_1MS(5);
    LCD_wcmd(0x0C);      //��ʾ�����ع��
    Delay_1MS(5);
    LCD_wcmd(0x01);      //���LCD����ʾ����
    Delay_1MS(5);
}

void Clear_Dis12864()
{
    LCD_wcmd(0x01);      //���LCD����ʾ����
    Delay_1MS(5);
}

/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(unsigned char X,unsigned char Y)
{                          
	unsigned char  pos;
	if (X==0)
	{
		X=0x80;
	}
	else if (X==1)
	{
		X=0x90;
	}
	else if (X==2)
	{
		X=0x88;
	}
	else if (X==3)
	{
		X=0x98;
	}
	pos = X+Y ;  
	LCD_wcmd(pos);     //��ʾ��ַ
}


void Dis_many(unsigned char *ttc,unsigned char x,unsigned char y)  //��ʾ�ֿ�����
{
	lcd_pos(x,y);             //������ʾλ��
	while(*ttc!= '\0')
	{
		LCD_wdat(*ttc);      //��ʾ�ַ�
		*(ttc++);
	}
}


void Dis_char(unsigned char ttc,unsigned char x,unsigned char y)  //��ʾ�ֿ�����
{
	lcd_pos(x,y);             //������ʾλ��
    LCD_wdat(ttc);      //��ʾ�ַ�
}