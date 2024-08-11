#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"
unsigned char KeyNum;

unsigned int j;
void main()
{
	
	Nixie(4,0);
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			Nixie(4,KeyNum);
			Buzzer_Time(100);
		}
	}
}