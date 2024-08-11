#include <REGX52.H>
#include "Delay.h"

/*
概要：  返回按键键码
参数：  无
返回值：按下按键的键码
*/

unsigned char Key()
{
	unsigned char KeyNumber,a;
	if(P3_5==0){Delay(20);while(P3_5==0);Delay(20);KeyNumber=1;}
	if(P3_4==0){Delay(20);while(P3_4==0);Delay(20);KeyNumber=2;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=3;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=4;}
	a=KeyNumber;
	KeyNumber=0;
	return a;
}