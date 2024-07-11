#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_Show_V1(uint8_t x,uint8_t y,uint16_t V1_Digital); //x,y分别表示OLED的行数和列数
void OLED_Show_V2(uint8_t x,uint8_t y,uint16_t V2_Digital); //x,y分别表示OLED的行数和列数
void OLED_Show_VOUTA(uint8_t x,uint8_t y,uint16_t V_A_Digital);
#endif
