

#include "./controller/TaskSingleWork.h"


#include "./sys/bsp_systime.h"   

#include "./GV_variable.h" 


#include "./screen/Screen.h"
#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./converter/data_convert.h"
#include <stdlib.h>

 #include "./sys/sysio.h"
#include "string.h"
#include "./screen/ScreenDataDis.h"
#include "./controller/DisStateFun.h"
#include "./communication/Comu485Dis.h"

#include "./service/CapacityFun.h"

#include "./usart/bsp_usart_sd.h"

#include "./communication/SD_485Dis.h"
#include "./communication/Comu485DataFun.h"

#include "./controller/TaskFun.h"
#include "./sys/systick.h"
#include "./communication/SD_485DataFun.h"
#include "./iwdg/bsp_iwdg.h"   
#include "./screen/ScreenDS1302.h"   

#include "./controller/StateFun.h"
#include "./Converter/data_compare.h"
#include "./service/StopMechineFun.h"
#include "./service/StandbyMechineFun.h"
#include "./service/StartMechineFun.h"


#define COMMUNICATION_OVERTIME  30
extern str_ComuBoardState GV_ComuBoardState;


extern str_HardwareState GV_HardwareState; 
extern str_CommSendToSlaveBoardState GV_CommSendToSlaveBoardState;

extern ScreenCommu_Item_t  GV_ScreenCommu;
extern str_ScreenSetRunState GV_ScreenSetRunBoardState;

extern uint16_t Array_ErrorType_OverTime[4];
extern uint16_t Array_ErrorType_OverTime_English[ETE_Size];
extern uint16_t Array_WorkType_NowMessage_English[ETE_Size];
extern uint16_t Array_WorkType_NowMessage[4];


extern uint16_t Array_WorkType_Stop[4];
extern uint16_t Array_WorkType_Stop_English[ETE_Size];

extern uint16_t Array_WorkType_Run[4];
extern uint16_t Array_WorkType_Run_English[ETE_Size];



extern uint16_t Array_WorkType_ParrelChargeFinish[4];//并充完成
extern uint16_t Array_WorkType_ParrelDisChargeFinish[4];//并放完成
extern uint16_t Array_WorkType_MaintainFinish[4];//维护完成
extern uint16_t Array_WorkType_Finish[4];//工作完成

extern uint16_t Array_WorkType_Finish_English[ETE_Size];//工作完成
extern uint16_t Array_ErrorType_MachineBreakdown_English[ETE_Size];
extern uint16_t Array_WorkType_wrongstop01[4];

//static uint32_t starttime=0,overtime=0;
/**
  * @brief  10秒一次扫通信超时函数
  * @param  
  * @retval 无
  */
