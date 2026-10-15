#ifndef __ADC_H
#define	__ADC_H


#include "stm32f4xx.h"


#if  0  //open DMA or close DMA exti ?开启或关闭
#define ADCx_DMA_ENABLE 




#else
#define ADCx_IT_ENABLE  0

// ADC 中断相关宏定义
#define    ADC_IRQ                       ADC_IRQn
#define    ADC_IRQHandler                ADC_IRQHandler
#endif

#if 0
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_AHB1PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_AHB1Periph_GPIOC  
#define    ADC_PORT                      GPIOA

// PC1-通道11 独立IO
#define    ADC_PIN                       GPIO_Pin_2
#define    ADC_CHANNEL                   ADC_Channel_2
#define    ADC_DMA_CHANNEL               DMA1_Channel1

#else

#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_AHB1PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_AHB1Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// PC1-通道11 独立IO
#define    ADC_PIN                       GPIO_Pin_3
#define    ADC_CHANNEL                   ADC_Channel_13
#define    ADC_DMA_CHANNEL               DMA_Channel_0
#define    ADC_DMA_STREAM                DMA2_Stream0
#define    ADC_DMA_CLK                   RCC_AHB1Periph_DMA2
// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define    ADC_DR_ADDR                   ((u32)ADC1+0x4c)

#endif





void ADCx_Init(void);
uint16_t ADC_GetValue(uint16_t ch);


#endif /* __ADC_H */

