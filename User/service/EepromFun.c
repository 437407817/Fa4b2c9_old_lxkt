#include "./service/EepromFun.h"

#include "./sys/bsp_systime.h"   


#include "./GV_variable.h"

#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./i2c/hard_i2c/bsp_iic.h"
#include "./i2c/hard_i2c/bsp_i2c_ee.h"
#include "./test/bsp_test_iic.h" 
#include "./i2c/factory_iic.h"


extern str_EEpromSettingState TMP_EEpromSettingState;
extern str_EEprom_SYS_SettingDataState TMP_EEprom_SYS_SettingState;
extern str_ChipEncode GV_EEpromChipEncode;
extern str_PowerDownState GV_PowerDownState;

//#define  EEP_PageAddress_01      0x0000
//#define  EEP_PageAddress_02      0x0200
//#define  EEP_PageAddress_03      0x0220
//#define  EEP_PageAddress_04      0x0240

uint8_t* tmpPtr;
/**
  * @brief  保存eeprom数据
  * @param  SYSState_Item_t获取版号 BatterySetTargetStateItem_t获取保存信息
  * @retval 无
  */
uint8_t SaveBoardSettingEEpromData(void){

		 tmpPtr= (uint8_t*)&TMP_EEpromSettingState.EEP_Bat_SingleBattRun;
	return	SaveEEpromDataFun(&tmpPtr ,sizeof(TMP_EEpromSettingState) ,  EEP_PageAddress_01);
	
	
	#if 0
uint16_t size_ee = sizeof(TMP_EEpromSettingState);
//uint16_t size_ee = 208;		
uint16_t size_ee02 = size_ee;
uint8_t I2c_Buf_Write[size_ee];
uint8_t 	I2c_Buf_Read[size_ee];
	//TMP_EEpromSettingState.EEP_Bat_SingleBattRun
memcpy(&I2c_Buf_Write,&TMP_EEpromSettingState.EEP_Bat_SingleBattRun,size_ee);//Heap_Size       EQU     0x00000400  否则存储失败
	//SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)TMP_EEpromSettingState.EEP_Bat_SingleBattRun,size_ee,"  TMP_EEpromSettingState  9999  =????? ");
	
	SYSTEM_ERROR("\n ********** SaveBoardSettingEEpromData**********%d\n",size_ee);
	
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Write,size_ee,"  I2c_Buf_Write  =????? ");
 EEPROM_WriteBuffer( I2c_Buf_Write, EEP_PageAddress_01, size_ee);
//	  sEE_WriteBuffer( I2c_Buf_Write, EEP_PageAddress_01, size_ee);
	//EE_soft_WriteBytes(I2c_Buf_Write,  EEP_PageAddress_01,  size_ee);

Delay(100);
	
	size_ee02 = size_ee;
EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_01, size_ee02);	
	
//sEE_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_01, (uint16_t *)(&size_ee02));
	
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,size_ee,"  I2c_Buf_Read  =????? ");
	for (uint8_t i=0; i<size_ee; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			
			SYSTEM_ERROR("\n **********EEprom error**********\n");
		return 1;
		}
   
	}


//GV_HardwareState.BatteryChargerParallel_R1A_S2A=(uint8_t)GV_EEprom.Battery_SET_R1A_S2A;
		return 0;
		
		
		#endif
}



/**
  * @brief  读取eeprom数据
  * @param  SYSState_Item_t获取版号 BatterySetTargetStateItem_t获取保存信息
  * @retval 无
  */
void GetBoardSettingEEpromData(void){

	

				tmpPtr = (uint8_t*)&TMP_EEpromSettingState.EEP_Bat_SingleBattRun;
		ReadEEpromDataFun(&tmpPtr ,sizeof(TMP_EEpromSettingState) ,  EEP_PageAddress_01);
	


		#if 0
//uint8_t size_ee = sizeof(BatterySetTargetStateItem_t);
	
volatile uint8_t size_ee = sizeof(TMP_EEpromSettingState);
	uint8_t size_ee02 = size_ee;
	
uint8_t 	I2c_Buf_Read[size_ee];
EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_01, size_ee02);
	
//	sEE_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_01, (uint16_t *)(&size_ee02));
//EE_soft_ReadBytes(I2c_Buf_Read, EEP_PageAddress_01, size_ee02);
memcpy(&TMP_EEpromSettingState.EEP_Bat_SingleBattRun,&I2c_Buf_Read,size_ee);	

//	GV_HardwareState.BatteryChargerParallel_R1A_S2A=(uint8_t)GV_EEprom.Battery_SET_R1A_S2A;
	
	SYSTEM_DEBUG("\n **********EEprom r**********%d\n",size_ee);
//	pp=&GV_EEprom.Battery_SET_SumlimitValue;
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,size_ee,"  *********** =????? ");

	#endif
	
	

}





/**
  * @brief  保存eeprom数据,timedate
  * @param  SYSState_Item_t获取版号 BatterySetTargetStateItem_t获取保存信息
  * @retval 无
  */
