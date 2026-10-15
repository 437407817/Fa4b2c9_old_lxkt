#ifndef __BSP_RANDOM_H
#define	__BSP_RANDOM_H


#include "stm32f4xx.h"








void RNG_Random_Init(void);



void RNG_Random_Test(void);


uint8_t RNG_Random_0_9(void);
uint16_t RNG_Random_0_9999(void);


void RNG_Random_setArray(uint16_t *array,uint16_t arraycount,uint16_t min,uint16_t max);

uint16_t Simple_Random(uint16_t min,uint16_t max);
void Simple_Random_setArray(uint16_t *array,uint16_t arraycount,uint16_t min,uint16_t max);

#endif /* __BSP_RANDOM_H */
