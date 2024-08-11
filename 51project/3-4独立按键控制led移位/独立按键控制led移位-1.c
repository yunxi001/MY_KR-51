#include<REGX52.H>
#include<INTRINS.H>
void delay(unsigned int xms)		//@11.0592MHz
{
	while(xms)
	{
		unsigned char i, j;
		
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}	
}
void main()
{
	
	unsigned char led;
	P1=~0x01;
	while(1)
	{	if(P3_5==0)
		{
			delay(20);
			while(P3_5==0);
			delay(20);
			led++;
			if(led>=8)
				led=0;
			P1=~(0x01<<led);
		}
		if(P3_4==0)
		{
			delay(20);
			while(P3_4==0);
			delay(20);
			
			if(led==0)
				led=7;
			else
				led--;
			P1=~(0x01<<led);
		}
	}
}