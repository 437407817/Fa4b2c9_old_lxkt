

#include "./service/DisStateFun.h"

//#include "./sys/bsp_systime.h"   





//#include "./GV_variable.h"
//#include "./sys/sysio.h"


//#include "./screen/Screen.h"
//#include "./screen/ScreenDataDis.h"

//extern uint32_t baiseTimeCount01;

extern SYSState_Item_t GV_SYSState;
extern HardwareState_Item_t GV_HardwareState;
extern BatterySetTargetStateItem_t  GV_BatterySetTargetState;
extern BatteryStateItem_t   GV_BatteryState;
extern CommuDataMasterToSlave_Item_t  GV_S_CommuDataSlaveGot;
extern CommuDataSlaveToMaster_Item_t  GV_S_CommuDataSlave_SlaveSend;
extern ScreenBatteryShow_Item_t GV_ScreenBatteryShow;

extern CommuDataMasterToSlave_Item_t  GV_M_CommuDataMasterSend;
extern CommuDataSlaveToMaster_Item_t  GV_M_CommuDataSlave2_MasterGot,GV_M_CommuDataSlave3_MasterGot;


extern Test_Item_t GV_Test;


uint16_t Array_message01SerialRun[5]={0xB4AE,0xB3E4,0xD6D0,0x2020,0x2020};//串充中
uint16_t Array_message02ParallelRun[5]={0xB2A2,0xB3E4,0xD6D0,0x2020,0x2020};//并充中
uint16_t Array_message03Stop[5]={0xB4FD,0xBBFA,0xD6D0,0x2020,0x2020};//待机中
uint16_t Array_message04Pause[5]={0xD4DD,0xCDA3,0xD6D0,0x2020,0x2020};//暂停中
uint16_t Array_message05Delay[5]={0xD1D3,0xCAB1,0xD6D0,0x2020,0x2020};//延时中
   
uint16_t Array_message06SingleStop[5]={0xB5A5,0xCCE5,0xC2FA,0xCDEA,0xB3C9};//单体满完成
uint16_t Array_message07SerialStop[5]={0xB4AE,0xB3E4,0xC2FA,0xCDEA,0xB3C9};//串充满完成
uint16_t Array_message08ParrelStop[5]={0xB2A2,0xB3E4,0xC2FA,0xCDEA,0xB3C9};//并充满完成

uint16_t Array_message[5];
uint16_t Array_messageDelayTime;





void RunMaintainWork_ChangeIn(void){
	
if(GV_BatterySetTargetState.Battery_SET_SerialorParrel==3)//维护
{
	//判断电压达到上限了吗？？999 单体上限和总体上限，如果达到了，则返回，并进入状态2
 
	//GV_HardwareState.Serial_parallel_Delay_Nowstate=1;
	//GV_SYSState.RunStateChangeIN=0;
	
	SYSTME_INFO("\n **********switch maintain**********\n");
}else if(GV_BatterySetTargetState.Battery_SET_SerialorParrel==1){//并充
	//判断电压达到上限了吗？？999 单体上限和总体上限，如果达到了，则返回，并进入状态2

	//GV_HardwareState.Serial_parallel_Delay_Nowstate=1;
//GV_SYSState.RunStateChangeIN=0;
	SYSTME_INFO("\n **********switch bingchong**********\n");
}else if(GV_BatterySetTargetState.Battery_SET_SerialorParrel==2){//并放
	//判断电压达到上限了吗？？999 单体哪个达到停哪个
 

	//GV_HardwareState.Serial_parallel_Delay_Nowstate=2;

//GV_SYSState.RunStateChangeIN=0;
		SYSTME_INFO("\n **********switch bingfang**********\n");
}

}



void MaintainStateRun_Start(void){
	//


}



void MaintainStateRun_Stop(void){
	//
if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==1){

MaintainState_SerialRun_Stop();

}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==2){

MaintainState_ParallelRun_Stop();

}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==3){

MaintainState_Delay_Stop();

}

GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=0;

}









void MaintainState_SerialRun_Start(void){

//GV_BatterySetTargetState.Battery_SET_Maintain_Num
//GV_BatterySetTargetState.Battery_SET_SumlimitValue
	//判断电压达到上限了吗？？999 单体上限和总体上限，如果达到了，则返回，并进入状态2

	GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=1;
	
	//GV_SYSState.RunStateChangeIN=0;
	GV_HardwareState.Slave_2_ChargerParallelNeedBitState=0;
	GV_HardwareState.Slave_3_ChargerParallelNeedBitState=0;
	GV_HardwareState.Master_1_ChargerParallelNeedBitState=0;
	GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;//改变从机关闭状态一次//d从发送2时Slave_ChangeParallelBitChange=0，否则一直发1;
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
	CANMaster_M_Send_S_Run_TestSet();
	  MasterBoardSerialChargeON;
	
	//Array_message=Array_message01SerialRun;
	memcpy(&Array_message,&Array_message01SerialRun,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	SYSTME_INFO("\n **********SerialRun_Start**********\n");
	
	
	//屏幕提示串充启动中999

}



void MaintainState_SerialRun_Stop(void){

//GV_BatterySetTargetState.Battery_SET_Maintain_Num
//GV_BatterySetTargetState.Battery_SET_SumlimitValue
	//判断电压达到上限了吗？？999 单体上限和总体上限，如果达到了，则返回，并进入状态2

	GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=0;
	
	//GV_SYSState.RunStateChangeIN=0;

GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;//改变从机关闭状态一次//d从发送2时Slave_ChangeParallelBitChange=0，否则一直发1;
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
	//CANMaster_M_Send_S_Run_TestSet();
	
		 MasterBoardSerialChargeOFF;
	
		memcpy(&Array_message,&Array_message03Stop,10);
	SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	  

	//memcpy(&Array_message,&Array_message03Stop,6);
	//SCREEN_write_cmd(EM_StateMessage,Array_message,3);//发送电压状态
		SYSTME_INFO("\n **********SerialRun_Stop**********\n");
	
	//屏幕提示串充启动中999

}


#endif



void MaintainState_ParallelRun_Start(void){

GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=2;
//ChargerParallelNeedBitSetOpen();//设置串充状态位
	RelayGateALL_On;
	GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;
	
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
SwitchMaster_SlaveParllelCharger();//打开主机并充
	CANMaster_M_Send_S_Run_TestSet();//can发送给从机
	
	//屏幕提示串充启动中999
	memcpy(&Array_message,&Array_message02ParallelRun,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);//发送电压状态
	SYSTME_INFO("\n **********ParallelRun_Start**********\n");
//	delay_ms
}





void MaintainState_ParallelRun_Stop(void){
GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=0;
GV_HardwareState.Master_1_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_2_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_3_ChargerParallelNeedBitState=0;
	
GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;
	
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
SwitchMaster_SlaveParllelCharger();//打开主机并充
CANMaster_M_Send_S_Run_TestSet();//can发送给从机	
	delay_ms(50);
	RelayGateALL_Off;
	GV_BatterySetTargetState.Battery_SET_RunState=0;
	SCREEN_write_cmd(EM_ICOAddress_RunState,&GV_BatterySetTargetState.Battery_SET_RunState,1);	
	memcpy(&Array_message,&Array_message08ParrelStop,10);
	SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	
SYSTME_INFO("\n **********ParallelRun_Stop**********\n");

}






void MaintainState_Pause(void){

if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==1){

MaintainState_SerialRun_Pause();//串充暂停


}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==2){

MaintainState_ParallelRun_Pause();

}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==3){

MaintainState_Delay_Pause();

}
memcpy(&Array_message,&Array_message04Pause,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);//发送电压状态
}


void MaintainState_PauseResume(void){

if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==1){

MaintainState_SerialRun_PauseResume();////串充暂停恢复



}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==2){

MaintainState_ParallelRun_PauseResume();

}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==3){

MaintainState_Delay_PauseResume();

}

}







