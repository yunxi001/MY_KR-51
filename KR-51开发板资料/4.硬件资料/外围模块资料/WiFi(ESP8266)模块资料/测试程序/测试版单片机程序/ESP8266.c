/**************************************************************************************
*���ܣ�Wifiģ����� 											                      *
*˵�����ֻ���װ����APP���ֻ�����WiFiģ�飬���ƿ������ϵ�LED��������					  *
*Ӳ�����ӣ���J10����������ñ  1,3�����߶�· 2,4�����߶�·							  *
*���ߣ��з�����																		  *
*��˾������Ӳ�Ʒ���޹�˾ 														  *
*�绰��0530-2897239   15192459227			  										  *
*��ַ�������п���������·�뻴��·����ڿ���Ӳ�Ʒ���޹�˾ 						  *
***************************************************************************************/
#include <REGX52.H>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;
/**��������ʹ��**/
#define	RX1_Lenth		32			//���ڽ��ջ��峤��

uchar	idata RX1_Buffer[RX1_Lenth];	//���ջ���
uchar	TX1_Cnt;	//���ͼ���
uchar	RX1_Cnt;	//���ռ���
bit		B_TX1_Busy;	//����æ��־

/*************	�˿����Ŷ���	**************/
sbit LED1=P1^0;//LED1
sbit LED2=P1^1;//LED2
sbit LED3=P1^2;//LED3
sbit DK1=P1^3;//�̵���
sbit BEEP=P2^5;//������	

/**wifiģ������**/
unsigned char LYMS[13]="AT+CWMODE=2\r\n";
unsigned char SZLY[38]="AT+CWSAP='ESP8266','0123456789',11,0\r\n";
unsigned char RST[8]="AT+RST\r\n";
unsigned char SZDLJ[13]="AT+CIPMUX=1\r\n";
unsigned char KQFU[21]="AT+CIPSERVER=1,5000\r\n";
unsigned char FSSJ[13]="AT+CIPSEND=\r\n";//AT+CIPSEND= ��������	 


void Delay2(unsigned long cnt)
{
	long i;
 	for(i=0;i<cnt*100;i++);
}
void Delay3(unsigned int N) 
{
	int i;
	for(i=0;i<N*10;i++);
}



/********************************************************************
* ���� : Uart_Init()
* ���� : ���ڳ�ʼ��������11.0592,������9600��ʹ���˴����ж�
* ���� : ��
* ��� : ��
***********************************************************************/
void Uart_Init(void)
{
     TMOD = 0x20;   //��ʱ�������ڶ�ʱ��1�ķ�ʽ2
     PCON = 0x00;   //����Ƶ
     SCON = 0x50;	//���ڹ����ڷ�ʽ1�������������н���	
     TH1 = 0xFd;    //���ò����� 9600
     TL1 = 0xFd;
     TR1 = 1;		//������ʱ��1
	 ES = 1;		//�������ж�
	 EA = 1;		//�����ж�
	 RX1_Cnt=0;		//���ܼ�������
	 TX1_Cnt = 0;	//���ͼ�������
	 B_TX1_Busy = 0;//��ʼ����æ��־λ		
}
/********************************************************************
* ���� : Main()
* ���� : ������
* ���� : ��
* ��� : ��
***********************************************************************/
void main(void)
{
	char i=0;

	Uart_Init();

	Delay3(2000);
  /******************����WiFiģ��**********************************************/
	for(i=0;i<13;i++)//AT+CWMODE=2 ���ó�·��ģʽ
	{
		SBUF=LYMS[i];Delay3(5);
	}
	Delay3(1000);
	for(i=0;i<38;i++)//AT+CWSAP="ESP8266","0123456789",11,0 ����·��
	{
		SBUF=SZLY[i];Delay3(5);
	}
	Delay3(3000);
	for(i=0;i<8;i++)//AT+RST ����
	{
		SBUF=RST[i];Delay3(5);
	}
	Delay3(5000);
	for(i=0;i<13;i++)//AT+CIPMUX=1 ���óɶ�����
	{
		SBUF=SZDLJ[i];Delay3(5);
	}
	Delay3(2000);
	for(i=0;i<21;i++)//AT+CIPSERVER=1,5000 ����TCP����˿�
	{
		SBUF=KQFU[i];Delay3(5);
	}
	Delay3(2000);
	while (1)
	{
	
	}
}

/********************************************************************
* ���� : Uart_Int()
* ���� : �����ж��Ӻ���
* ���� : ��
* ��� : ��
***********************************************************************/
void UART1_int (void) interrupt 4
{
//	char i,a,b,c;
	if(RI)
	{
		RI = 0;
		RX1_Buffer[RX1_Cnt] = SBUF;		//����һ���ֽ�
		if(RX1_Buffer[0]==0x45)
		{
			RX1_Cnt++;
		}
		else
		{
			RX1_Cnt=0;
		}
		if(RX1_Cnt>=10)
		{
			if(RX1_Buffer[0]==0x45&&RX1_Buffer[1]==0x53&&RX1_Buffer[2]==0x50)
			{
				if(RX1_Buffer[4]==0x4C&&RX1_Buffer[5]==0x45&&RX1_Buffer[6]==0x44)//�ж�LED
				{
					if(RX1_Buffer[7]==0x31)//�ж�LED1
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED1=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED1=1;
						}
					}
					if(RX1_Buffer[7]==0x32)//�ж�LED2
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED2=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED2=1;
						}
					}
					if(RX1_Buffer[7]==0x33)//�ж�LED3
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							LED3=0;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							LED3=1;
						}
					}
				}
				if(RX1_Buffer[4]==0x4A&&RX1_Buffer[5]==0x44&&RX1_Buffer[6]==0x51)//�жϼ̵���
				{
					if(RX1_Buffer[7]==0x31)//�ж�LED1
					{
						if(RX1_Buffer[3]==0x4B)//�жϿ�
						{
							DK1=1;
						}
						if(RX1_Buffer[3]==0x47)//�жϹ�
						{
							DK1=0;
						}
					}
				}
				if(RX1_Buffer[3]==0x46&&RX1_Buffer[4]==0x4D&&RX1_Buffer[5]==0x51&&RX1_Buffer[6]==0x43&&RX1_Buffer[7]==0x53)//�жϷ�����
				{
					BEEP=1;Delay2(100);BEEP=0;Delay2(100);BEEP=1;Delay2(100);BEEP=0;Delay2(100);
				}
				RX1_Cnt=0;
			}
			else
			{
				RX1_Cnt=0;
			}
			RX1_Cnt=0;
		}
	}
	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;		//�������æ��־
	}
}

