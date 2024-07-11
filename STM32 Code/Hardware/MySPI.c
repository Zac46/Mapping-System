#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define DAC_SYNC GPIO_Pin_6
#define DAC_SCLK GPIO_Pin_0 //注意这个是GPIOB，其余是GPIOA
#define DAC_MOSI GPIO_Pin_5


//SPI通信的片选端SYNC的写操作
void MySPI_W_SYNC(uint8_t BitValue)   
{
	GPIO_WriteBit(GPIOA,DAC_SYNC,(BitAction)BitValue);
}

//SPI通信的时钟端SCLK的写操作
void MySPI_W_SCLK(uint8_t BitValue)   
{
	GPIO_WriteBit(GPIOB,DAC_SCLK,(BitAction)BitValue);
}


//SPI通信的主机输出，从机输入端的写操作
void MySPI_W_MOSI(uint8_t BitValue)   
{
	GPIO_WriteBit(GPIOA,DAC_MOSI,(BitAction)BitValue);
}

//初始化SPI端口，将SYNC，MOSI，SCLK端口全部置为高电平
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin=DAC_SYNC | DAC_MOSI;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin=DAC_SCLK;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	MySPI_W_SYNC(1);  //初始化后置引脚的默认电平
	MySPI_W_SCLK(0);
	
}

//启用片选，代表SPI通信开始
void MySPI_Start(void)
{
	MySPI_W_SYNC(0);
}

//关闭片选，SPI通信结束
void MySPI_Stop(void)
{
	MySPI_W_SYNC(1);
}

//SPI通信发送一个字节
void MySPI_SendByte(uint8_t ByteSend)
{
	uint8_t i;
	for (i=0;i<8;i++)
	{
		MySPI_W_SCLK(1);
		MySPI_W_MOSI(ByteSend & (0x80)>>i);
		MySPI_W_SCLK(0);
	}
}



//在DAC8563中的指定寄存器中写入数据
void DAC8563_Reg_Write(uint8_t cmd,uint16_t data)
{
	MySPI_Start();
	Delay_us(1);
	MySPI_SendByte(cmd);
	MySPI_SendByte((data & 0xFF00)>>8);
	MySPI_SendByte(data & 0x00FF);
	MySPI_Stop();
}

