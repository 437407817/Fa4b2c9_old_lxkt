
#include "./controller/TaskFun_Outer.h"
#include "./controller/TaskFun.h"

#include "./sys/bsp_systime.h"   

#include "./GV_variable.h"
#include "./screen/Screen.h"
#include "./defines.h"


#include "./converter/data_convert.h"
#include <stdlib.h>

 #include "./sys/sysio.h"

#include "./screen/ScreenDataDis.h"

#include "./service/EepromFun.h"
#include "./controller/DisStateFun.h"
#include "./communication/Comu485Dis.h"
#include "./service/DisposeDataFun.h"

#include "./test/bsp_test_485.h" 

#include "./communication/Comu485Dis.h"
#include "./screen/ScreenDataDis.h"

#include "./sys/systick.h"
#include "./controller/TaskSingleWork.h"

#include "./sensor/bsp_test_DS1302.h"
#include "./usart/usart485verify.h"




#define FE_AFTER_WAITE_ASK_DATA_TIME   360
#define OVERTIME_EACH_DATA_ASK   (FE_AFTER_WAITE_ASK_DATA_TIME+140)
//#define OVERTIME_EACH_DATA_ASK   400


//AskUploadDataovertimefun
TaskComps_t g_taskComps[] = 
{
# if 1
	
	{0, 1000,   1000,   Handle_CheckStop_CommuOverTimeFalg},
	{0, 4000, ASK_SLAVE_NOTWORK_DUTY_TIME, Handle_SendVolDataToScreenAndAskSlave},
	
	{0, 100,   100,   pull_data_from_screen},
//	{0, 0,   4000,   Handle_SendCapacityDataToScreen},
 // {0, 0,   900,   Handle_SendSDTimeDataToScreen},
	
	{0, 0,   4000,  Handle_CheckStop_ALLBoard_FinishWork},//();//监测停止条件 
//	{0, 0,   0,  Handle_ChangeCheckStop_ALLBoard_FinishWork_time},//();//监测停止条件 
	
	
	{0, 0,   OVERTIME_EACH_DATA_ASK,   AskUploadDataovertimefun},	

	//{0, 0,   99999999,   Handle_SaveSdData},	
	//{0, 0,   150,   Handle_ImmediateSaveSd},	
#endif
	
	{0, 500,   1000,   Handle_getTime},	
	{0, 1000,   1000,   SEGGER_HostDataToUsart},
	
	{0, 0,   FE_AFTER_WAITE_ASK_DATA_TIME,   Handle_SendSlaveAskdataAfter50MS},
  {0, 100,   100,   Usart485ComTask},	//100ms速度太快，写一半的时候就去读，会出错
//	{0, 1000,   1000,   Handle_FeedIWatchDog},	
		{0, 1000,   5000,   Handle_can},	

	{0, 10000,   10000,   Handle_showdata},
//  {0, 2000,   2000,   DS1302_TEST_get},
//	{0, 2000,   10000,   Handle_test},	
	/* 添加业务功能模块 */
};

//extern uint8_t calculate_TASK_NUM_MAX( void );

 uint8_t calculate_TASK_NUM_MAX(void)
{
	//Usb2ComAppInit();
	return (sizeof(g_taskComps) / sizeof(g_taskComps[0]));

}






