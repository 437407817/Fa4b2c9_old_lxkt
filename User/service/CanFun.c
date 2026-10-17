#include "./service/CanFun.h"

#include "./sys/bsp_systime.h"   


 #include "./sys/sysio.h"

 #include "./can/bsp_can.h" 




#include <stdint.h>
#include "./sys/bsp_random.h" 


extern str_SendAllCanDataState		GV_SendAllCanDataState;
extern str_ComuBoardState GV_ComuBoardState;
extern str_ScreenSettingDataState GV_ScreenSettingDataState;



extern str_ScreenSettingCANDataState     GV_ScreenSetting_CAN_DataState;



void CanDataDisposeFun(void){

//	for(uint16_t i=0;i<BOARD_COUNT;i++)
//{
//	
//memcpy(&GV_SendAllCanDataState.GV_SendSingleCanDataState[i],&GV_ComuBoardState.getSlaveUpdloadState[i],106);	
//memcpy(&GV_SendAllCanDataState.GV_SendSingleCanDataState[i].CAN_SUMvol,&GV_ComuBoardState.screenBatVolComuState[i].SC_SUMvol,4*2);	
//		
//}
	
	RNG_Random_setArray((uint16_t *)&GV_SendAllCanDataState,sizeof(GV_SendAllCanDataState)/ sizeof(uint16_t),0,0xFFFF);
}



void CanDataSendAlwaysFun(void){

CANx_IT_DataDispose();
    uint16_t ret;
CanDataDisposeFun();
//for(uint16_t i=0;i<BOARD_COUNT;i++){
	#if 0
    // 调用分包发送；0x18000001为CAN扩展帧ID
    ret = CANx_SendExtFrame_StructSplit(CAN_SEND_ID_1, (uint8_t *)&GV_SendAllCanDataState.GV_SendSingleCanDataState[0], 118);
	delay_ms(1);
CANx_SendExtFrame_StructSplit(CAN_SEND_ID_2, (uint8_t *)&GV_SendAllCanDataState.GV_SendSingleCanDataState[1], 118);
		delay_ms(1);
	CANx_SendExtFrame_StructSplit(CAN_SEND_ID_3, (uint8_t *)&GV_SendAllCanDataState.GV_SendSingleCanDataState[2], 118);
		delay_ms(1);
	CANx_SendExtFrame_StructSplit(CAN_SEND_ID_4, (uint8_t *)&GV_SendAllCanDataState.GV_SendSingleCanDataState[3], 118);
		delay_ms(1);
	#endif
if(ret == 0)
{
//    SYSTEM_DEBUG("can send over------------- ");
}
else
{
    // 如果某一次因为总线忙发送失败，不要让单片机崩溃，打印个日志跳过即可
//    SYSTEM_DEBUG("can send error, fail at pkg: %d", ret);
    
    // 【核心防卡死】如果连续发生发送失败或总线异常，建议在这里执行一次CAN外设软件复位，防止硬件锁死
    // CAN_DeInit(CANx);
    // CANx_Mode_Init();
}
//}

}



/**
 * @brief 将GV_ScreenSettingDataState前4组参数拷贝到CAN发送用结构体GV_ScreenSetting_CAN_DataState
 */
void ScreenSettingData_CopyToCanData(void)
{
    uint8_t i;
    // 循环0~3，拷贝每个数组的前4个元素
    for(i = 0; i < 4; i++)
    {
        GV_ScreenSetting_CAN_DataState.Set_Bat_SingleBattRun[i]        = GV_ScreenSettingDataState.Set_Bat_SingleBattRun[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_Run_Vol_difference[i]   = GV_ScreenSettingDataState.Set_Bat_Run_Vol_difference[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_RunCount_polar[i]      = GV_ScreenSettingDataState.Set_Bat_RunCount_polar[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_Runworkingmode[i]       = GV_ScreenSettingDataState.Set_Bat_Runworkingmode[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_BattNum[i]              = GV_ScreenSettingDataState.Set_Bat_BattNum[i];

        GV_ScreenSetting_CAN_DataState.Set_Bat_UpperLimitParallelVol[i]    = GV_ScreenSettingDataState.Set_Bat_UpperLimitParallelVol[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_UpperAlarmParallelVol[i]   = GV_ScreenSettingDataState.Set_Bat_UpperAlarmParallelVol[i];

        GV_ScreenSetting_CAN_DataState.Set_Bat_LowVoltageAlarm[i]         = GV_ScreenSettingDataState.Set_Bat_LowVoltageAlarm[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_ChargeCurrent_xmA[i]       = GV_ScreenSettingDataState.Set_Bat_ChargeCurrent_xmA[i];

        GV_ScreenSetting_CAN_DataState.Set_Bat_StopCapacity[i]    = GV_ScreenSettingDataState.Set_Bat_StopCapacity[i];
        GV_ScreenSetting_CAN_DataState.Set_Bat_StopTime[i]        = GV_ScreenSettingDataState.Set_Bat_StopTime[i];
    }
}


/**
 * @brief 外部业务：处理CAN_GET_ID_1接收到的数据
 * @param data 接收的数据数组
 * @param len 有效字节长度DLC
 */
void User_CanGetId1Process(uint8_t *data, uint8_t len)
{
    // 在这里写你的业务解析逻辑
    SYSTEM_DEBUG("User_CanGetId1Process len=%d", len);
    SYSTEM_DEBUG_ARRAY_MESSAGE(data, len,"User CAN Data:");
uint16_t ret;
	// 屏幕参数更新之后，调用拷贝
ScreenSettingData_CopyToCanData();

// 之后直接拿 GV_ScreenSetting_CAN_DataState 做CAN分包发送
ret = CANx_SendExtFrame_StructSplit(CAN_SEND_ID_RETURN_1,
                                    (uint8_t *)&GV_ScreenSetting_CAN_DataState,
                                    sizeof(str_ScreenSettingCANDataState));
	
    /*
    示例：
    uint8_t val0 = data[0];
    uint16_t val1 = (data[1] <<8) | data[2];
    */
}







/*********************************************END OF FILE**********************/
