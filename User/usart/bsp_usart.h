#ifndef __USART_H
#define	__USART_H

#include "stm32f4xx.h"
#include <stdio.h>


#if  0   //open or close DMA RX ?开启或关闭
#define USARTx_A_RX_DMA_ENABLE 
#endif 

#if  0   //open or close DMA TX ?开启或关闭
#define USARTx_A_TX_DMA_ENABLE 
#endif 


#define USE_USARTx_A   1  //选择USART几
#if (USE_USARTx_A == 1)
#define USE_USART1_A 
#else
#if (USE_USARTx_A == 2)
#define USE_USART2_A 
#else
#if (USE_USARTx_A == 3)
#define USE_USART3_A 
#else
#if (USE_USARTx_A == 4)
#define USE_USART4_A 



#endif 
#endif 
#endif 
#endif 





#ifdef USE_USART1_A


//引脚定义
/*******************************************************/
// 串口1-USART1

#define USARTx_A                             USART1
#define USARTx_A_CLK                         RCC_APB2Periph_USART1
#define USARTx_A_APBxClkCmd                  RCC_APB2PeriphClockCmd

#define USARTx_A_BAUDRATE              115200
// USART GPIO 引脚宏定义
#define USARTx_A_GPIO_APBxClkCmd             RCC_AHB1PeriphClockCmd



#define USARTx_A_IRQHandler                  USART1_IRQHandler
#define USARTx_A_IRQ                 				USART1_IRQn




//USART

#define USARTx_A_RX_GPIO_PORT          GPIOA
#define USARTx_A_RX_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define USARTx_A_RX_PIN                GPIO_Pin_10
#define USARTx_A_RX_AF                 GPIO_AF_USART1
#define USARTx_A_RX_SOURCE             GPIO_PinSource10

#define USARTx_A_TX_GPIO_PORT          GPIOA
#define USARTx_A_TX_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define USARTx_A_TX_PIN                GPIO_Pin_9
#define USARTx_A_TX_AF                 GPIO_AF_USART1
#define USARTx_A_TX_SOURCE             GPIO_PinSource9



//DMA
#define USARTx_A_DR_BASE               (USART1_BASE+0x04)		

#define USARTx_A_DMA_CLK               RCC_AHB1Periph_DMA2	
#define USARTx_A_DMA_CHANNEL           DMA_Channel_4



//#define USARTx_A_DMA_STREAM            DMA2_Stream7




/************************************************************/
#endif 

#ifdef USE_USART2_A

//引脚定义
/*******************************************************/
#define USARTx_A                             USART2
#define USARTx_A_CLK                         RCC_APB1Periph_USART2
#define USARTx_A_APBxClkCmd                  RCC_APB1PeriphClockCmd
#define USARTx_A_BAUDRATE                    115200  //串口波特率


// USART GPIO 引脚宏定义
#define USARTx_A_GPIO_APBxClkCmd             RCC_APB2PeriphClockCmd
#define USARTx_A_RX_GPIO_PORT                GPIOA
#define USARTx_A_RX_GPIO_CLK                 RCC_APB2Periph_GPIOA
#define USARTx_A_RX_PIN                      GPIO_Pin_3


#define USARTx_A_TX_GPIO_PORT                GPIOA
#define USARTx_A_TX_GPIO_CLK                 RCC_APB2Periph_GPIOA
#define USARTx_A_TX_PIN                      GPIO_Pin_2


#define USARTx_A_IRQHandler                  USART2_IRQHandler
#define USARTx_A_IRQ                 				USART2_IRQn
/************************************************************/

#endif 



// 串口3-USART3
#ifdef USE_USART3_A

//引脚定义
/*******************************************************/
#define USARTx_A                             USART3
#define USARTx_A_CLK                         RCC_APB1Periph_USART3
#define USARTx_A_APBxClkCmd                  RCC_APB1PeriphClockCmd
#define USARTx_A_BAUDRATE                    115200  //串口波特率


// USART GPIO 引脚宏定义
#define USARTx_A_GPIO_APBxClkCmd             RCC_APB2PeriphClockCmd
#define USARTx_A_RX_GPIO_PORT                GPIOB
#define USARTx_A_RX_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define USARTx_A_RX_PIN                      GPIO_Pin_11


#define USARTx_A_TX_GPIO_PORT                GPIOB
#define USARTx_A_TX_GPIO_CLK                 RCC_APB2Periph_GPIOB
#define USARTx_A_TX_PIN                      GPIO_Pin_10


#define USARTx_A_IRQHandler                  USART3_IRQHandler
#define USARTx_A_IRQ                 				USART3_IRQn
/************************************************************/

#endif 

// 串口3-USART4  //RCT6没有该外设
#ifdef USE_USART4_A

//引脚定义
/*******************************************************/
#define USARTx_A                             USART4
#define USARTx_A_CLK                         RCC_APB1Periph_USART4
#define USARTx_A_APBxClkCmd                  RCC_APB1PeriphClockCmd
#define USARTx_A_BAUDRATE                    115200  //串口波特率


// USART GPIO 引脚宏定义
#define USARTx_A_GPIO_APBxClkCmd             RCC_APB2PeriphClockCmd
#define USARTx_A_RX_GPIO_PORT                GPIOC
#define USARTx_A_RX_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define USARTx_A_RX_PIN                      GPIO_Pin_11


#define USARTx_A_TX_GPIO_PORT                GPIOC
#define USARTx_A_TX_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define USARTx_A_TX_PIN                      GPIO_Pin_10


#define USARTx_A_IRQHandler                  USART4_IRQHandler
#define USARTx_A_IRQ                 				USART4_IRQn
/************************************************************/

#endif 




#define DEBUG_USART_DR_BASE               (USART1_BASE+0x04)		
#define RECEIVEBUFF_SIZE                  5000				//接收缓冲大小
#define DEBUG_USART_DMA_CLK               RCC_AHB1Periph_DMA2	
#define DEBUG_USART_DMA_CHANNEL           DMA_Channel_4
#define DEBUG_USART_DMA_STREAM            DMA2_Stream2











#define  RINGBUFF_LEN          (500)     
#define  RINGBUFF_OK           1     
#define  RINGBUFF_ERR          0   
void RingBuff_Init(void);
uint8_t Write_RingBuff(uint8_t data);
uint8_t Read_RingBuff(uint8_t *rData);


// 串口对应的DMA请求通道
#define  USART_TX_DMA_STREAM     DMA2_Stream7

// 串口对应的DMA请求通道
#define  USART_RX_DMA_STREAM     DMA2_Stream2

// 外设寄存器地址
#define  USART_DR_ADDRESS        (USART1_BASE+0x04)
// 一次发送的数据量
#define  SENDBUFF_SIZE            50

#define  RECEIVEBUFF_SIZE            5000



void USART_A_Config(void);
void USARTx_TX_DMA_Config(void);
void USARTx_RX_DMA_Config(void);

void USART_All_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART1_H */
