/**************************************************************************************
*���ܣ�ESP8266�����ȵ㲢��������												               									*
*�ر�˵����																																						*
*         	  MCU��STC89C52     																											*
*							����11.0592MHz																													*
*���ߣ�����з�����																		  															*
*��˾������Ӳ�Ʒ���޹�˾ 																														*	
*�绰��0530-2897239   15192459227			  										  												*
*����޸�ʱ�䣺2018��1��18��																														*
***************************************************************************************/

#include "reg51.h"

unsigned char RST[]="AT+RST\r\n";//����ģ��
unsigned char LYMS[]="AT+CWMODE=1\r\n";//����WIFIģ��Ϊstationģʽ
unsigned char SZLY[]="AT+CWJAP=\"MERCURY_C1D7\",\"12345678\"\r\n";/*����WIFIģ������WIFI������������*/
unsigned char KQFU[]="AT+CIPSTART=\"TCP\",\"192.168.0.111\",8000\r\n";//���ӷ�����
unsigned char TCMS[]="AT+CIPMODE=1\r\n";//͸��ģʽ
unsigned char FSSJ[]="AT+CIPSEND\r\n";//��������	 

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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD = 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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
	Delay_Xms(1500);//�ȴ�WIFI�ϵ��ʼ��
	SendString(LYMS);//AT+CWMODE=1 ����stationģʽ��ֻ�����������ȵ�
	Delay_Xms(100);
	SendString(SZLY);//����WIFIģ������WIFI������������
	Delay_Xms(2000);//�ȴ�����WIFI�Լ���ȡIP��ַ
	SendString(KQFU);//���ӷ�����
	Delay_Xms(2000);//�ȴ����ӳɹ�
	SendString(TCMS);//����Ϊ͸��ģʽ
	Delay_Xms(100);
	SendString(FSSJ);//׼����������
	Delay_Xms(100);
}

void main()
{
	Init_Uart();
	while(1)
	{
		Online();//���߹��̵Ĵ��� ��Ҫ�������
		
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