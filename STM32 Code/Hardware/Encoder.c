#include "stm32f10x.h"                  // Device header

int16_t Encoder1_Count;
int16_t Encoder2_Count;

void Encoder_Init(void)
{

     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
	 GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8| GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);

	 EXTI_InitTypeDef EXTI_InitStructure;
	 EXTI_InitStructure.EXTI_Line=EXTI_Line8 | EXTI_Line9 | EXTI_Line10| EXTI_Line11;
	 EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	 EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	 EXTI_Init(&EXTI_InitStructure);
	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	 NVIC_Init(&NVIC_InitStructure);
	 
	 NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	 NVIC_Init(&NVIC_InitStructure);

      
}

int16_t Encoder1_Get(void)
{
	int16_t Temp;
	Temp = Encoder1_Count;
	Encoder1_Count=0;
	return Temp;
}

int16_t Encoder2_Get(void)
{
	int16_t Temp;
	Temp = Encoder2_Count;
	Encoder2_Count=0;
	return Temp;
}




void EXTI15_10_IRQHandler(void)
{
     if(EXTI_GetITStatus(EXTI_Line11) == SET)
	 {
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10) == 0)
		 {
			 Encoder1_Count --;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line11);
	 }
	 
	 if(EXTI_GetITStatus(EXTI_Line10) == SET)
	 {
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0)
		 {
			 Encoder1_Count ++;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line10);
	 }
}



void EXTI9_5_IRQHandler(void)
{
     if(EXTI_GetITStatus(EXTI_Line8) == SET)
	 {
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) == 0)
		 {
			 Encoder2_Count --;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line8);
	 }
	  if(EXTI_GetITStatus(EXTI_Line9) == SET)
	 {
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0)
		 {
			 Encoder2_Count ++;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line9);
	 }
}