void Handle_CheckStop_CommuOverTimeFalg(void){

//	Calculate_StartRunTime(&starttime);
//SYSTEM_INFO("Handle_CheckStop_CommuOverTimeFalg  %d \n",starttime);
	//for(uint16_t ici=1;ici<GV_CommSendToSlaveBoardState.BoardNum;ici++){//123456
	
	
	
//    for (uint16_t ici = 0; ici < GV_HardwareState.hard_board_count; ici++) {

//        if ((GV_HardwareState.hard_board_whichIsActiveBit & (1 << ici)) != 0 ) {

//        }

//    }

	
	
	
	
//		for(uint16_t ici=0;ici<GV_HardwareState.hard_board_count;ici++){//++++
  for (uint16_t ici = 0; ici < GV_HardwareState.hard_board_count; ici++) {

        if ((GV_HardwareState.hard_board_whichIsActiveBit & (1 << ici)) != 0 ) {
            
			
			
			//BOARD_COUNT_CHANGE
	GV_ComuBoardState.commu_overtime[ici]+=1;
//SYSTEM_INFO("===GV_ComuBoardState.commu_overtime[ici]=%d\n",GV_ComuBoardState.commu_overtime[ici]);
//			if(ici==0){
//			
//			GV_ComuBoardState.commu_overtime[ici]=0;
//			}
					
					
	if(GV_ComuBoardState.commu_overtime[ici]>=COMMUNICATION_OVERTIME){
	//GV_ComuBoardState.commu_ErrorOvertimeBOARD=ici+1;
		GV_ComuBoardState.commu_ErrorBoardNo=ici+1;
		GV_ComuBoardState.commu_overtime_FLAG=1;

	//停止启动函数，并报错误超时信息err000
if((GV_ComuBoardState.check_isOverTimeStop[ici]==0)&&(GV_ComuBoardState.commu_ErrorBoardNo!=0)){
	
	StopBoardFunByBoardId(ici,EM_Send);
//MaintainStateRun_AllBoard_Stop(EM_Send);
//	LedClose_All_ByBoardidFun();
//	Set_NeedfinishWorkBit_AllBoard_StateFun();
//	ChangeOneClickCloseIconAndNboardIcon();
//	SetTaskHandlerTimeRloadAndChangeState(&Handle_SendVolDataToScreenAndAskSlave,ASK_SLAVE_NOTWORK_DUTY_TIME,1);
//	

	
//	if(GV_ComuBoardState.commu_OT_scrShowErrorMess_flag[ici]==1){
	GV_ComuBoardState.commu_OT_scrShowErrorMess_flag[ici]=1;
		memcpy(&GV_ComuBoardState.screenBatVolComuState[ici].SC_ErrorType,&Array_ErrorType_OverTime,ETE_Size*2);
	memcpy(&GV_ComuBoardState.screenBatVolComuState[ici].SC_ErrorType_English,&Array_ErrorType_OverTime_English,ETE_Size*2);

	
//	}
	
//	TurnFan_OFF;
//	TurnWork_led_OFF;
	SYSTEM_ERROR("===CommuOverTime***stop***%d",GV_HardwareState.hard_board_count);
GV_ComuBoardState.check_isOverTimeStop[ici]=1;
//	GV_ComuBoardState.check_TimeStop_BoardNo=GV_ComuBoardState.commu_ErrorBoardNo;
	
	
	
	
	
}
    
		
//if(GetWrongLed_STATE!=1){
//TurnWrong_led_ON;
//}			
GetWrongLed_STATEAndled_ON;

memcpy(&Array_WorkType_NowMessage,&Array_ErrorType_OverTime,4*2);
memcpy(&Array_WorkType_NowMessage_English,&Array_ErrorType_OverTime_English,ETE_Size*2);





SYSTEM_ERROR("===CommuOverTime BoardNum=%d time= %d\n",ici+1,GV_ComuBoardState.commu_overtime[ici]);

		
	}else{
	GV_ComuBoardState.commu_OT_scrShowErrorMess_flag[ici]=0;
		
		
	if(GV_ComuBoardState.commu_overtime_FLAG==1){
//	if(GV_ComuBoardState.commu_overtime[ici]<COMMUNICATION_OVERTIME){
	if(IFCommuBoardAllNotOverTime(COMMUNICATION_OVERTIME)==1){

	GV_ComuBoardState.commu_overtime_FLAG=0;
	GV_ComuBoardState.commu_ErrorBoardNo=0;
		GV_ComuBoardState.check_TimeStop_BoardNo=0;
		if(GV_ScreenSetRunBoardState.Set_NowRunState==EM_RunState_Run){
				memcpy(&Array_WorkType_NowMessage,&Array_WorkType_Run,4*2);
memcpy(&Array_WorkType_NowMessage_English,&Array_WorkType_Run_English,ETE_Size*2);
		
		}else{
		memcpy(&Array_WorkType_NowMessage,&Array_WorkType_Stop,4*2);
memcpy(&Array_WorkType_NowMessage_English,&Array_WorkType_Stop_English,ETE_Size*2);
		
		}

		
		TurnWrong_led_OFF;
	
//		GV_ComuBoardState.check_isOverTimeStop=0;
		memset(GV_ComuBoardState.check_isOverTimeStop,0,BOARD_COUNT*2);
	}
	
	}
	
	}
	
		
	
	
}
	
		}//++++
	
//SYSTEM_INFO("Handle_CheckStop_CommuOverTimeFalg  %d \n",Calculate_diffRunTime(&starttime,&overtime));
}




