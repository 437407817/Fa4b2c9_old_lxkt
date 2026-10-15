
#ifndef __CC6902_H
#define	__CC6902_H


#include "stm32fxxx.h"


#if  0  //open DMA or close DMA exti ?开启或关闭
#define ADC_CC6902_DMA_ENABLE 
#endif

#define ADCx_IT_ENABLE  0



#if ADCx_IT_ENABLE==1
// ADC 中断相关宏定义
#define    ADC_CC6902_IRQ                       ADC_IRQn
#define    ADC_CC6902_IRQHandler                ADC_IRQHandler
#endif


#define    ADC_CC6902                           ADC1

#define    ADC_CC6902_CLK                       RCC_APB2Periph_ADC1


#define    ADC_CC6902_GPIO_CLK                  RCC_AHB1Periph_GPIOA  
#define    ADC_CC6902_PORT                      GPIOA


#define    ADC_CC6902_PIN                       GPIO_Pin_4
#define    ADC_CC6902_CHANNEL                   ADC_Channel_4
#define    ADC_CC6902_DMA_CHANNEL               DMA1_Channel1

void ADC_CC6902_Init(void);

uint16_t ADC_CC6902_GetValue(void);
int16_t ADC_CC6902_10A_calculateData(uint16_t ConvertedValue);

int16_t ADC_CC6902_XA_calculateData(uint16_t ConvertedValue,uint16_t CurrentSensitivity);
void ADC_CC6902_TEST(void);
#endif /* __CC6902_H */

