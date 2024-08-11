#include <REGX52.H>
#include "Delay.h"

sbit Buzzer=P2^5;

void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	while(i<100)
			{
				Buzzer=!Buzzer;
				Delay(1);
				i++;
			}
			i=0;
}
