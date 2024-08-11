#include <INTRINS.H>
/**
  * @brief  延时函数 延时x毫秒
  * @param  无
  * @retval 无
  */
void Delay(unsigned int xms)  //@11.0592MHz
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
