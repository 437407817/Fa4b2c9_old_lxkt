#ifndef __ADS7822_H
#define	__ADS7822_H


#include "stm32fxxx.h"




#define ADS7822_CS_GPIO_Clk             RCC_AHB1Periph_GPIOH
#define ADS7822_CS_GPIO_Port            GPIOH
#define ADS7822_CS_GPIO_Pin             GPIO_Pin_6

#define ADS7822_CLK_GPIO_Clk            RCC_AHB1Periph_GPIOH
#define ADS7822_CLK_GPIO_Port           GPIOH
#define ADS7822_CLK_GPIO_Pin            GPIO_Pin_7

#define ADS7822_OUT_GPIO_Clk            RCC_AHB1Periph_GPIOH
#define ADS7822_OUT_GPIO_Port           GPIOH
#define ADS7822_OUT_GPIO_Pin            GPIO_Pin_9

#define ADS7822_CS_L   GPIO_ResetBits(ADS7822_CS_GPIO_Port,ADS7822_CS_GPIO_Pin)
#define ADS7822_CS_H   GPIO_SetBits(ADS7822_CS_GPIO_Port,ADS7822_CS_GPIO_Pin)

#define ADS7822_SCK_L   GPIO_ResetBits(ADS7822_CLK_GPIO_Port,ADS7822_CLK_GPIO_Pin)
#define ADS7822_SCK_H   GPIO_SetBits(ADS7822_CLK_GPIO_Port,ADS7822_CLK_GPIO_Pin)

#define ADS7822_READBIT  GPIO_ReadInputDataBit(ADS7822_OUT_GPIO_Port,ADS7822_OUT_GPIO_Pin)

uint16_t ADS7822_CatchVolBit(void);
void ADS7822_Init(void);
uint16_t ADS7822_CatchVol(void);
uint32_t ADS7822_VolDispose(uint16_t  ADS7822_VAL);
void ADS7822_Test(void);
#endif /* __ADC_H */

