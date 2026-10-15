/**
  ******************************************************************************
  * @file    bsp_test-can.c
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

#include "./test/bsp_test_gpio_in.h"   
#include "./io/IN_io/bsp_gpio_in.h"  
#include "./sys/sysio.h"
#include "./sys/bsp_systime.h" 


 void GPIO_In_Test(void){
 
 uint8_t	ko= GPIO_ReadInputDataBit(IOInput_GPIO_PORT,IOInput_GPIO_PIN);
	
SYSTEM_INFO("\n io  output = %d \n", ko);
Delay_Ms(3000);
	 
	 
	 
}

















//******************************





















/*********************************************END OF FILE**********************/
