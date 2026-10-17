/**
  ******************************************************************************
  * @file    bsp_util_time.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./sys/sys_init_all.h" 
#include "./usart/bsp_usart.h"  
#include "./adc/bsp_adc.h"
#include "./i2c/hard_i2c/bsp_i2c_ee.h"
#include "./i2c/hard_i2c/bsp_iic.h"
#include "./sys/bsp_systime.h" 
#include "./test/bsp_test_all.h"  
#include "./spi/flash/bsp_spi_flash.h"
#include "./can/bsp_can.h"
#include "./SeggerRTT/SEGGER_RTT.h"
#include "./io/IN_io/bsp_gpio_in.h"
#include "./io/OUT_io/bsp_gpio_out.h" 
#include "./sdram/bsp_sdram.h" 
 #include "./sys/bsp_random.h" 
 #include "./usart/bsp_485_usart.h"


#include "./controller/MainWorkFun.h"
 #include "./sensor/DS1302.h"
 #include "./adc/ADS7822.h"
 #include "./adc/CC6902.h"
 #include "./dac/DAC7311.h"
 #include "./GV_variable.h" 
 
 #include "./usart/bsp_usart_sd.h"
 #include "./controller/TaskFun.h"

 #include "./sys/systick.h"
 
 #include "./i2c/soft_i2c/bsp_soft_i2c_gpio.h"
 
 #include "./i2c/soft_i2c/bsp_soft_i2c_ee.h"
 #include "./defines.h"
  #include "./system_config.h"
	#include "./iwdg/bsp_iwdg.h"   
	
	#include "./i2c/factory_iic.h"
#include "./power/bsp_power.h"	
	#include "./usart/usart485verify.h"

//******************************





void Init_ALL_cfg(void){
SystickInit();	
	
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);


Delay(5000);
	
USART_All_Config();
USART_485_A_Config();
	Usart485ComAppInit();
	USART_485_B_Config();
//IN_Io_ALL_GPIO_Config();
	
	IN_Io_ALL_GPIO_Config();
	
	RNG_Random_Init();
	
	OUT_Io_GPIO_Config();
	
	
	#if(USE_EEPROM_soft0_or_Hard1==1)
	I2C_HardEE_Init();
	#else
//	i2c_Soft_CfgGpio();
	#endif
	IIC_EE_Factory_Init();
	
DS1302_GPIO_Init();
//IIC_ConfigInit();	

	//EE_soft_Test();
//SPI_ALL_Init();	
	
//OUT_Io_GPIO_Config();	
CANx_config_Init();
////	LCD_Init();
//CAN_Config_Init();	
SEGGER_RTT_Init();
Init_Voltage_Monitoring_Config();
SYSTEM_DEBUG("SEGGER_RTT_Init over------------- ");
//		SDRAM_Init();
//	OLED_Init();
//ADCx_Init();
//ADC_CC6902_Init();
//	ADS7822_Init();

//DAC7311_Init();
//SYSTEM_DEBUG("iic over------------- ");

 AppTaskScheduleInit();
 
 
 //IWDG_Config_nms(EM_iwd_4000ms);
Delay(100);

}


void Need_SingleTest_Pro(void){
	

	initGV_variable();

	
	ALLperipheral_SingleWork();
	
	

 // ALLperipheral_SingleTest();
IWDG_Feed();
}




void Need_RepetitionTest_Pro(void){

	
  //ALLperipheral_RepetitionTest();
	//ALLperipheral_RepetitionWork();
	//SYSTEM_DEBUG("TaskHandler------------- ");
	AppTaskCb();
	TaskHandler();



}






/*********************************************END OF FILE**********************/
