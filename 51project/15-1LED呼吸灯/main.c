#include <REGX52.H>

sbit LED=P1^0;

void Delay_LED(unsigned int t)
{
	while(t--);
}
void main()
{
	unsigned char Time,i;
	while(1)
	{
		for(Time=0;Time<100;Time++)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				Delay_LED(Time);
				LED=1;
				Delay_LED(100-Time);
			}
		}
		for(Time=100;Time>0;Time--)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				Delay_LED(Time);
				LED=1;
				Delay_LED(100-Time);
			}
		}
	
	}
}