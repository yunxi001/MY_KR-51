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
	if(P3_5==0)
	{
		delay(20);
		while(P3_5==0);
		delay(20);
		P1_0=~P1_0;
	}
	
}