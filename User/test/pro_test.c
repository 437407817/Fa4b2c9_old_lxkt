


#include "./test/pro_test.h"  


#include "./GV_variable.h" 
#include <stdlib.h>

 #include "./sys/sysio.h"
#include "string.h"


extern str_ScreenSetRunState GV_ScreenSetRunBoardState;



extern str_EEpromSettingState TMP_EEpromSettingState;




extern ScreenCommu_Item_t  GV_ScreenCommu;
extern str_HardwareState GV_HardwareState; 
extern str_BatterySetCalibration GV_BatterySetCalibration;
extern str_ComuBoardState GV_ComuBoardState;
extern str_CommSendToSlaveBoardState GV_CommSendToSlaveBoardState;
extern str_CommSlaveAskState GV_CommSlaveAskState;


void Pro_Test(uint8_t workStatus){

for(uint16_t i=0;i<12;i++){

GV_ComuBoardState.getSlaveUpdloadState[i].BS_Addr=i+1;
GV_ComuBoardState.getSlaveUpdloadState[i].BS_WorkStatus=workStatus;

	
	memset(GV_ComuBoardState.getSlaveUpdloadState[i].BS_Vol,(int16_t)(3000+i),12);
	
	

}





}































