#include <REGX52.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char KeyNumber=0;
	if(P3_5==0){Delay(20);while(P3_5==0);Delay(20);KeyNumber=1;}
	if(P3_4==0){Delay(20);while(P3_4==0);Delay(20);KeyNumber=2;}
	
	return KeyNumber;
}