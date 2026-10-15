#include <stdint.h>
#include "stm32fxxx.h"
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h" 

#include "./sys/systick.h"


static volatile uint32_t g_sysRunTime = 0;
//uint64_t g_sysRunTime = 0;
extern volatile uint32_t g_sysRunCount ;
static void (*g_pTaskScheduleFunc)(void);          // 函数指针变量，保存任务调度的函数地址

/**
***********************************************************
* @brief 注册任务调度回调函数
* @param pFunc, 传入回调函数地址
* @return 
***********************************************************
*/
void TaskScheduleCbReg(void (*pFunc)(void))
{
	g_pTaskScheduleFunc = pFunc;
}

/**
***********************************************************
* @brief systick初始化
* @param
* @return 
***********************************************************
*/
void SystickInit(void)
{
	/*1ms 产生一次定时中断*/

  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

}

#include "./sys/sysio.h"
/**
***********************************************************
* @brief 定时中断服务函数，1ms产生一次中断
* @param
* @return 
***********************************************************
*/

#if USE_FREERTOS 
extern void xPortSysTickHandler(void);
#endif
//systick中断服务函数
void SysTick_Handler(void)
{	
	#if USE_FREERTOS
    #if (INCLUDE_xTaskGetSchedulerState  == 1 )
      if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
      {
    #endif  /* INCLUDE_xTaskGetSchedulerState */  
        xPortSysTickHandler();
    #if (INCLUDE_xTaskGetSchedulerState  == 1 )
      }
    #endif  /* INCLUDE_xTaskGetSchedulerState */
	#else
			g_sysRunTime++;

		g_sysRunCount++;
	//g_pTaskScheduleFunc();
		TimingDelay_Decrement();
	//SYSTEM_DEBUG("Han time=%llu  =%llu",g_sysRunTime++,GetSysRunTime());
	//SYSTEM_DEBUG("Han1 time=%llu  ", GetSysRunTime());
	//SYSTEM_DEBUG("Han2 time=%llu  ", g_sysRunTime);
	//printf("Han1 time=%llu  ", GetSysRunTime());
	#endif

	
	
	
}


void Calculate_StartRunTime(uint32_t* nowStarttime)
{
	*nowStarttime=g_sysRunTime;

	return ;
}

uint32_t Calculate_diffRunTime(uint32_t* nowStarttime,uint32_t* nowOvertime)
{
//	uint32_t printtime;
	*nowOvertime=g_sysRunTime;
//	printtime=*nowOvertime-(*nowStarttime);

	return *nowOvertime-(*nowStarttime);
}




/**
***********************************************************
* @brief 获取系统运行时间
* @param
* @return 以1ms为单位
***********************************************************
*/
uint32_t GetSysRunTime(void)
{
	return g_sysRunTime;
}
