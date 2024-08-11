#ifndef __XPT2046_H__
#define __XPT2046_H__

#define XPT2046_XP_8       0x9c    //0x8c
#define XPT2046_YP_8       0xDc
#define XPT2046_VBAT_8     0xAc
#define XPT2046_AUX_8      0xEc

#define XPT2046_XP_12      0x9c    //0x8c
#define XPT2046_YP_12      0xDc
#define XPT2046_VBAT_12    0xAc
#define XPT2046_AUX_12     0xEc

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif