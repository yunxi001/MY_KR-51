#include <REGX52.H>
#include "LCd1602.h"
#include "Delay.h"
int Result=0;
void main()
{
	LCD_Init();
	
	
	while(1)
		
	{
		Result++;
		Delay(1000);
		LCD_ShowNum(1,1,Result,3);
	}
}
//void main()
//{
//P2_0 = 0;
//P2_1 = 0;
//P2_2 = 0;	

//}
