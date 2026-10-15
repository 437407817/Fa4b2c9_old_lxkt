/**
  ******************************************************************************
  * @file    bsp_test-all.c
  * @author  fire
  * @version V1.0
  * @date    2023-05-15
  * @brief   应用函数接口
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
	
#include "./sys/bsp_systime.h"   
#include "./test/bsp_test_adc.h"   
#include "./usart/bsp_usart.h"
#include "./adc/bsp_adc.h"
//******************************


extern __IO uint16_t ADC_ConvertedValue;

void ADC_Test2(void)
	{

  float ADC_ConvertedValueLocal;  

	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/10*3.3; 
	
		printf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",
		       ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");

}




void ADC_Test(void)
	{


	
		printf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_GetValue(ADC_CHANNEL)); 


}










/*********************************************END OF FILE**********************/
