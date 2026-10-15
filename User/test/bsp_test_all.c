/**
  ******************************************************************************
  * @file    bsp_test-all.c
  * @author  fire
  * @version V1.0
  * @date    2023-05-15
  * @brief   应用函数接口
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
#include "./test/bsp_test_all.h"   

#include "./test/bsp_test_iic.h"  
#include "./test/bsp_test_adc.h"  
#include "./test/bsp_test_spi.h"  
#include "./test/bsp_test_can.h" 
#include "./test/bsp_test_usart.h" 
#include "./test/bsp_test_SeggerRTT.h"  
#include "./sys/bsp_systime.h" 
#include "./sys/bsp_random.h" 
//#include "./extfun/oled/bsp_oled_test.h"
//#include "./spi/lcd/lcd_test.h"

#include "./test/bsp_test_485.h" 
#include "./test/bsp_test_gpio_out.h"  
#include "./test/bsp_test_gpio_in.h"
#include "./test/bsp_test_soft_iic.h"  
#include "./sdram/bsp_sdram.h"   
#include "./test/bsp_test_sdram.h" 

#include "./sensor/bsp_test_DS1302.h"
#include "./adc/ADS7822.h"
#include "./adc/CC6902.h"
 #include "./sys/sysio.h"
#include "./dac/DAC7311.h"
#include "./screen/ScreenDataDis.h"
#include "./i2c/soft_i2c/bsp_soft_i2c_ee.h"
//******************************

void ALLperipheral_SingleTest(void)
{
//Delay_Ms(1000);
//USART_Test();
	  
//I2C_Test();
	//EE_soft_Test(); 
//SeggerRTT_Test();	
//Soft_i2c_Test();

	
//	SDRAM_Test();
	//SRAM_Test();
//SPI_Test();
	EE_soft_Test();
	//LCD_Test();
}


void ALLperipheral_RepetitionTest(void)
{
//RNG_Random_Test();
//USART_Test();
	//OLED_Test();
 //ADC_CC6902_TEST();
USART_485_B_Test();
//	USART_485_Test();
	//test_ds1302();
		//DAC7311_Test();
	//Delay_Ms(2000);

//LCD_Test();
//GPIO_Out_Test();
//	ADS7822_Test();
//GPIO_In_Test();
//ADC_Test();
//CAN_Test();
	

	
	
	
	
}




/*********************************************END OF FILE**********************/
