#ifndef __OLED_IIC_H
#define	__OLED_IIC_H

#include "..\Driver\LQ_SOFTI2C.h"

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
unsigned char OLED_EN(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_CN(unsigned char x, unsigned char y, unsigned char N);
unsigned char OLED_NUM(unsigned char x, unsigned char y, double num, int i, int f, unsigned char TextSize);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif
