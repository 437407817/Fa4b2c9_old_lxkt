#ifndef __TEST_485_H
#define	__TEST_485_H


#include "stm32f4xx.h"

void USART_485_Test(void);





void USART_485_Test1(void);


void USART_485_B_Test(void);



void p_ReturnDataToBack_485_B(uint8_t **frame,uint16_t* length);

void p_ReturnDataToBack(uint8_t **frame,uint16_t* length);














#endif /* __TEST_485_H */
