#ifndef __SERIAL_H
#define __SERIAL_H


extern uint8_t Serial_RxPacket[];

void Serial_SendByte(uint8_t Byte);
void Serial_Init(void);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);
void Serial_SendString(char *String);
void Serial_SendNum(int32_t Num);
		
#endif
