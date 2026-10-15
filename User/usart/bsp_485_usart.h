#ifndef __DEBUG_485_H
#define	__DEBUG_485_H

#include "stm32fxxx.h"
#include <stdio.h>
#include "./sys/bsp_systime.h"




#if (EMBED_FIRE_INTERFACE==1)
#define USART_485_A                             USART2
#define USART_485_A_CLK                         RCC_APB1Periph_USART2
#define USART_485_A_BAUDRATE                    115200

#define USART_485_A_RX_GPIO_PORT                GPIOD
#define USART_485_A_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define USART_485_A_RX_PIN                      GPIO_Pin_6
#define USART_485_A_RX_AF                       GPIO_AF_USART2
#define USART_485_A_RX_SOURCE                   GPIO_PinSource6

#define USART_485_A_TX_GPIO_PORT                GPIOD
#define USART_485_A_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define USART_485_A_TX_PIN                      GPIO_Pin_5
#define USART_485_A_TX_AF                       GPIO_AF_USART2
#define USART_485_A_TX_SOURCE                   GPIO_PinSource5

#define _485_A_RE_GPIO_PORT					   GPIOB
#define _485_A_RE_GPIO_CLK					   RCC_AHB1Periph_GPIOB
#define _485_A_RE_PIN							   GPIO_Pin_8

#define _485_A_INT_IRQ                 		   USART2_IRQn
#define _485_A_IRQHandler                        USART2_IRQHandler
#else

#define USART_485_A                             UART4
#define USART_485_A_CLK                         RCC_APB1Periph_UART4
#define USART_485_A_BAUDRATE                    9600

#define USART_485_A_RX_GPIO_PORT                GPIOC
#define USART_485_A_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define USART_485_A_RX_PIN                      GPIO_Pin_11
#define USART_485_A_RX_AF                       GPIO_AF_UART4
#define USART_485_A_RX_SOURCE                   GPIO_PinSource11

#define USART_485_A_TX_GPIO_PORT                GPIOC
#define USART_485_A_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define USART_485_A_TX_PIN                      GPIO_Pin_10
#define USART_485_A_TX_AF                       GPIO_AF_UART4
#define USART_485_A_TX_SOURCE                   GPIO_PinSource10

#define _485_A_RE_GPIO_PORT					   GPIOD
#define _485_A_RE_GPIO_CLK					   RCC_AHB1Periph_GPIOD
#define _485_A_RE_PIN							   GPIO_Pin_4

#define _485_A_INT_IRQ                 		   UART4_IRQn
#define _485_A_IRQHandler                        UART4_IRQHandler







#endif





	/// 不精确的延时

/*控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define _485_A_RX_EN()			 GPIO_ResetBits(_485_A_RE_GPIO_PORT,_485_A_RE_PIN); 
//进入发送模式,必须要有延时等待485处理完数据
#define _485_A_TX_EN()			 GPIO_SetBits(_485_A_RE_GPIO_PORT,_485_A_RE_PIN);  DelayNclock(200);//Delay(1);



void USART_485_A_Config(void);

//void _485_SendByte(  uint8_t ch );
//void _485_SendStr_length( uint8_t *str,uint32_t strlen );
//void _485_SendString(  uint8_t *str);

void bsp_485_A_IRQHandler(void);
char *get_rebuff(uint16_t *len);
void clean_rebuff(void);


/**
***********************************************************
* @brief 注册回调函数
* @param pFunc，函数指针变量，接收传入的回调函数地址
* @return 
***********************************************************
*/
void reg485ComCb(void (*pFunc)(uint8_t data));




#endif /* __USART1_H */
