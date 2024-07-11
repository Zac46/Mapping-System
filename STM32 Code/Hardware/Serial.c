#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

uint8_t Serial_RxPacket[6];
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);//A1置低电平，充当地
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;

	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART2,Byte);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET); //直到变成RESET状态(即数据已经发出)时才执行操作
}

void Serial_SendString(char *String)
{
	uint8_t i;
	
	for(i=0;String[i]!=0;i++)
	{
		Serial_SendByte(String[i]);
	}
}

void Serial_SendNum(int32_t Num)   //通过串口发送数字(以字符串形式)
{
	int temp[20]; //假设数字位数不超过20位
	int len=0; //用于统计数字有多长
	int j=0;
	
	if (Num>=0)
	{
	
		while(Num != 0)
		{
			temp[j]=Num%10;
			len++;
			Num=Num/10; 
			j++;
		}
		
		
		
		for(int i=len-1;i>-1;i--)   //高位先行
		{
			Serial_SendByte(temp[i]+0x30);
		}
	
	}
	
	else
	{
		Num=-Num;
		while(Num != 0)
		{
			int box=Num%10;
			temp[j]=box;
			len++;
			Num=Num/10; 
			j++;
		}
			
		for(int i=len-1;i>-1;i--)
		{
			Serial_SendByte(temp[i]+'0');
		}
	}
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag ==1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

void USART2_IRQHandler(void)
{
	static uint8_t RxState=0;   //静态变量只能在本函数使用，只会初始化一次
	static uint8_t pRxPacket=0;  //用于记录已经接受了几个数据
	
	if (USART_GetITStatus(USART2,USART_IT_RXNE)== SET) //SET代表中断已经发生，即数据已经传入
	{
		uint8_t RxData = USART_ReceiveData(USART2);
		
		if(RxState==0)  //等待数据包头状态
		{
			
			if(RxData == 0x46) //即收到了'F'
			{
				RxState=1;
				pRxPacket=0;  //清零
			}
		}
		else if(RxState==1)   //接受数据内容状态
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket++;
			if(pRxPacket>=6)
			{
				RxState =2;
			}
		}
		else if(RxState==2)   //等待数据包尾状态
		{
			if(RxData == 0x45)   //即收到了'E'
			{
				RxState=0;
				Serial_RxFlag=1;   //置标志位代表已经收到一个完整数据包
			}
		}
		
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

