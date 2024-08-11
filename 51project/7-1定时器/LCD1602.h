#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
void LCD_Init();  //初始化
void LCD_Delay();  
void LCD_WriteCommand(unsigned char Command);  //发送指令  0x18左移，0x1c右移 
void LCD_WriteData(unsigned char Data);   //发送数据
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);  //显示字符
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);  //显示字符串
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);  //显示无符号的数字
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);  //显示有符号的数字
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);  //显示16进制的数字
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);   //显示二进制的数字
//每行可以储存40个
#endif