#ifndef __LCD1602_H__
#define __LCD1602_H__

//�û����ú�����
void LCD_Init();  //��ʼ��
void LCD_Delay();  
void LCD_WriteCommand(unsigned char Command);  //����ָ��  0x18���ƣ�0x1c���� 
void LCD_WriteData(unsigned char Data);   //��������
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);  //��ʾ�ַ�
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);  //��ʾ�ַ���
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);  //��ʾ�޷��ŵ�����
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);  //��ʾ�з��ŵ�����
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);  //��ʾ16���Ƶ�����
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);   //��ʾ�����Ƶ�����
//ÿ�п��Դ���40��
#endif