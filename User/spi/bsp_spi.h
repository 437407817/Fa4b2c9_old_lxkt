#ifndef __SPI_H
#define __SPI_H

#include "stm32fxxx.h"
#include <stdio.h>
#include "./TM/tm_stm32f4_spi.h"

/*命令定义-结尾*******************************/

#define Dummy_Byte                0xFF
/*SPI接口定义-开头****************************/



#if (EMBED_FIRE_INTERFACE==1)
#define      SPIx_A                        SPI5
#define      SPI_A_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define      SPI_A_CLK                     RCC_APB2Periph_SPI5


//SCK引脚    SCL

#define      SPI_A_SCK_CLK                 RCC_AHB1Periph_GPIOF   
#define      SPI_A_SCK_PORT                GPIOF   
#define      SPI_A_SCK_PIN                 GPIO_Pin_7
#define      SPI_A_SCK_PINSOURCE           GPIO_PinSource7
#define      SPI_A_SCK_AF                  GPIO_AF_SPI5

//MISO引脚

#define      SPI_A_MISO_CLK                RCC_AHB1Periph_GPIOF    
#define      SPI_A_MISO_PORT               GPIOF 
#define      SPI_A_MISO_PIN                GPIO_Pin_8
#define      SPI_A_MISO_PINSOURCE          GPIO_PinSource8
#define      SPI_A_MISO_AF                 GPIO_AF_SPI5
//MOSI引脚   SDA

#define      SPI_A_MOSI_CLK                RCC_AHB1Periph_GPIOF    
#define      SPI_A_MOSI_PORT               GPIOF 
#define      SPI_A_MOSI_PIN                GPIO_Pin_9
#define      SPI_A_MOSI_PINSOURCE          GPIO_PinSource9
#define      SPI_A_MOSI_AF                 GPIO_AF_SPI5

//CS(NSS)引脚 片选选普通GPIO即可(板子上自带flash片选)

#define      SPI_A_CS_CLK                RCC_AHB1Periph_GPIOF   
#define      SPI_A_CS_PORT               GPIOF
#define      SPI_A_CS_PIN                GPIO_Pin_6


#else

#define      SPIx_A                        SPI5
#define      SPI_A_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define      SPI_A_CLK                     RCC_APB2Periph_SPI5


//SCK引脚    SCL

#define      SPI_A_SCK_CLK                 RCC_AHB1Periph_GPIOF   
#define      SPI_A_SCK_PORT                GPIOF   
#define      SPI_A_SCK_PIN                 GPIO_Pin_7
#define      SPI_A_SCK_PINSOURCE           GPIO_PinSource7
#define      SPI_A_SCK_AF                  GPIO_AF_SPI5

//MISO引脚

#define      SPI_A_MISO_CLK                RCC_AHB1Periph_GPIOF    
#define      SPI_A_MISO_PORT               GPIOF 
#define      SPI_A_MISO_PIN                GPIO_Pin_8
#define      SPI_A_MISO_PINSOURCE          GPIO_PinSource8
#define      SPI_A_MISO_AF                 GPIO_AF_SPI5
//MOSI引脚   SDA

#define      SPI_A_MOSI_CLK                RCC_AHB1Periph_GPIOF    
#define      SPI_A_MOSI_PORT               GPIOF 
#define      SPI_A_MOSI_PIN                GPIO_Pin_9
#define      SPI_A_MOSI_PINSOURCE          GPIO_PinSource9
#define      SPI_A_MOSI_AF                 GPIO_AF_SPI5

//CS(NSS)引脚 片选选普通GPIO即可(板子上自带flash片选)

#define      SPI_A_CS_CLK                RCC_AHB1Periph_GPIOF   
#define      SPI_A_CS_PORT               GPIOF
#define      SPI_A_CS_PIN                GPIO_Pin_6



#endif












#define SPI_A_CS_LOW()      GPIO_ResetBits( SPI_A_CS_PORT, SPI_A_CS_PIN )
#define SPI_A_CS_HIGH()     GPIO_SetBits( SPI_A_CS_PORT, SPI_A_CS_PIN )




/*SPI_A接口定义-结尾****************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define DEBUG_ON         1

#define INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define DEBUG(fmt,arg...)          do{\
                                          if(DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)
void SPI_ALL_Init(void);
void SPI_A_Init(void);
uint8_t SPI_ReadByte(SPI_TypeDef* SPIx);
uint8_t SPI_SendByte(SPI_TypeDef* SPIx ,uint8_t byte);
uint16_t SPI_SendHalfWord(SPI_TypeDef* SPIx,uint16_t HalfWord);





#endif /* __SPI_H */

