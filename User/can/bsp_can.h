#ifndef __CAN_H
#define	__CAN_H

#include "stm32f4xx.h"
#include "./usart/bsp_usart.h"





//===================== 【配置区，只在这里修改】=====================
#define CAN_SELECT_1        1       // 1=CAN1，0=CAN2

// 波特率选择，取消注释其中一个，其余注释
//#define CAN_BAUD_CFG     CAN_BAUD_1M
#define CAN_BAUD_CFG     CAN_BAUD_500K
//#define CAN_BAUD_CFG     CAN_BAUD_250K
//#define CAN_BAUD_CFG     CAN_BAUD_125K
//===================================================================



//波特率选项定义
#define CAN_BAUD_1M         0
#define CAN_BAUD_500K       1
#define CAN_BAUD_250K       2
#define CAN_BAUD_125K       3

#define CAN_SEND_ID_1       0x18000001
#define CAN_SEND_ID_2       0x18000002
#define CAN_SEND_ID_3       0x18000003
#define CAN_SEND_ID_4       0x18000004

#define CAN_SEND_ID_RETURN_1       0x18000012
#define CAN_GET_ID_1       0x18000011




#if CAN_SELECT_1
#define CANx                    CAN1
#define CANx_RX_IRQn            CAN1_RX0_IRQn
#define CANx_IT_FMPx            CAN_IT_FMP0

#define CAN_RX_GPIO_PORT        GPIOA
#define CAN_TX_GPIO_PORT        GPIOA
#define CAN_RX_GPIO_RCC         RCC_AHB1Periph_GPIOA
#define CAN_TX_GPIO_RCC         RCC_AHB1Periph_GPIOA
#define CAN_RX_PIN              GPIO_Pin_11
#define CAN_TX_PIN              GPIO_Pin_12
#define CAN_RX_PIN_SOURCE       GPIO_PinSource11
#define CAN_TX_PIN_SOURCE       GPIO_PinSource12
#define CAN_AF_NUM              GPIO_AF_CAN1
#define CANx_RX0_IRQHandler		CAN1_RX0_IRQHandler
#define RCC_APBxPeriph_CANx		RCC_APB1Periph_CAN1
#else
#define CANx                    CAN2
#define CANx_RX_IRQn            CAN2_RX0_IRQn
#define CANx_IT_FMPx            CAN_IT_FMP0

#define CAN_RX_GPIO_PORT        GPIOB
#define CAN_TX_GPIO_PORT        GPIOB
#define CAN_RX_GPIO_RCC         RCC_AHB1Periph_GPIOB
#define CAN_TX_GPIO_RCC         RCC_AHB1Periph_GPIOB
#define CAN_RX_PIN              GPIO_Pin_5
#define CAN_TX_PIN              GPIO_Pin_6
#define CAN_RX_PIN_SOURCE       GPIO_PinSource5
#define CAN_TX_PIN_SOURCE       GPIO_PinSource6
#define CAN_AF_NUM              GPIO_AF_CAN2
#define CANx_RX0_IRQHandler		CAN2_RX0_IRQHandler
#define RCC_APBxPeriph_CANx		RCC_APB1Periph_CAN2
#endif

//过滤器模式
typedef enum
{
    CAN_FILTER_MASK_MODE = 0,
    CAN_FILTER_LIST_MODE = 1
}CAN_Filter_Mode_t;

typedef struct
{
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t  IDE;
    uint8_t  RTR;
    uint8_t  DLC;
    uint8_t  Data[8];
}CAN_RxMsg_t;

#define CAN_RX_FIFO_DEPTH  16
typedef struct
{
    CAN_RxMsg_t buf[CAN_RX_FIFO_DEPTH];
    uint8_t wr_ptr;
    uint8_t rd_ptr;
    uint8_t count;
}CAN_RxFifo_t;



// CAN接收回调函数指针
// 参数：data:接收数据缓冲区，len：DLC数据长度
typedef void (*CAN_RxCallbackFunc)(uint8_t *data, uint8_t len);
// 注册回调的函数
void CAN_SetRxGetId1Callback(CAN_RxCallbackFunc cb);





extern CAN_RxFifo_t g_canRxFifo;

void CAN_GPIO_Init(void);
void CANx_Mode_Init(void);   //不再传参，波特率由头文件宏配置

uint8_t CANx_SetFilterBank(uint8_t bankNum, CAN_Filter_Mode_t filterMode,
                           uint32_t id1, uint32_t id2, uint32_t mask);

uint8_t CANx_SendExtFrame(uint32_t extId, uint8_t *pBuf, uint8_t len);
uint8_t CANx_SendExtRemoteFrame(uint32_t extId, uint8_t reqDlc);

uint8_t CANx_RxFifo_Push(CAN_RxMsg_t *msg);
uint8_t CANx_RxFifo_Pop(CAN_RxMsg_t *msg);
uint8_t CANx_RxFifo_IsEmpty(void);

uint16_t CANx_SendExtFrame_StructSplit(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen);

void CANx_config_Init(void);

uint16_t CANx_SendExtFrame_StructSplit(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen);


void CANx_IT_DataDispose(void);

#endif







