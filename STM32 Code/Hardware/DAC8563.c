#include "stm32f10x.h"                  // Device header
#include "MySPI.h"

#define DAC_CLR GPIO_Pin_4   //A
#define DAC_LDAC GPIO_Pin_1  //B


//线性校准函数
int32_t Linear_Correct(double x1, double y1, double x2, double y2, double x)
{
	
    if (x2 == x1)
    {
        return 0;
    }
	
	double temp=(y2 - y1) * (x - x1) / (x2 - x1);
	
    return y1 + (int64_t)temp;
}


//设置AB(A对应V1，B对应V2)两通道输出的电压值
void DAC_OutAB(u16 dat_a, u16 dat_b) 
{
	MySPI_Start();
	DAC8563_Reg_Write(0x18, dat_a);
	DAC8563_Reg_Write(0x19, dat_b);
	MySPI_Stop();
}

//初始化DAC8563
void DAC8563_Init(void)    
{
	MySPI_Init();  //初始化SPI通信
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin= DAC_CLR;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin= DAC_LDAC; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA,DAC_CLR,Bit_RESET);
	GPIO_WriteBit(GPIOB,DAC_LDAC,Bit_RESET);

	DAC8563_Reg_Write(0x20,0x0003); //使能两个通道的DAC
	DAC8563_Reg_Write(0x30,0x0003); //不使能LDAC
	DAC8563_Reg_Write(0x38,0x0001); //使用内部参考电压2.5V
	DAC_OutAB(32768,32768);   //初始化两通道V1和V2，使其输出0V电压(-10V和10V的中间值)
	
}

//设置V1_OUT端口的电压
void DAC8563_SetVoltage_V1(uint16_t Voltage)
{
	MySPI_Start();
	DAC8563_Reg_Write(0x000,Voltage);
	MySPI_Stop();
}

//设置V2_OUT端口的电压
void DAC8563_SetVoltage_V2(uint16_t Voltage)
{
	MySPI_Start();
	DAC8563_Reg_Write(0x001,Voltage);
	MySPI_Stop();
}



