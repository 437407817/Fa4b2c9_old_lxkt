#ifndef __SYSTIME_H
#define	__SYSTIME_H


#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"









#if  (USE_FREERTOS ==0)

#define   Delay_Us(ms)   Delay_Us_NoTask(ms)	
#endif

#define  Delay(ms)  delay_ms(ms)


#define   Delay_Ms(ms)   delay_ms(ms)

																				
#define   delay_us(ms)   delay_us_soft(ms)	






#define  delay_ms(ms)                   do{\
                                          if(USE_FREERTOS==0){\
																						Delay_Ms_NoTask(ms);\
                                          }else{vTaskDelay(ms/portTICK_PERIOD_MS); }\
                                          }while(0)

void Delay_Ms_NoTask( __IO uint32_t ms);
void Delay_Us_NoTask( __IO uint32_t us);



//Delay_Ms_NoTask(ms);}\


void delay_us_soft(uint32_t delay_us);

void TimingDelay_Decrement(void);
void DelayNclock(__IO uint32_t nCount);
#if 0
#define   Delay_Us(ms)   Delay_Us_NoTask(ms)																					
#define   delay_us(ms)   Delay_Us_NoTask(ms)	//调用后会改变系统的时机

void Delay_Us_NoTask( __IO uint32_t us);
#endif
















#endif /* __SYSTIME_H */