uint8_t IFCommuBoardAllNotOverTime(uint8_t overtime){

for(uint16_t i=0;i<4;i++){
if(GV_ComuBoardState.commu_overtime[i]<overtime){


}else{

return 0;//有超时

}

}
return 1;
}








void Handle_CheckStop_ALLBoard_FinishWork(void){

	
	if(GV_ScreenSetRunBoardState.Set_NowRunState!=EM_RunState_Stop){
	
		
//	if(Buffercmp(GV_ComuBoardState.getSlaveUpdloadState,(uint8_t *)GV_ComuBoardState.getSlaveUpdloadState,8)){
//	
//	
//	
//	}
	
	
for(uint16_t ifw=0;ifw<GV_HardwareState.hard_board_count;ifw++){


	//
	if((
//		(GV_ComuBoardState.getSlaveUpdloadState[ifw].BS_WorkStatus==0)||
	((GV_ComuBoardState.getSlaveUpdloadState[ifw].BS_WorkStatus>=4)&&(GV_ComuBoardState.getSlaveUpdloadState[ifw].BS_WorkStatus<8)) )
		&& (GV_HardwareState.hard_board_whichIsActiveBit & (1 << ifw)) != 0  
//	&& GV_ScreenSetRunBoardState.Set_NowSingleRunState[ifw]==EM_RunState_Run
	){//从控板对应返回完成
	
		
		
		
		
		GV_ComuBoardState.commu_finishwork_FLAG|=(1<<ifw);//对应置1

	}else{
	

		
		
	GV_ComuBoardState.commu_finishwork_FLAG&=(~(1<<ifw));//对应置0
	
	}
	
	
	
	
}

//    uint16_t a = 0x0000; // 示例值

//    // 使用按位或操作来将a的低n位置为1
//    a |= ((1 << (GV_HardwareState.hard_board_count)) - 1);
uint16_t idiff=0;
uint16_t tmpdata=0;
if(GV_ComuBoardState.commu_finishwork_Old_FLAG != GV_ComuBoardState.commu_finishwork_FLAG){
SYSTEM_DEBUG("STOP=    ==\n");
 idiff=find_different_bit_position(GV_ComuBoardState.commu_finishwork_Old_FLAG, GV_ComuBoardState.commu_finishwork_FLAG) ;

	
	
	
if((idiff>=0)&&(idiff<4)){
	
	
	MaintainStateRun_SingleBoard_Stop(idiff,EM_Send);
	LedClose_ByBoardidFun(idiff);
		GV_ScreenSetRunBoardState.Set_NowSingleRunState[idiff]=EM_RunState_Stop;
		ChangeNboardTo_stopORstart_IconState(idiff,EM_RunState_Stop);
		AutoChangeOneStartIconFun();
	
	GV_ComuBoardState.commu_needfinishwork_FLAG&=(~(1<<idiff));//对应置0
	GV_ComuBoardState.commu_finishwork_FLAG&=(~(1<<idiff));//对应置0
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_finishwork_FLAG,"close  commu_finishwork_FLAG==");
//	SYSTEM_DEBUG_BINARY(GV_HardwareState.hard_board_whichIsActiveBit,"PPPP ");
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_needfinishwork_FLAG,"close  commu_needfinishwork_FLAG== ");
}

	
	
	
GV_ComuBoardState.commu_finishwork_Old_FLAG=GV_ComuBoardState.commu_finishwork_FLAG;
}




if((GV_ComuBoardState.commu_finishwork_FLAG==(GV_ComuBoardState.commu_needfinishwork_FLAG & GV_HardwareState.hard_board_whichIsActiveBit))&&(GV_ScreenSetRunBoardState.Set_NowRunState!=EM_RunState_Stop)){

	SYSTEM_DEBUG("STOP=all    ==\n");

	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_finishwork_FLAG,"commu_finishwork_FLAG=");
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_needfinishwork_FLAG,"commu_needfinishwork_FLAG=");
//	SYSTEM_DEBUG_BINARY(GV_HardwareState.hard_board_whichIsActiveBit,"GV_HardwareState.hard_board_whichIsActiveBit=");
	
	
MaintainStateRun_AllBoard_Stop(EM_Send);
	
