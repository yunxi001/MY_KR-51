#include "main.h"
sfr TEST=0xA1;	//�ж���89C����12C
bit MCU_TYPE=0;   //��Ƭ���ͺ� =0Ϊ89C   =1Ϊ12C  Ĭ��Ϊ89C
bit TES_MODE=0;		//�Զ����� =0   �ֶ�����=1
unsigned char step=0;

void Mcu_type_judge()	//�ж���89C����12C
{
	if (TEST!=0xA1)
	{
		MCU_TYPE=1;
	}
	else
	{
		MCU_TYPE=0;
	}
}


void Key_test(void)
{
	unsigned char temp=1;
	while(temp)
	{
		if (Key0==0)
		{
			BEEP=0;
			while(Key0==0);	
		}
		if (Key1==0)
		{
			BEEP=0;
			while(Key1==0);	
		}
		if (Key2==0)
		{
			BEEP=0;
			while(Key2==0);	
		}
		if (Key3==0)
		{
			BEEP=0;
			while(Key3==0);	
		}
		BEEP=1;
	}
	
}


void Mode_judge()
{
	unsigned char i=1;
	Beebee_100(2);
	while (i)
	{
		if (Key1==0)	//�ֶ�
		{
			TES_MODE=1;	
			i=0;
			while(Key1==0);
		}
		if (Key2==0)
		{
			i=0;
			while(Key1==0);	
			Key_test();	
		}
		if (Key3==0) 	//�Զ�
		{
		   	TES_MODE=0;
			i=0;
			while(Key3==0);
		}
	}
}

void Liushui_test(unsigned char num)
{
	unsigned char i,j;
	unsigned char LEDdis=0;	//LED����
	for (i=0;i<num;i++)
	{
		Beebee_200(1);
		for (j=0;j<2;j++)
		{
			P1=0;
			Delay_1MS(200);
			P1=0xff;
			Delay_1MS(100);
		}
		LEDdis=0x80;
		for (j=0;j<9;j++)
		{
			P1=~LEDdis;
			LEDdis>>=1;
			Delay_1MS(150);
		}
	}
}

void LED_test(unsigned char num)
{
	unsigned char i,j;
	unsigned int  temp=0;
	temp=0;
	Display_Buff[0]=temp%10000/1000;		
	Display_Buff[1]=temp%1000/100;
	Display_Buff[2]=temp%100/10;
	Display_Buff[3]=temp%10; 
	TR1=1;
	for (i=0;i<num;i++)
	{
		Beebee_200(2);
		for (j=0;j<10;j++)
		{
			temp=j*1111;
			Display_Buff[0]=temp%10000/1000;		
			Display_Buff[1]=temp%1000/100;
			Display_Buff[2]=temp%100/10;
			Display_Buff[3]=temp%10; 
			Delay_1MS(300);
		}
	}
	Stop_Display();
	TR1=0;
}

void TEMP_test(unsigned char num)
{
	unsigned char i,j;
	unsigned int  temp=0;
	temp=0;
	Display_Buff[0]=temp%10000/1000;		
	Display_Buff[1]=temp%1000/100;
	Display_Buff[2]=temp%100/10;
	Display_Buff[3]=temp%10; 
	TR1=1;
	for (i=0;i<num;i++)
	{
		Beebee_200(3);
		for (j=0;j<10;j++)
		{
			temp=read_temp();
			if (tflag)
			{
				//�¶�Ϊ��
				Display_Buff[0]=16;
			}
			else
			{
				Display_Buff[0]=temp%10000/1000;
			}		
			Display_Buff[1]=temp%1000/100;
			Display_Buff[2]=temp%100/10;
			Display_Buff[3]=temp%10; 		//��λ ���϶�
			Delay_1MS(300);
		}
	}
	Stop_Display();
	TR1=0;
}

