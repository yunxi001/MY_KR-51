#ifndef __MAIN_H
#define __MAIN_H

#include <reg52.h>

#include "other.h"
#include "led.h"
#include "ds18b20.h"
#include "inf.h"
#include "lcd12864.h"

sbit Key0=P3^2;
sbit Key1=P3^3;
sbit Key2=P3^4;
sbit Key3=P3^5;

sbit DQ=P2^6;	//DS18B20�뵥Ƭ�����
sbit BEEP=P2^5;

extern bit MCU_TYPE;   //��Ƭ���ͺ� =0Ϊ89C   =1Ϊ12C  Ĭ��Ϊ89C
extern bit TES_MODE;		//�Զ����� =0   �ֶ�����=1
extern unsigned char step;


#endif