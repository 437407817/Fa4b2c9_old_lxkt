#ifndef __SYS_INIT_ALL_H
#define	__SYS_INIT_ALL_H


#include "stm32f4xx.h"






#define NVIC_PriorityGroup_x  NVIC_PriorityGroup_2




















//..\..\Libraries\CMSIS;..\..\User;..\..\Libraries\FWlib\inc;
//..\..\FreeRTOS\include;..\..\FreeRTOS\portable\RVDS\ARM_CM3;..\..\FreeRTOS;

//..\..\User\spi\flash;..\..\SYSTEM\sys
//..\..\User\Led;..\..\User\TimBase;..\..\User\spi;																					



void Init_ALL_cfg(void);

void Need_SingleTest_Pro(void);
void Need_RepetitionTest_Pro(void);






#endif /* __SYS_INIT_ALL_H */