void INF_test()
{
	unsigned char i=5;
	unsigned char tstep=step;
	Display_Buff[0]=0;
	Display_Buff[1]=0;
	Display_Buff[2]=0;
	Display_Buff[3]=0;
	TR1=1;
	Beebee_200(4);
	while(i)
	{
		if (Infrared_Flag)
		{
			Infrared_Flag=0;
			Display_Buff[0]=Infrared_Code[2]%10000/1000;		
			Display_Buff[1]=Infrared_Code[2]%1000/100;
			Display_Buff[2]=Infrared_Code[2]%100/10;
			Display_Buff[3]=Infrared_Code[2]%10; 
			Beebee_100(1);
			i--;	
		}
		if (tstep!=step)	//������Ŀ�ı� ��ǰ�˳�
		{
			i=0;
		}
	}
	Stop_Display();
	TR1=0;
}

void LCD12864_test(unsigned char num)
{
	unsigned char i;
	unsigned char word0[]={"����ӿƼ�"};
	unsigned char word1[]={"����ӿƼ�"};
	unsigned char word2[]={"����ӿƼ�"};
	unsigned char word3[]={"����ӿƼ�"};
	unsigned char word4[]={"�������"};
	unsigned char word5[]={"Finish the test"};
	LCD_Init();
	for (i=0;i<num;i++)
	{
		Beebee_200(5);
		Dis_many(word0,0,0);
		Delay_1MS(800);
		Dis_many(word1,1,0);
		Delay_1MS(800);
		Dis_many(word2,2,0);
		Delay_1MS(800);
		Dis_many(word3,3,0);
		Delay_1MS(800);
		Clear_Dis12864();
	}
	Dis_many(word0,0,1);
	Delay_1MS(800);
	Dis_many(word4,2,2);
	Delay_1MS(800);
	Dis_many(word5,3,0);
	Delay_1MS(800);
}



void Auto_test()
{
	switch (step)
	{
//		case 0:	//��������
//		{
//		  	Key_test();
//			step=1;
//		}break;
		case 0:	//��ˮ��
		{
			Liushui_test(2);
			step=1;
		}break;
		case 1:	//�����
		{
			LED_test(2);
			step=2;
		}break;
		case 2:	//�¶ȼ�
		{
			TEMP_test(2);
			step=3;
		}break;
		case 3:	//1602
		{
			INF_test();
			//BEEP=Key0;
			step=4;
		}break;
		case 4:	//1602
		{
			LCD12864_test(2);
			step=5;
		}break;
		case 5:	//12864
		{
			Beebee_100(5);
		}break;
		default:break;
	}
}

void Manual_test()
{
	switch (step)
	{
		case 0:	//��ˮ��
		{
			Liushui_test(1);
		}break;
		case 1:	//�����
		{
			LED_test(1);
		}break;
		case 2:	//�¶ȼ�
		{
			TEMP_test(1);
		}break;
		case 3:	//1602
		{
			INF_test();
		}break;
		case 4:	//12864
		{
			LCD12864_test(1);
		}break;
		case 5:	//12864
		{
			Beebee_100(5);
		}break;
		default:break;
	}
}

void Key_Init()
{
	IT1=1; 	//�ⲿ�ж�0�͵�ƽ����

	EX1=1;	//�ⲿ�ж�0ʹ��	
	EA=1;
}

void Sys_Init()
{
	Mcu_type_judge();	//оƬ�ͺż��
	Mode_judge();		//����ģʽѡ��
	LED_Init();
	INF_Init();
	Key_Init();
}


void main()
{
	Sys_Init();
	while(1)
	{
		if (TES_MODE==0)	//�Զ�ģʽ
		{
			Auto_test();
		}
		else
		{
		   	Manual_test();
		}	
	}
}

void int1_isr () interrupt 2
{
   if (Key1==0)
   {
   		Delay_1MS(100);
		if (Key1==0)
		{
			if (step<4)
			{
				step++;
			}
			else
			{
				step=0;
			}
			while(Key1==0);
		}
   }
}