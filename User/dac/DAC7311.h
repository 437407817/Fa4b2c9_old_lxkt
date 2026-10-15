#ifndef __DAC7311_H
#define	__DAC7311_H


#include "stm32fxxx.h"




#define DAC7311_DIN_GPIO_SCLK             RCC_AHB1Periph_GPIOC
#define DAC7311_DIN_GPIO_Port            GPIOC
#define DAC7311_DIN_GPIO_Pin             GPIO_Pin_5

#define DAC7311_SCLK_GPIO_SCLK            RCC_AHB1Periph_GPIOC
#define DAC7311_SCLK_GPIO_Port           GPIOC
#define DAC7311_SCLK_GPIO_Pin            GPIO_Pin_4

#define DAC7311_SYNC_GPIO_SCLK            RCC_AHB1Periph_GPIOA
#define DAC7311_SYNC_GPIO_Port           GPIOA
#define DAC7311_SYNC_GPIO_Pin            GPIO_Pin_7

#define DAC7311_DIN_L   GPIO_ResetBits(DAC7311_DIN_GPIO_Port,DAC7311_DIN_GPIO_Pin)
#define DAC7311_DIN_H   GPIO_SetBits(DAC7311_DIN_GPIO_Port,DAC7311_DIN_GPIO_Pin)

#define DAC7311_SCLK_L   GPIO_ResetBits(DAC7311_SCLK_GPIO_Port,DAC7311_SCLK_GPIO_Pin)
#define DAC7311_SCLK_H   GPIO_SetBits(DAC7311_SCLK_GPIO_Port,DAC7311_SCLK_GPIO_Pin)

#define DAC7311_SYNC_L   GPIO_ResetBits(DAC7311_SYNC_GPIO_Port,DAC7311_SYNC_GPIO_Pin)
#define DAC7311_SYNC_H   GPIO_SetBits(DAC7311_SYNC_GPIO_Port,DAC7311_SYNC_GPIO_Pin)




void DAC7311_WriteData(uint16_t Data);

void DAC7311_Init(void);
uint32_t DAC7311_VolDispose_mv(uint16_t  DAC7311_Vbit);
void DAC7311_Test(void);

#endif /* __DAC7311_H */

