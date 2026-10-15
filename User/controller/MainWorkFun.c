



#include "./controller/MainWorkFun.h"


#include "./sdram/bsp_sdram.h"   
#include "./test/bsp_test_sdram.h" 

#include "./sensor/bsp_test_DS1302.h"
#include "./adc/ADS7822.h"
#include "./adc/CC6902.h"

#include "./dac/DAC7311.h"

#include "./controller/StateFun.h"

 #include "./controller/TaskFun.h"
#include "./communication/Comu485Dis.h"
#include "./screen/ScreenDataDis.h"

#include "./communication/SD_485Dis.h"


void ALLperipheral_SingleWork(void)
{

	ScreenJumpToMainPage();
	
	
//	Delay(10800);

}


void ALLperipheral_RepetitionWork(void)
{

	
	//	MasterMain_While();
	//ScreenSendParaVol();
	SEGGER_HostDataToUsart();
	//pull_data_from_screen();
	//pull_data_from_485();
	//pull_data_from_SD_485();
	
	
}























