#include "main.h"
unsigned char tflag;//�¶�������־  0��ʾ���¶ȣ�1��ʾ���¶�

void ds1820rst()   /*ds1820��λ*/
{ 
	unsigned char x=0;
	DQ = 1;          //DQ��λ
	Delay_1US(14); //��ʱ
	DQ = 0;          //DQ����
	Delay_1US(480); //��ȷ��ʱ����480us
	DQ = 1;          //����
	Delay_1US(140); 
} 

unsigned char ds1820rd()/*������*/
{ 
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{   DQ = 0; //�������ź�
	    dat>>=1;
	    DQ = 1; //�������ź�
	    if(DQ)
	    dat|=0x80;
	    Delay_1US(20);
	}
   return(dat);
}
void ds1820wr(unsigned char wdata)/*д����*/
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = wdata&0x01;
		Delay_1US(20);
		DQ = 1;
		wdata>>=1;
	}
}
unsigned int read_temp()/*��ȡ�¶�ֵ��ת��*/
{
	unsigned char a,b;
	unsigned int tvalue;
	ds1820rst();    
	ds1820wr(0xcc);//*���������к�*/
	ds1820wr(0x44);//*�����¶�ת��*/
	ds1820rst();    
	ds1820wr(0xcc);//*���������к�*/ 
	ds1820wr(0xbe);//*��ȡ�¶�*/ 
	a=ds1820rd();
	b=ds1820rd();
	tvalue=b;
	tvalue<<=8;
	tvalue=tvalue|a;
	if(tvalue<0x0fff)
	{
		tflag=0;
	}
	else
	{
		tvalue=~tvalue+1;
		tflag=1;
	}
	tvalue=tvalue*(0.0625);//�����Ҫ���¶�ֵ��ȷ��1λС������0.0625����10����
	return(tvalue);
}


/************DS18B20�¶� end ************/