//	ChangeOneClickOpenIconAndNboardIcon();
	ChangeOneClickCloseIconAndNboardIcon();
	SetTaskHandlerTimeRloadAndChangeState(&Handle_SendVolDataToScreenAndAskSlave,ASK_SLAVE_NOTWORK_DUTY_TIME,1);
	SuspendTaskHandler(Handle_CheckStop_ALLBoard_FinishWork);
	TurnFinish_led_ON;
	TurnFan_OFF;
memcpy(&Array_WorkType_NowMessage,&Array_WorkType_Finish,4*2);
memcpy(&Array_WorkType_NowMessage_English,&Array_WorkType_Finish_English,ETE_Size*2);


}


	
}

}
















/**
* @brief  4秒发送一次屏幕函数并采集
  * @param  
  * @retval 无
  */
//static uint32_t starttime2=0,overtime2=0;
void Handle_SendVolDataToScreenAndAskSlave(void){

//		Calculate_StartRunTime(&starttime2);
//SYSTEM_INFO("Handle_SendVolDataToScreenAndAskSlave  %d \n",starttime2);
	
ScreenSendVolDataToScreen();
//	SYSTEM_INFO("Handle_SendVolDataToScreenAndAskSlave 1  %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
comu_SendslaveAskdata();	//从485访问来询问从机数据
	
//SYSTEM_INFO("Handle_SendVolDataToScreenAndAskSlave 2 %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
//	Handle_CheckStop_ALLBoard_FinishWork();//监测停止条件
	
//	SYSTEM_INFO("Handle_SendVolDataToScreenAndAskSlave 3 %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
//SYSTEM_DEBUG("Handle_CheckStop_ALLBoard_FinishWork==\n");
}





/**
* @brief  4秒发送一次屏幕函数容量数据
  * @param  
  * @retval 无
  */
//static uint32_t starttime3=0,overtime3=0;
void Handle_SendCapacityDataToScreen(void){
//		Calculate_StartRunTime(&starttime3);
//SYSTEM_INFO("Handle_SendCapacityDataToScreen  %d \n",starttime3);
	
ScreenCapacityDataToScreen();
	
//	SYSTEM_INFO("Handle_SendCapacityDataToScreen  %d \n",Calculate_diffRunTime(&starttime3,&overtime3));

}





/**
* @brief  4秒发送一次屏幕函数容量数据
  * @param  
  * @retval 无
  */

//static uint32_t starttime4=0,overtime4=0;
void Handle_SendSDTimeDataToScreen(void){
	
//		Calculate_StartRunTime(&starttime4);
//SYSTEM_INFO("Handle_SendSDTimeDataToScreen  %d \n",starttime4);
	
sd_usart_cmd_ReadTime();
pull_data_from_SD_485();pull_data_from_SD_485();
	
//		SYSTEM_INFO("Handle_SendSDTimeDataToScreen  %d \n",Calculate_diffRunTime(&starttime4,&overtime4));

}



/**
* @brief  50ms
  * @param  
  * @retval 无
  */
//creat_ticktime(1)
//static uint32_t starttime5=0,overtime5=0;
void Handle_SendSlaveAskdataAfter50MS(void){
//SYSTEM_DEBUG(" ==s485_SendSlaveAskdataAfter50MS   1");
//		Calculate_StartRunTime(&starttime5);
//SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",starttime5);
	
	
	
  s485_SendSlaveAskdataAfter50MS();
	
	
//	SYSTEM_DEBUG(" ==s485_SendSlaveAskdataAfter50MS   2");
	SuspendTaskHandler(&Handle_SendSlaveAskdataAfter50MS);
	
//	SYSTEM_DEBUG(" ==s485_SendSlaveAskdataAfter50MS   3");
	
//	SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",Calculate_diffRunTime(&starttime5,&overtime5));
}






