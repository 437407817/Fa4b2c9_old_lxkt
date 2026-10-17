#include "./controller/TaskFun.h"

//#include "./sys/bsp_systime.h"   

//#include "./GV_variable.h"
//#include "./screen/Screen.h"
//#include "./defines.h"


//#include "./converter/data_convert.h"


 #include "./sys/sysio.h"

//#include "./screen/ScreenDataDis.h"

//#include "./service/EepromFun.h"
//#include "./controller/DisStateFun.h"
//#include "./communication/Comu485Dis.h"
//#include "./service/DisposeDataFun.h"

//#include "./test/bsp_test_485.h" 

//#include "./communication/Comu485Dis.h"
//#include "./screen/ScreenDataDis.h"

//#include "./sys/systick.h"
//#include "./controller/TaskSingleWork.h"
//#include "./controller/TaskFun_Outer.h"



//typedef struct
//{
//	uint8_t run;                // 调度标志，1：调度，0：挂起
//	uint32_t timCount;          // 时间片计数值(如果初始化时为0.则不启动)
//	uint32_t timRload;          // 时间片重载值
//	void (*pTaskFuncCb)(void);  // 函数指针变量，用来保存业务功能模块函数地址
//} TaskComps_t;

extern  TaskComps_t g_taskComps[] ;
//static TaskComps_t g_taskComps[] = 
//{
//# if 1
//	{0, 1000,   1000,   Handle_CheckStop_CommuOverTimeFalg},
//	{0, 4000, 4000, Handle_SendVolDataToScreenAndAskSlave},
//	{0, 100,   100,   pull_data_from_screen},
//	{0, 0,   4000,   Handle_SendCapacityDataToScreen},
//  {0, 0,   900,   Handle_SendSDTimeDataToScreen},
//	{0, 0,   50,   Handle_SendSlaveAskdataAfter50MS},
//	{0, 1,   1,   pull_data_from_485},	
//	{0, 1000,   1000,   SEGGER_HostDataToUsart},
//	{0, 0,   99999999,   Handle_SaveSdData},	
//	
//#endif
//	{0, 2000,   10000,   Handle_test},	
//	/* 添加业务功能模块 */
//};

static uint8_t  TASK_NUM_MAX;

//#define TASK_NUM_MAX   (sizeof(g_taskComps) / sizeof(g_taskComps[0]))

 void TaskHandler(void)
{
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (g_taskComps[i].run)                  // 判断时间片标志
		{
			g_taskComps[i].run = 0;              // 标志清零
			g_taskComps[i].pTaskFuncCb();        // 执行调度业务功能模块

		}
	}
}


 void SuspendTaskHandler(void (*pc)(void))
{
	if(pc==NULL){
		
	return;
	}
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (*(g_taskComps[i].pTaskFuncCb)==*pc)                  // 判断时间片标志
		{
			g_taskComps[i].run = 0;              // 标志清零
			g_taskComps[i].timCount=0;        // 执行调度业务功能模块
			//return;
		}
	}
}
//有刷新的功能
 void ResumeTaskHandler(void (*pc)(void))
{
	if(pc==NULL){
		
	return;
	}
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (*(g_taskComps[i].pTaskFuncCb)==*pc)                  // 判断时间片标志
		{
			g_taskComps[i].run = 0;              // 标志清零
			g_taskComps[i].timCount=g_taskComps[i].timRload;        // 执行调度业务功能模块
			//return;
		}
	}
}

//不改变原来的启动运行状态
 void SetTaskHandlerTimeRload(void (*pc)(void),uint32_t rlotime)
{
	if(pc==NULL){
		
	return;
	}
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (*(g_taskComps[i].pTaskFuncCb)==*pc)                  // 判断时间片标志
		{
			g_taskComps[i].run = 0;              // 标志清零
			g_taskComps[i].timRload=rlotime;        // 执行调度业务功能模块
			//return;
		}
	}
}

//changestate=0:挂起，changestate=1:恢复，changestate=2，3，4:保持原来状态，
 void SetTaskHandlerTimeRloadAndChangeState(void (*pc)(void),uint32_t rlotime,uint8_t changestate)
{
	if(pc==NULL){
		
	return;
	}
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (*(g_taskComps[i].pTaskFuncCb)==*pc)                  // 判断时间片标志
		{
			g_taskComps[i].run = 0;              // 标志清零
			g_taskComps[i].timRload=rlotime;        // 执行调度业务功能模块
			
			if(changestate==0){
			g_taskComps[i].timCount=0;
			}else if(changestate==1){
			g_taskComps[i].timCount=g_taskComps[i].timRload;
			}else{
			
			
			}
			return;
		}
	}
}





/**
***********************************************************
* @brief 在定时器中断服务函数中被间接调用，设置时间片标记，
         需要定时器1ms产生1次中断
* @param
* @return 
***********************************************************
*/
static void TaskScheduleCb(void)
{
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (g_taskComps[i].timCount)
		{
			g_taskComps[i].timCount--;
			if (g_taskComps[i].timCount == 0)
			{
				g_taskComps[i].run = 1;
				g_taskComps[i].timCount = g_taskComps[i].timRload;
			}
		}
	}
}

 void PrintTaskHandlerState(void (*pc)(void))
{
	if(pc==NULL){
		
	return;
	}
	for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
	{
		if (*(g_taskComps[i].pTaskFuncCb)==*pc)                  // 判断时间片标志
		{
//			g_taskComps[i].run = 0;              // 标志清零
//			g_taskComps[i].timCount=0;        // 执行调度业务功能模块
			SYSTEM_INFO(" timCount=%d timRload=%d",g_taskComps[i].timCount,g_taskComps[i].timRload);

			//return;
		}
	}
}


//static void DrvInit(void)
//{
//	SystickInit();
//	LedDrvInit();
//	KeyDrvInit();
//	DelayInit();
//	Usb2ComDrvInit();
//}
 void AppTaskScheduleInit(void)
{
	//Usb2ComAppInit();
	extern uint8_t calculate_TASK_NUM_MAX( void );
	
	//TASK_NUM_MAX= (sizeof(g_taskComps) / sizeof(g_taskComps[0]));
	 TASK_NUM_MAX = calculate_TASK_NUM_MAX();
	//SYSTEM_DEBUG("TaskHandler------------%d- ",TASK_NUM_MAX);
	TaskScheduleCbReg(TaskScheduleCb);
}





volatile uint32_t g_sysRunCount=0 ;

void AppTaskCb(void){

	//uint32_t GetSysRunCount(void)
	
	if(g_sysRunCount>0){
	g_sysRunCount--;
		TaskScheduleCb();
	
	}

}






























