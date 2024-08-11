#include <REGX52.H>
#include "Delay.h"
sbit right_RED=P1^4;
sbit left_RED=P1^5;
sbit middle_RED=P1^6;

unsigned char flag;	 //用于循迹方向的判断


int RED ()
{
	Delay(1);
    if((left_RED==1)&&(middle_RED==0))
    {
	    flag = 0;//左边检测到黑线
    }
    if((right_RED==1)&&(middle_RED==0))
    {
		  flag = 1;//右边检测到黑线
	}
    if((left_RED==0)&&(right_RED==0)&&middle_RED==1)
	{
			flag = 3; //两边都没检测到黑线而中间是黑线
	}
//	else
//	{
//		  flag = 4;
//	}
	return flag;
}
