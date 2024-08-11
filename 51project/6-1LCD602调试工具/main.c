#include "regx52.h"
 #include "intrins.h"
/*#include "Timer0.h"
#include "uart.h" */
#include "LCD1602.h"

void Delay500ms()  //@11.0592MHz
{
 unsigned char i, j, k;

 _nop_();
 i = 4;
 j = 129;
 k = 119;
 do
 {
  do
  {
   while (--k);
  } while (--j);
 } while (--i);
}

void main()
{
  LCD_Init();
  LCD_ShowChar(1,7,'Y');
  LCD_ShowString(2,2,"Hello!Yinyuer");
  LCD_ShowNum(1,8,689,3);
  
  while(1)
  {
    
  }
}

/*void UART_Routine() interrupt 4
{
  if( RI==1 )
  {
    P1=SBUF;
    UART_SendByte(SBUF);
    
    RI = 0;
  }
}*/