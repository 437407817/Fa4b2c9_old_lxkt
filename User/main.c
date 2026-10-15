/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   读写SDRAM
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./sdram/bsp_sdram.h"
//#include "./malloc/malloc.h"
#include <stdlib.h>
#include "./sys/bsp_systime.h" 

#include "./sys/sys_init_all.h" 



#include "freerotspro.h" 
#include "FreeRTOSConfig.h" 
#include "./GV_variable.h"


#include "./sys/sysio.h"

#include "./sys/systick.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

  
	 #if 0
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
	#endif
//	
	  Init_ALL_cfg();
//	
	Need_SingleTest_Pro();
	
	#if USE_FREERTOS 
	FreerTosProBegin();
#endif
	
  while(1){
	
	Need_RepetitionTest_Pro();
		//Delay(1);  //非常重要，必须要有，否则启动后卡死
	//DelayNclock(100);
	//SYSTEM_DEBUG("1s time=%llu",GetSysRunTime());
	};
	

}


/*********************************************END OF FILE**********************/

