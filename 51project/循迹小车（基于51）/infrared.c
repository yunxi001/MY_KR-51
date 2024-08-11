#include <REGX52.H>
#include "Delay.h"


sbit  hw1=P1^7;    //左传感器
sbit  hw2=P1^6;    //右传感器
sbit  hw3=P1^5;    //中间传感器

/**
 *@brief   红外传感器发送信号，黑色为1，白色为0
    *@param   无
    *@retval  i,红外传感器发送的信号
**/

unsigned int infrared()
{
 unsigned int i;
 while(1)
 {
  Delay(1);
  if((hw1==0)&&(hw2==0)&&(hw3==1))
  {
   i=0;  //前进
  }
     if((hw1==0)&&(hw2==1))
  {
   i=1;  //右转
  }
  if((hw1==1)&&(hw2==0))
  {
   i=2;  //左转
  }
     if((hw1==1)&&(hw2==1))//不确定
  {
   i=3;  //停止
  }
  return i;
 }
}