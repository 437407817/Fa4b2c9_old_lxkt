#ifndef __IWDG_H
#define	__IWDG_H

#include "stm32f4xx.h"

enum IWatchDogType{
EM_iwd_1000ms,
EM_iwd_2000ms,
EM_iwd_4000ms,
	
};



void IWDG_Config(uint8_t prv ,uint16_t rlv);
void IWDG_Feed(void);
void IWDG_Config_nms(enum IWatchDogType iwdtime );
#endif /* __IWDG_H */