void MaintainState_SerialRun_Pause(void){
GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=1;

	 MasterBoardSerialChargeOFF;
	
	
	SYSTME_INFO("\n **********SerialRun_Pause**********\n");

}





void MaintainState_ParallelRun_Pause(void){
GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=2;
	
GV_HardwareState.Master_1_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_2_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_3_ChargerParallelNeedBitState=0;
GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
SwitchMaster_SlaveParllelCharger();//打开主机并充
CANMaster_M_Send_S_Run_TestSet();//can发送给从机
	delay_ms(50);
	RelayGateALL_Off;
	
	SYSTME_INFO("\n **********ParallelRun_Pause**********\n");
}

void MaintainState_SerialRun_PauseResume(void){
GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=1;

	 MasterBoardSerialChargeON;
	
	memcpy(&Array_message,&Array_message01SerialRun,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	SYSTME_INFO("\n **********SerialRun_PauseResume**********\n");

}


void MaintainState_ParallelRun_PauseResume(void){
GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=2;
GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;	
	
	SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
//ChargerParallelNeedBitSetOpen();
	RelayGateALL_On;
	delay_ms(50);
SwitchMaster_SlaveParllelCharger();//打开主机并充
CANMaster_M_Send_S_Run_TestSet();//can发送给从机
	
		memcpy(&Array_message,&Array_message02ParallelRun,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	
SYSTME_INFO("\n **********ParallelRun_PauseResume**********\n");
}









void MaintainState_DelayRun_Start(void){
	

	GV_SYSState.Delay_MintuesSeconds=0;
	GV_SYSState.Delay_MintuesSeconds_On=1;
	GV_SYSState.Delay_MintuesSeconds_hard=GV_BatterySetTargetState.Battery_SET_Delay_Mintues*60+GV_BatterySetTargetState.Battery_SET_Delay_Seconds;

	memcpy(&Array_message,&Array_message05Delay,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	SYSTME_INFO("\n **********DelayRun_Start**********\n");
}
	

void MaintainState_Delay_Pause(void){
	GV_SYSState.Delay_MintuesSeconds_On=0;

	SYSTME_INFO("\n **********Delay_Pause**********\n");
}

void MaintainState_Delay_PauseResume(void){
	GV_SYSState.Delay_MintuesSeconds_On=1;
	
	
	memcpy(&Array_message,&Array_message05Delay,10);SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	
SYSTME_INFO("\n **********Delay_PauseResume**********\n");
}

void MaintainState_Delay_Stop(void){
	GV_SYSState.Delay_MintuesSeconds_On=0;
	SYSTME_INFO("\n **********Delay_Stop**enter into *ParallelRun*******\n");
	MaintainState_ParallelRun_Start();

}






















void ChargerParallelNeedBitSetOpen(void){
	
	
	
if((GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==2)&&(GV_BatterySetTargetState.Battery_SET_RunState==1)){

for(uint8_t i=0;i<GV_BatterySetTargetState.Battery_SET_Maintain_Num;i++){
	if(((GV_BatteryState.ALL_ParallelSaturateVolBitState>>i)&0x0001)==0){
		
		if(i<8){
		
	GV_HardwareState.Master_1_ChargerParallelNeedBitState|=(0x01<<i);
		
	}else if(i<16){
		
	GV_HardwareState.Slave_2_ChargerParallelNeedBitState|=(0x01<<(i-8));
	
	}else if(i<24){
	GV_HardwareState.Slave_3_ChargerParallelNeedBitState|=(0x01<<(i-16));	
	
	}
	
}else{


		if(i<8){
		
	GV_HardwareState.Master_1_ChargerParallelNeedBitState&=~(0x01<<i);
		
	}else if(i<16){
		
	GV_HardwareState.Slave_2_ChargerParallelNeedBitState&=~(0x01<<(i-8));
	
	}else if(i<24){
	GV_HardwareState.Slave_3_ChargerParallelNeedBitState&=~(0x01<<(i-16));	
	
	}



}
	
}



if((GV_HardwareState.Slave_2_ChargerParallelNeedBitState!=GV_HardwareState.Slave_2_ChargerParallelReadBitState)||
	(GV_HardwareState.Slave_3_ChargerParallelNeedBitState!=GV_HardwareState.Slave_3_ChargerParallelReadBitState)){

GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange=1;
		
		SYSTME_DEBUG("*GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange**%d  ***\n",GV_M_CommuDataMasterSend.Slave_ChangeParallelBitChange);
}



}else{
//	SYSTME_DEBUG("dxxxxxxxxxxxxxx  clear-");
GV_HardwareState.Master_1_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_2_ChargerParallelNeedBitState=0;
GV_HardwareState.Slave_3_ChargerParallelNeedBitState=0;	
}
	//SYSTME_DEBUG("dxxxxxxxxxxxxxx  %d --%x-  %d",GV_HardwareState.Slave_2_ChargerParallelNeedBitState,GV_BatteryState.ALL_ParallelSaturateVolBitState,GV_BatterySetTargetState.Battery_SET_Maintain_Num);

//SYSTME_DEBUG("GV_HardwareState.Master_1_ChargerParallelNeedBitState =.AAA.=%x  %x  ",GV_HardwareState.Master_1_ChargerParallelNeedBitState ,GV_BatteryState.ALL_ParallelSaturateVolBitState);







}
	
	void SwitchMaster_SlaveParllelCharger(void){
	
		if(GV_HardwareState.BatteryChargerParallel_R1A_S2A==0){
	ChargeChangeTo1A;
			
			//SYSTME_DEBUG("ChargeChangeTo1A++++++++++1111\n");
			
		GV_SYSState.ParrleCurrentNowis=1;
	}else{
	ChargeChangeTo2A;	
		
		//SYSTME_DEBUG("ChargeChangeTo2A+++++++++++2222\n");
		GV_SYSState.ParrleCurrentNowis=2;
	}
	if(GV_HardwareState.CHX_step==0){
	
	GV_HardwareState.Master_1_ChargerParallelReadBitState = ~RelayReadPallelChargeOutputDataBit();
	}
    
	
	
	
		//SYSTME_DEBUG("GV_HardwareState.Master_1_ChargerParallelNeedBitState =...=%x  %x",GV_HardwareState.Master_1_ChargerParallelNeedBitState ,GV_HardwareState.Master_1_ChargerParallelReadBitState);
	
//		if(GV_HardwareState.Master_1_ChargerParallelNeedBitState != GV_HardwareState.Master_1_ChargerParallelReadBitState){//未打开的话，打开
//	  ChargerParallelByBitOpen(GV_HardwareState.Master_1_ChargerParallelNeedBitState);
//	

//	}
//  delay_ms(10);
//	GV_HardwareState.Master_1_ChargerParallelReadBitState = ~RelayReadPallelChargeOutputDataBit();
	
	
	
	
		//SYSTME_DEBUG("GV_HardwareState.Master_1_ChargerParallelNeedBitState =...=%x  %x",GV_HardwareState.Master_1_ChargerParallelNeedBitState ,GV_HardwareState.Master_1_ChargerParallelReadBitState);
//	GV_M_CommuDataMasterSend
	
// CANMasterPackCommuDataNeedSendtoSlave();
	
	
	
	//屏幕数据


	}
	


	
	

		
	
	


void MaintainState_Runwhile_CheckStop(void){
if(GV_BatterySetTargetState.Battery_SET_RunState==1){//只有在启动运行中才判断是否停止



	if((GV_BatterySetTargetState.Battery_SET_SerialorParrel==0)||(GV_BatterySetTargetState.Battery_SET_SerialorParrel==1))//均衡或串充
{
if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==1){//串充中
if((GV_BatteryState.ALL_ParallelSaturateVolBitState!=0)||(GV_BatteryState.SumSerial_vol_Value>=GV_BatterySetTargetState.Battery_SET_SumlimitValue)){
SYSTME_INFO("\n *********MasterBoardSerialChargeOFF*****%x  %d**%d*\n",GV_BatteryState.ALL_ParallelSaturateVolBitState,GV_BatteryState.Max_vol_Value,GV_BatterySetTargetState.Battery_SET_SumlimitValue);
 MasterBoardSerialChargeOFF;
	
	if(GV_BatteryState.ALL_ParallelSaturateVolBitState!=0){
		memcpy(&Array_message,&Array_message06SingleStop,10);
	SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	}
	else if(GV_BatteryState.SumSerial_vol_Value>=GV_BatterySetTargetState.Battery_SET_SumlimitValue){
			memcpy(&Array_message,&Array_message07SerialStop,10);
	SCREEN_write_cmd(EM_StateMessage,Array_message,5);
	}
	
	
	
	if(GV_BatterySetTargetState.Battery_SET_SerialorParrel==0){//如果设置的是均衡状态
		MaintainState_SerialRun_Stop();
	GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=3;//进入延迟状态
		//EnterIntoRunState_ChangeIn();//
		MaintainState_DelayRun_Start();
	}else{
		
		
	GV_HardwareState.HS_Serial_parallel_Delay_Nowstate=0;//进入停止状态
		MaintainState_SerialRun_Stop();
			GV_BatterySetTargetState.Battery_SET_RunState=0;
	SCREEN_write_cmd(EM_ICOAddress_RunState,&GV_BatterySetTargetState.Battery_SET_RunState,1);	
	}
	
	
	//提示停止999
}

}else if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==3){//延迟状态
if(GV_SYSState.Delay_MintuesSeconds_On==1){
					
	      // GV_SYSState.Delay_MintuesSeconds++;
	//	SYSTME_DEBUG("\n *********%d********%d \n",GV_SYSState.Delay_MintuesSeconds_On,GV_SYSState.Delay_MintuesSeconds_hard-GV_SYSState.Delay_MintuesSeconds);	
	//memcpy(&Array_message,&Array_message01SerialRun,6);
	Array_messageDelayTime=GV_SYSState.Delay_MintuesSeconds_hard-GV_SYSState.Delay_MintuesSeconds;
	SCREEN_write_cmd(EM_StateMessageDelay,&Array_messageDelayTime,1);
			//	SCREEN_write_cmd(EM_ICOAddress_RunState,&GV_BatterySetTargetState.Battery_SET_RunState,1);
if(GV_SYSState.Delay_MintuesSeconds>=GV_SYSState.Delay_MintuesSeconds_hard){
					Array_messageDelayTime=0;
	SCREEN_write_cmd(EM_StateMessageDelay,&Array_messageDelayTime,1);
					MaintainState_Delay_Stop();
					
}

//GV_BatterySetTargetState.Battery_SET_RunState=2;

}else if(GV_BatterySetTargetState.Battery_SET_RunState==2){//延迟暂停状态



}


}

}
if(GV_HardwareState.HS_Serial_parallel_Delay_Nowstate==2){//并充

SwitchMaster_SlaveParllelCharger();
	ChargerParallelNeedBitSetOpen();
	if((GV_HardwareState.Master_1_ChargerParallelNeedBitState==0)&&(GV_HardwareState.Slave_2_ChargerParallelNeedBitState==0)&&(GV_HardwareState.Slave_3_ChargerParallelNeedBitState==0)
		&&(GV_BatterySetTargetState.Battery_SET_RunState!=2)){
			GV_BatterySetTargetState.Battery_SET_RunState=0;
			
			
			MaintainStateRun_Stop();
	//	SCREEN_write_cmd(EM_ICOAddress_RunState,&GV_BatterySetTargetState.Battery_SET_RunState,0);	
	}
		
	if(GV_HardwareState.ReadyRunState!=1){
				GV_BatterySetTargetState.Battery_SET_RunState=0;

			MaintainStateRun_Stop();
	
	}
	
//SYSTME_INFO(" *********SwitchMaster_SlaveParllelCharger***999999*");

}

	
	
	}

}
























/*********************************************END OF FILE**********************/
