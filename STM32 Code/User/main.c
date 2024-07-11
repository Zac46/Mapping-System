#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DAC8563.h"
#include "MySPI.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();
	Serial_Init(); 
	DAC8563_Init();
	 
	
//----------------------------------------------------------------------

	uint16_t V1_Digital=32005;
	uint16_t V2_Digital=42518;

	//两通道的电压值设置，范围为0-65535,对应-10-+10V
	
    while(1)
	{
		if(Serial_GetRxFlag()==1)
		{
	
			if(Serial_RxPacket[0]==0x33 && Serial_RxPacket[1]==0x30)   //V1按照最慢挡位增加
			{
				V1_Digital++;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}
			
			if(Serial_RxPacket[0]==0x33 && Serial_RxPacket[1]==0x31)   //V1按照中等挡位增加
			{
				V1_Digital+=10;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}
			if(Serial_RxPacket[0]==0x33 && Serial_RxPacket[1]==0x32)   //V1按照最大挡位增加
			{
				V1_Digital+=100;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}
			if(Serial_RxPacket[0]==0x32 && Serial_RxPacket[1]==0x30)   //V1按照最慢挡位减小
			{
				V1_Digital--;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}	
		    if(Serial_RxPacket[0]==0x32 && Serial_RxPacket[1]==0x31)   //V1按照中等挡位减小
			{
				V1_Digital-=10;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}
			if(Serial_RxPacket[0]==0x32 && Serial_RxPacket[1]==0x32)   //V2按照最大挡位减小
			{
				V1_Digital-=100;
				Serial_SendByte('M');	
				Serial_SendNum(V1_Digital);	
			}
			if(Serial_RxPacket[0]==0x31 && Serial_RxPacket[1]==0x30)   //V2按照最慢挡位增加
			{
				V2_Digital++;
				Serial_SendByte('N');	
				Serial_SendNum(V2_Digital);	
			}
			if(Serial_RxPacket[0]==0x31 && Serial_RxPacket[1]==0x31)   //V2按照中等挡位增加
			{
				V2_Digital+=10;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}
			if(Serial_RxPacket[0]==0x31 && Serial_RxPacket[1]==0x32)   //V2按照最大挡位增加
			{
				V2_Digital+=100;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}
			
			if(Serial_RxPacket[0]==0x30 && Serial_RxPacket[1]==0x30)   //V2按照最慢挡位减小
			{
				V2_Digital--;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}
			
			if(Serial_RxPacket[0]==0x30 && Serial_RxPacket[1]==0x31)   //V2按照中等挡位减小
			{
				V2_Digital-=10;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}	
			if(Serial_RxPacket[0]==0x30 && Serial_RxPacket[1]==0x32)   //V2按照最大挡位减小
			{
				V2_Digital-=100;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}
			
		
			
			

			if(Serial_RxPacket[0]==0x39)   //设置V1的值
			{
				uint16_t temp=0;
				for(int i =1;i<6;i++)
				{
					temp*=10;
					temp+=(Serial_RxPacket[i]-0x30);
				}
				
				V1_Digital= temp;
				Serial_SendByte('M');
				Serial_SendNum(V1_Digital);	
				
			}
			
			if(Serial_RxPacket[0]==0x38)   //设置V2的值
			{
				uint16_t temp=0;
				for(int i =1;i<6;i++)
				{
					temp*=10;
					temp+=(Serial_RxPacket[i]-0x30);
				}
				
				V2_Digital= temp;
				Serial_SendByte('N');
				Serial_SendNum(V2_Digital);	
			}
			
			
		}
		
		DAC8563_SetVoltage_V1(V1_Digital);
		DAC8563_SetVoltage_V2(V2_Digital);	
		//OLED_Show_V1(1,1,V1_Digital);  //OLED上显示V1的设置值，注意，这个设置值很可能会和输入设置值有偏差，因为并不是所有的初始输入值都能被达到。
		//OLED_Show_V2(2,1,V2_Digital);  //OLED上显示V2的设置值
    }
	
	
}
	
	

		

	
	
	





