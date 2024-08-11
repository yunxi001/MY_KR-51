#include <INTRINS.H>
/**
  * @brief  延时函数 延时x毫秒
  * @param  无
  * @retval 无
  */
void Delay_1ms(unsigned int xms)  //@11.0592MHz
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

void Delay_10us(unsigned int xus)		//@11.0592MHz
{
	unsigned char i;
	while(xus)
	{
		i = 2;
		while (--i);
		xus--;
	}
	
}
