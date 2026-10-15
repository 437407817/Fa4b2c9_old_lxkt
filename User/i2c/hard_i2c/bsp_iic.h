#ifndef __BSP_IIC_H
#define	__BSP_IIC_H




#include "stm32fxxx.h"
#include "stdlib.h"	    

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define IIC1_OWN_ADDRESS7      0X0A   







/* STM32 I2C 快速模式 */
#define IIC1_Speed              100000



/*I2C接口*/






#ifdef STM32F10X
  #define IIC1_CLK_INIT								RCC_APB1PeriphClockCmd
#endif  //STM32F4配置
#ifdef STM32F4XX
  #define IIC1_CLK_INIT								RCC_AHB1PeriphClockCmd
#endif


#if (EMBED_FIRE_INTERFACE==1)
#define IIC1                          I2C1
#define IIC1_CLK                      RCC_APB1Periph_I2C1
#define IIC1_SCL_PIN                  GPIO_Pin_6                 
#define IIC1_SCL_GPIO_PORT            GPIOB                       
#define IIC1_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IIC1_SCL_SOURCE               GPIO_PinSource6
#define IIC1_SCL_AF                   GPIO_AF_I2C1

#define IIC1_SDA_PIN                  GPIO_Pin_7                  
#define IIC1_SDA_GPIO_PORT            GPIOB                       
#define IIC1_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IIC1_SDA_SOURCE               GPIO_PinSource7
#define IIC1_SDA_AF                   GPIO_AF_I2C1

#define IIC1_WORD_ADDR_SIZE           8





#else
#define IIC1                          I2C2
#define IIC1_CLK                      RCC_APB1Periph_I2C2
#define IIC1_SCL_PIN                  GPIO_Pin_4                 
#define IIC1_SCL_GPIO_PORT            GPIOH                       
#define IIC1_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOH
#define IIC1_SCL_SOURCE               GPIO_PinSource4
#define IIC1_SCL_AF                   GPIO_AF_I2C2

#define IIC1_SDA_PIN                  GPIO_Pin_5                  
#define IIC1_SDA_GPIO_PORT            GPIOH                       
#define IIC1_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOH
#define IIC1_SDA_SOURCE               GPIO_PinSource5
#define IIC1_SDA_AF                   GPIO_AF_I2C2

#define IIC1_WORD_ADDR_SIZE           8
//#define IIC1_WORD_ADDR_SIZE           16





#endif


  		






/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))



/*信息输出*/
#define IIC_DEBUG_ON         0

#define IIC_INFO(fmt,arg...)           printf("<<-IIC-INFO->> "fmt"\n",##arg)
#define IIC_ERROR(fmt,arg...)          printf("<<-IIC-ERROR->> "fmt"\n",##arg)
#define IIC_DEBUG(fmt,arg...)          do{\
                                          if(IIC_DEBUG_ON)\
                                          printf("<<-IIC-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

																					
																					
uint32_t I2C_START(void);
uint32_t I2C_ByteToWriteInsert(u8 WriteAddr);
uint32_t I2C_AddressToWriteInsert(u8 SlaverAddress);
void I2C_STOP(void);

void IIC_ConfigInit(void);

uint32_t I2C_ByteToWriteOver(u8 SlaverAddress, u16 InsideAddrOrCMD,u8 Data);
uint32_t I2C_BytesToWriteOver(u8 SlaverAddress, u16 InsideAddrOrCMD,u8 *pData);













#endif /* __BSP_IIC_H */


