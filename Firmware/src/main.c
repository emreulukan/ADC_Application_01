#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t ADC_Value;
float Resistor_Value;

void GPIO_Config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = 0x03;
	GPIO_InitStruct.GPIO_OType = 0x00;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = 0x00;
	GPIO_InitStruct.GPIO_Speed = 0x03;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void ADC_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div6;
	ADC_CommonInit(&ADC_CommonInitStruct);
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_8b;
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);
}

uint16_t Read_ADC(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_28Cycles);
	ADC_ContinuousModeCmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}


int main(void)
{

	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  ADC_Value = Read_ADC();
	  Resistor_Value = (10000/255)*ADC_Value;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
