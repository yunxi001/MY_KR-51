#include "main.h"

sbit LED_WA=P2^0;	//����� ����λ
sbit LED_WB=P2^1;
sbit LED_WC=P2^2;
sbit LED_WD=P2^3;

code unsigned char LED_Code[17]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf}; 	//0-F ���һλ�� ����
unsigned char Display_Buff[4];			//��λ�������ʾ���� Ҫ��ʾ������
unsigned char Display_Num=0;			//Ҫ��ʾ�������λ��
unsigned char Display_Time=0;			//�������ʾ�����¼

/************�������ʾ begin ************/

/***********************************
*�������ƣ�void LED_Init(void)
*�������ܣ���ʼ�� 
*����˵������
*����˵������
*����˵������Դʹ��  ��ʱ��1 ���ڶ�̬ɨ�������
***********************************/
void LED_Init(void)
{
	
	TMOD|=0x10;	//��ʱ��1 16λ�ֶ���װ
	TH1=(65536-922)/256;	//11.0592M���� 1ms��װֵ
	TL1=(65536-922)%256; 	//Ϊ���ټ�¼ʱ��
	ET1=1;	//����ʱ��1�ж�
	TR1=0;	//������ʱ��1
//
//	EA=1;
}


void Stop_Display(void)
{
	LED_WA=1;
	LED_WB=1;
	LED_WC=1;
	LED_WD=1;
	P0=0xff;
}

/***********************************
*�������ƣ�void LED_Display(unsigned char num)
*�������ܣ��������ʾ 
*����˵����num ָ��Ҫ��ʾ��λ
*����˵������
*����˵����ÿ����ʾ��ָ��Ҫ��ʾ��λ 
***********************************/
void LED_Display(unsigned char num,unsigned char dot)
{
	switch (num)
	{
		case 0:
		{
			LED_WA=0;
			LED_WB=1;
			LED_WC=1;
			LED_WD=1;
			if (dot==0)
			{
				P0=LED_Code[Display_Buff[0]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[0]];
			}
		}break;
		case 1:
		{
			LED_WA=1;
			LED_WB=0;
			LED_WC=1;
			LED_WD=1;
			if (dot==1)
			{
				P0=LED_Code[Display_Buff[1]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[1]];
			}
		}break;
		case 2:
		{
			LED_WA=1;
			LED_WB=1;
			LED_WC=0;
			LED_WD=1;
			if (dot==2)
			{
				P0=LED_Code[Display_Buff[2]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[2]];
			}
		}break;
		case 3:
		{
			LED_WA=1;
			LED_WB=1;
			LED_WC=1;
			LED_WD=0;
			if (dot==3)
			{
				P0=LED_Code[Display_Buff[3]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[3]];
			}
		}break;
		default:break;
	}
}

/***********************************
*�������ƣ�void Time1 () interrupt 3
*�������ܣ���ʱ��1 �жϷ������ 
*����˵������
*����˵������
*����˵�������� �������ʾ
***********************************/
void Time1 () interrupt 3
{
	TH1=(65536-922)/256;	//11.0592M���� 1ms��װֵ
	TL1=(65536-922)%256; 	//Ϊ���ټ�¼ʱ��
	Display_Time++;
	if (Display_Time>=3)	//�������ʾ���
	{
		Display_Time=0;
		LED_Display(Display_Num,4);
		if (Display_Num<3)
		{
			Display_Num++;
		}	
		else
		{
			Display_Num=0;
		}
	}
}

/************�������ʾ end ************/