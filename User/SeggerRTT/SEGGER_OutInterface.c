#include "./SeggerRTT/SEGGER_OutInterface.h"
#include "./SeggerRTT/SEGGER_RTT.h"
#include "./sys/bsp_systime.h"   
#include "string.h"
#include <stdlib.h>

#include "stm32fxxx.h"


 #include "./sys/sysio.h"

#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./converter/data_convert.h"
#include <stdlib.h>

#include "./SeggerRTT/SEGGER_OutInterface.h"
#include "./iwdg/bsp_iwdg.h"   
/**
  * @brief  切换采集通道channel for collection
  */


#include "./communication/SD_485DataFun.h"
#include "./usart/bsp_usart_sd.h"
#include "./service/EepromFun.h"

#include "./controller/TaskFun.h"
#include "./controller/TaskSingleWork.h"  

#include "./sensor/DS1302.h"
#include "./sensor/bsp_test_DS1302.h"

//#include "./crypt/bsp_crypt_aes.h"

#include "./crypt/crypt_aes.h" 
#include "./crypt/bsp_encode.h"

#include "./service/PowerDownFun.h"



/**
  * @brief  切换采集通道channel for collection
  * @param  *i 当前通道第几个的状态地址  *openstate 1开启轮训转换采集 0 关闭所有通道
  * @retval 无
  */


//FE 0A


 void segger_outfun(uint8_t * tmp,uint16_t retlen){

SYSTEM_INFO("implement segger_outfun function.\r\n");

//	 SYSTEM_DEBUG("----%d,%d,%d,%d",tmp[2],tmp[3],tmp[4],tmp[5]);
	 		switch(tmp[1]){

      case 01:IWDG_Config_nms(EM_iwd_1000ms);SYSTEM_DEBUG("EM_iwd_1000ms");break;
				
			case 02:IWDG_Config_nms(EM_iwd_2000ms);SYSTEM_DEBUG("EM_iwd_2000ms");break;
			
			//case 03:IWDG_Config_nms(EM_iwd_4000ms);SYSTEM_DEBUG("EM_iwd_4000ms");break;
			case 03:DS1302_TEST_set();break;
			case 04:DS1302_TEST_get();break;
				
			//case 04:SuspendTaskHandler(&Handle_FeedIWatchDog);SYSTEM_DEBUG("SuspendTaskHandler_Handle_FeedIWatchDog");break;
			
			case 05:IWDG_Config_nms(EM_iwd_4000ms);SYSTEM_DEBUG("EM_iwd_4000ms");break;				
			case 06:ResumeTaskHandler(&Handle_FeedIWatchDog);SYSTEM_DEBUG("ResumeTaskHandler_Handle_FeedIWatchDog");break;	
				
				
			case 07:SD_BeginSave_Fun();break;
			//case 0x08:sd_usart_cmd_SetData( "串充","03:59:55",1234, 34567, 1);break;
 			case 0x08:SYSTEM_DEBUG("AES_test");I2C_ReadTest(256) ;break;
			case 0x09: showChipID();break;
			case 0x0a: cmpAndSaveChipData();break;
			case 0x0b: SaveSYS_SettingEEpromData();break;
			
			case 0x11: SYSTEM_DEBUG("SD_BeginSave_Fun 0");SD_BeginSave_Fun();SYSTEM_DEBUG("SD_BeginSave_Fun");break;
			case 0x12: SYSTEM_DEBUG("SD_STOP_Fun 0");SD_STOP_Fun();SYSTEM_DEBUG("SD_STOP_Fun");break;
//			case 0x12: SYSTEM_DEBUG("CheckOverDateChipData 0");CheckOverDateChipData();SYSTEM_DEBUG("CheckOverDateChipData");break;
			
			case 0x13: saveEEpromChip();break;
			case 0x14: SYSTEM_DEBUG("014");ClearEEpromSaveChipData();break;
			case 0x15: SYSTEM_DEBUG("015");segger_encodedata((tmp+2),retlen-1);break;
			//DS1302_SetTime(0x00, 30, 12, 25, 12, 24);
			default:break;
		}
	 
	 

}




















/*********************************************END OF FILE**********************/
