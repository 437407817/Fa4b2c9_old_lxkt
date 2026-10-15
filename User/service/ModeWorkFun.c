






#include "./service/ModeWorkFun.h"
#include "./GV_variable.h"
#include "./sys/sysio.h"

#include "./communication/Comu485Dis.h"
#include "./screen/ScreenSendFun.h"
#include "./defines.h"
#include "./io/OUT_io/bsp_gpio_out.h"   
#include "./converter/data_convert.h"

extern str_ScreenSetRunState GV_ScreenSetRunBoardState;
extern str_HardwareState GV_HardwareState; 

extern str_CommSendToSlaveBoardState GV_CommSendToSlaveBoardState;


extern uint16_t Array_WorkType_ParrelCharge[4];//并充中
extern uint16_t Array_WorkType_ParrelDisCharge[4];//并放中
extern uint16_t Array_WorkType_Maintain[4];//维护中

extern uint16_t Array_WorkType_SerialCharge[4];//串充中
extern uint16_t Array_WorkType_SerialDisCharge[4];//串放中

extern uint16_t Array_WorkType_Stop[4];//待机中
extern uint16_t Array_WorkType_ParrelChargeFinish[4];//并充完成
extern uint16_t Array_WorkType_ParrelDisChargeFinish[4];//并放完成
extern uint16_t Array_WorkType_MaintainFinish[4];//维护完成
extern uint16_t Array_WorkType_NowMessage[4];








