uint8_t SaveSYS_SettingEEpromData(void){

			 tmpPtr= (uint8_t*)&TMP_EEprom_SYS_SettingState.EEP_DS_save_hour;
	return	SaveEEpromDataFun(&tmpPtr ,EEPROM_SYS_SettingSaveDataCount ,  EEP_PageAddress_02);
	
	
	#if 0

uint16_t size_ee = EEPROM_SYS_SettingSaveDataCount;
		
uint16_t size_ee02 = size_ee;
uint8_t I2c_Buf_Write[EEPROM_SYS_SettingSaveDataCount];
uint8_t 	I2c_Buf_Read[EEPROM_SYS_SettingSaveDataCount];
	
memcpy(&I2c_Buf_Write,&TMP_EEprom_SYS_SettingState.EEP_DS_save_hour,EEPROM_SYS_SettingSaveDataCount);
	
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Write,size_ee,"  I2c_Buf_Write  =????? ");
EEPROM_WriteBuffer( I2c_Buf_Write, EEP_PageAddress_02, size_ee);

Delay(100);
	
	size_ee02 = size_ee;
//sEE_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_02, (uint16_t *)(&size_ee02));
	EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_02, size_ee02);
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,size_ee,"  I2c_Buf_Read  =????? ");
	for (uint8_t i=0; i<size_ee; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			
			SYSTEM_ERROR("\n **********EEprom error**********\n");
		return 1;
		}
   
	}


//GV_HardwareState.BatteryChargerParallel_R1A_S2A=(uint8_t)GV_EEprom.Battery_SET_R1A_S2A;
		return 0;
		
		#endif
}



void GetSYS_SettingEEpromData(void){

	
				tmpPtr = (uint8_t*)&TMP_EEprom_SYS_SettingState.EEP_DS_save_hour;
		ReadEEpromDataFun(&tmpPtr ,EEPROM_SYS_SettingSaveDataCount ,  EEP_PageAddress_02);
	

	#if 0
	
//uint8_t size_ee = sizeof(BatterySetTargetStateItem_t);
	
volatile uint8_t size_ee = EEPROM_SYS_SettingSaveDataCount;
	uint8_t size_ee02 = size_ee;
	
uint8_t 	I2c_Buf_Read[size_ee];
//sEE_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_02, (uint16_t *)(&size_ee02));
EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_02, size_ee02);
memcpy(&TMP_EEprom_SYS_SettingState.EEP_DS_save_hour,&I2c_Buf_Read,size_ee);	

//	GV_HardwareState.BatteryChargerParallel_R1A_S2A=(uint8_t)GV_EEprom.Battery_SET_R1A_S2A;
	
	SYSTEM_DEBUG("\n **********EEprom r**********%d\n",size_ee);
//	pp=&GV_EEprom.Battery_SET_SumlimitValue;
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,size_ee,"  sys_time_=== ");

	#endif
	
	

}



uint8_t SavePowerDownData(void){

				 tmpPtr= (uint8_t*)&GV_PowerDownState.PowerDown_State;
	return	SaveEEpromDataFun(&tmpPtr ,10 ,  EEP_PageAddress_03);
	
	
	#if 0

	
uint16_t size_ee = 10;
	uint16_t size_ee02 = size_ee;
uint8_t  I2c_Buf_Write[size_ee];
uint8_t 	I2c_Buf_Read[size_ee];
//	GV_PowerDownState.PowerDown_State=1;
memcpy(&I2c_Buf_Write,&GV_PowerDownState.PowerDown_State,10);	
EEPROM_WriteBuffer( I2c_Buf_Write, EEP_PageAddress_03, size_ee);


return 0;
	#endif
}

void GetPowerDownData(void){

	
					tmpPtr = (uint8_t*)&GV_PowerDownState.PowerDown_State;
		ReadEEpromDataFun(&tmpPtr ,10 ,  EEP_PageAddress_03);
	
	
	#if 0
volatile uint8_t size_ee = 10;
	uint8_t size_ee02 = size_ee;
	
uint8_t 	I2c_Buf_Read[size_ee];

EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_03, size_ee02);
memcpy(&GV_PowerDownState.PowerDown_State,&I2c_Buf_Read,size_ee);	

#endif


}


















extern str_ChipEncode GV_EEpromChipEncode;
extern str_ChipEncode GV_SaveEEpChipEncode;



uint8_t SaveChipEncodeEEpromData(void){

uint16_t size_ee = 16;
	uint16_t size_ee02 = size_ee;
uint8_t  I2c_Buf_Write[size_ee];
uint8_t 	I2c_Buf_Read[size_ee];
	
memcpy(&I2c_Buf_Write,&GV_SaveEEpChipEncode.code,size_ee);	
EEPROM_WriteBuffer( I2c_Buf_Write, EEP_PageAddress_03, size_ee);

Delay(100);
	
	size_ee02 = size_ee;
EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_03, size_ee02);	
	
//sEE_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_01, (uint16_t *)(&size_ee02));
	
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,size_ee,"  I2c_Buf_Read  =????? ");
	for (uint8_t i=0; i<size_ee; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			
			SYSTEM_ERROR("\n SaveChipEncodeEEpromData error\n");
		return 1;
		}
   
	}

return 0;

}



uint8_t GetChipEncodeEEpromData(void){

uint16_t size_ee = 16;

uint8_t 	I2c_Buf_Read[size_ee];
	
	

	

EEPROM_ReadBuffer(I2c_Buf_Read, EEP_PageAddress_03, size_ee);	

memcpy(&GV_EEpromChipEncode.code,&I2c_Buf_Read,size_ee);	

	SYSTEM_DEBUG_ARRAY_MESSAGE_HorA(0,(uint8_t *)GV_EEpromChipEncode.code,size_ee,"  GetChipEncodeEEpromData=== ");

return 0;


}


















/*********************************************END OF FILE**********************/
