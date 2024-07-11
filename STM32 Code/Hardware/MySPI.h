#ifndef __MYSPI_H
#define __MYSPI_H


void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
void DAC8563_Reg_Write(uint8_t cmd,uint16_t data);
uint8_t MySPI_R_CLR(void);

#endif
