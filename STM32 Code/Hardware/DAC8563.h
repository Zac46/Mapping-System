#ifndef __DAC8563_H
#define __DAC8563_H

void DAC_OutAB(u16 dat_a, u16 dat_b);
void DAC8563_Init(void);
void DAC8563_SetVoltage_V1(uint16_t Voltage);
void DAC8563_SetVoltage_V2(uint16_t Voltage);
int32_t Linear_Correct(double x1, double y1, double x2, double y2, double x);


#endif
