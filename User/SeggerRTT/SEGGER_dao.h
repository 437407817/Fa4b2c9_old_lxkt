#ifndef __SEGGER_DAO_H
#define	__SEGGER_DAO_H


#include "stm32fxxx.h"


//void SEGGER_PcDao_McuToCanTransform(CAN_TypeDef* CANx,uint8_t *array, uint16_t num);



void SEGGER_PcDao_UsartToMcuTransform(USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void SEGGER_PcDao_McuToUsartTransform(USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);


#endif /* __SEGGER_DAO_H */

