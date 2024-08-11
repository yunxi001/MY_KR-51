
/**************************************************************************************
*���ܣ��������            												  		      *
*˵���������������ʾ����ֵ��ǰ��λ��ʾң������ֵ   ����λ��ʾ����                    *
*Ӳ�����ӣ���J6����������ñ  �������ͷ    -->   P3^2         						  *
*		   ��J4����������ñ  ��һλ����� λ����-->P2.0								  *
*							 �ڶ�λ����� λ����-->P2.1								  *
*							 ����λ����� λ����-->P2.2								  *
*							 ����λ����� λ����-->P2.3								  *
*							 ���е������ ������-->P0								  *	
*���ߣ��з�����																		  *
*��˾������Ӳ�Ʒ���޹�˾ 														  *
*�绰��0530-2897239   15192459227			  										  *
*��ַ�������п���������·�뻴��·����ڿ���Ӳ�Ʒ���޹�˾ 						  *
***************************************************************************************/
/*
����ң����Դ���䣺
��ʱ��0����PWM����
��ʱ��1����ʱ 65ms�ֶ���װ
�ⲿ�ж�0�붨ʱ��1��ϸ���������
*/
#include <reg52.h>

#define Dig_Segment	P0
sbit Dig_Seat_1 = P2^0;
sbit Dig_Seat_2 = P2^1;
sbit Dig_Seat_3 = P2^2;
sbit Dig_Seat_4 = P2^3;

unsigned int  Infrared_Time=0;	//��������¼��ʱ��
unsigned char Infrared_Step=0; 	//���벽��
unsigned char Infrared_Code[4];	//��ź������
unsigned char Infrared_Num=0;		//��¼�����˺������Ķ���λ
unsigned char Infrared_Flag=0;	//����ɹ���־λ

				  /**0��  1��   2��  3�� 4��   5��  6�� 7��**/
unsigned char code table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
						  /**8��  9��  A��  B��  C��  D��  E��  F*/
                          0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
unsigned char Dig_data[4];

void delay(unsigned char i)
{
  unsigned char j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}


/****** ���������� begin ******/
void INF_Init(void)
{
	TMOD|=0x10;	//��ʱ��1 16λ�ֶ���װ
	TH1=0;	//��װֵΪ0  ��Ϊ��ʱ����������ֵ���ۼӵ�
	TL1=0; 	//Ϊ��������¼ʱ��
	ET1=1;	//����ʱ��1�ж�
	TR1=1;	//������ʱ��1

	IT0=1; 	//�ⲿ�ж�0�͵�ƽ����

	EX0=1;	//�ⲿ�ж�0ʹ��	
	EA=1;	
}

/***********************************
*�������ƣ�void Time1_isr (void) interrupt 3
*�������ܣ���ʱ��1�жϷ������
*����˵������
*����˵������
*����˵������
***********************************/
void Time1_isr (void) interrupt 3
{
	TH1=0;
	TL1=0;	//�ֶ���װ
}

/***********************************
*�������ƣ�void Int0_isr (void) interrupt 0
*�������ܣ��ⲿ�ж�0�жϷ������
*����˵������
*����˵������
*����˵������
***********************************/
void Int0_isr (void) interrupt 0
{
    Infrared_Time=TH1*256+TL1;   //�жϼ��ʱ��
    TH1=0; 
    TL1=0;            		//��ʱ��������������

	if (Infrared_Step==0)
	{
		if ((Infrared_Time>12000)&&(Infrared_Time<17000))  //��ʼ�� ��ȷ��һ����Χ Ȼ����αƽ�
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
		if ((Infrared_Time>1450)&&(Infrared_Time<3000))	 //�������Ϊ����1 ��ʱ��
		{
			Infrared_Code[Infrared_Num/8]<<=1;
			Infrared_Code[Infrared_Num/8]|=0x01;
			Infrared_Num++;
		}
		else if((Infrared_Time>700)&&(Infrared_Time<1450))//�������Ϊ����0��ʱ��
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
/****** ����������  end ******/
/***********************************
*�������ƣ�void Sys_Init(void)
*�������ܣ��ϵ��ʼ��
*����˵������
*����˵������
*����˵��������Ҫ�Ĺ��ܽ��б�Ҫ�ĳ�ʼ��
***********************************/
void Sys_Init(void)
{
	INF_Init();		//��������ʼ��
}
/***********************************
*�������ƣ�void Display(unsigned char Dig_data[4])
*�������ܣ�������ʾ����
*����˵����Dig_data  ��ʾ������
*����˵������
*����˵��������Ҫ�Ĺ��ܽ��б�Ҫ�ĳ�ʼ��
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
*�������ƣ�void main(void)
*�������ܣ������� 
*����˵������
*����˵������
*����˵����������������
***********************************/
void main(void)
{
	
	Sys_Init();		//�ϵ��ʼ��
	
	while(1)
	{
		if (Infrared_Flag)		//�ɹ����ܵ�������벢�ɹ�����
		{
			Infrared_Flag=0;	//���� ��ֹ�ظ�����
			Dig_data[0]=Infrared_Code[2]>>4;
			Dig_data[1]=Infrared_Code[2]&0x0f;
			Dig_data[2]=Infrared_Code[3]>>4;
			Dig_data[3]=Infrared_Code[3]&0x0f;
		}
		Display(Dig_data);	
	}		
}