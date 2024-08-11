#include "main.h"

unsigned char Infrared_Step=0;
unsigned int  Infrared_Time=0;
unsigned char Infrared_Num=0;
unsigned char Infrared_Code[4];
bit Infrared_Flag=0;

/****** ���������� begin ******/
void INF_Init(void)
{
	TMOD|=0x01;	//��ʱ��1 16λ�ֶ���װ
	TH0=0;	//��װֵ
	TL0=0; 	//Ϊ��������¼ʱ��
	ET0=1;	//����ʱ��1�ж�
	TR0=1;	//������ʱ��1

	IT0=1; 	//�ⲿ�ж�0�͵�ƽ����

	EX0=1;	//�ⲿ�ж�0ʹ��	
	EA=1;	
}

void Time0_isr (void) interrupt 1
{
	TH0=0;
	TL0=1;	
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
    Infrared_Time=TH0*256+TL0;   //�жϼ��ʱ��
    TH0=0; 
    TL0=0;            		//��ʱ��������������
	if (Infrared_Step==0)
	{
		if ((Infrared_Time>12000)&&(Infrared_Time<17000))  //��ʼ�� ��ȷ��һ����Χ Ȼ����αƽ�	12000 17000
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