/**
* @brief  50ms
  * @param  
  * @retval 无
  */

void Handle_SaveSdData(void){

//SD_Save_Fun();
	
	SYSTEM_INFO("===Handle_SaveSdData\n");
ResumeTaskHandler(&Handle_ImmediateSaveSd);
	
}

void Handle_ImmediateSaveSd(void){
SYSTEM_INFO("===Handle_ImmediateSaveSd\n");
//SD_Save_Fun();

	
}


//static uint32_t starttime6=0,overtime6=0;
void Handle_getTime(void){
//		Calculate_StartRunTime(&starttime6);
//SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",starttime6);
	
 DS1302_getTime_Fun();
	
//	SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",Calculate_diffRunTime(&starttime6,&overtime6));
}

void Handle_ChangeCheckStop_ALLBoard_FinishWork_time(void){
//		Calculate_StartRunTime(&starttime6);
//SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",starttime6);
	
 
	SetTaskHandlerTimeRloadAndChangeState(&Handle_CheckStop_ALLBoard_FinishWork,4000,1);
	SuspendTaskHandler(Handle_ChangeCheckStop_ALLBoard_FinishWork_time);
	SuspendTaskHandler(Handle_CheckStop_ALLBoard_FinishWork);
//	SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",Calculate_diffRunTime(&starttime6,&overtime6));
}

void Handle_showdata(void){
//		Calculate_StartRunTime(&starttime6);
//SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",starttime6);
//	 GV_ScreenSetRunBoardState.Set_NowSingleRunState==EM_RunState_Run
// DS1302_getTime_Fun();GV_ComuBoardState.commu_finishwork_FLAG
	SYSTEM_getAllLightsStateCountersfun();
	#if 0
	SYSTEM_DEBUG_BINARY(GV_HardwareState.hard_board_whichIsActiveBit,"hard_board_whichIsActiveBit  \n");
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_needfinishwork_FLAG,"commu_needfinishwork_FLAG  \n");
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_finishwork_Old_FLAG,"commu_finishwork_Old_FLAG  \n");
	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_finishwork_FLAG,"commu_finishwork_FLAG  \n");
	
	#endif
	
//	GV_ComuBoardState.commu_finishwork_Old_FLAG
//	SYSTEM_DEBUG_BINARY(GV_ComuBoardState.commu_finishwork_FLAG,"commu_finishwork_FLAG  \n");
	SYSTEM_DEBUG_ARRAY_MESSAGE_HorA(0,(uint8_t *)GV_ScreenSetRunBoardState.Set_NowSingleRunState,8,"Set_NowRunState = %d \n",GV_ScreenSetRunBoardState.Set_NowRunState);
	
	 PrintTaskHandlerState(Handle_CheckStop_ALLBoard_FinishWork);
//	SYSTEM_INFO("Handle_SendSlaveAskdataAfter50MS  %d \n",Calculate_diffRunTime(&starttime6,&overtime6));
}



void Handle_FeedIWatchDog(void){


	
	
	IWDG_Feed();		
	
	
}



#include "./test/bsp_test_can.h" 
#include "./service/CanFun.h"

void Handle_can(void){
//uint64_t i=GetSysRunTime();
CanDataSendAlwaysFun();
//SYSTEM_DEBUG("Handle_test 1s*** time=%u",(uint32_t)GetSysRunTime());
//SYSTEM_DEBUG("CAN_Test---------");
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t *)GV_ScreenSetRunBoardState.Set_ChargeStateSelect,8,"----////=====hehe");
//printf("Handle_test 1s*** time=%llu",i);
}



/**
* @brief  50ms
  * @param  
  * @retval 无
  */
void Handle_test(void){
//uint64_t i=GetSysRunTime();

SYSTEM_DEBUG("Handle_test 1s*** time=%u",(uint32_t)GetSysRunTime());

//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t *)GV_ScreenSetRunBoardState.Set_ChargeStateSelect,8,"----////=====hehe");
//printf("Handle_test 1s*** time=%llu",i);
}

