/**
  ******************************************************************************
  * @file    bsp_random.c
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
  
#include "./sys/bsp_random.h" 
#include "./sys/sysio.h"
 
//******************************

void RNG_Random_Init(void){


	/* 使能RNG时钟 */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	
	/* 使能RNG外设 */
  RNG_Cmd(ENABLE);

}

uint8_t RNG_Random_0_9(void){
	uint8_t random = 0;
	 while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
  {
  }
		      random = RNG_GetRandomNumber()%10;	
	//SYSTEM_INFO("\r\nRNG 产生的随机数：%d",random);
	return random;
}


uint16_t RNG_Random_0_9999(void){
	uint16_t random = 0;
	 while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
  {
  }
		      random = RNG_GetRandomNumber()%10000;	
	//SYSTEM_INFO("\r\nRNG 产生的随机数：%d",random);
		return random;
}


//RNG_Random_setArray((uint16_t *)&devData, sizeof(devData) / sizeof(uint16_t), 0, 0xFFFF);
// 或者写成：sizeof(devData) / 2
void RNG_Random_setArray(uint16_t *array,uint16_t arraycount,uint16_t min,uint16_t max){

	
	for(uint16_t i=0;i<arraycount;i++){
		 while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
	array[i]=min+(RNG_GetRandomNumber() % (max - min + 1));	
		
	};
	

		      
	//SYSTEM_INFO("\r\nRNG 产生的随机数：%d",random);
	
	
	
		//return random;
}





uint16_t Simple_Random(uint16_t min,uint16_t max){


    return  min+(rand() % (max - min + 1));


}


void Simple_Random_setArray(uint16_t *array,uint16_t arraycount,uint16_t min,uint16_t max){

	for(uint16_t i=0;i<arraycount;i++){
		array[i]=Simple_Random( min, max);
	};
	
}














void RNG_Random_Test(void){

	uint32_t random = 0;
		for(uint8_t i = 0; i < 8; i++)
    {
      /* 等待随机数产生完毕 */
      while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
      {
      }

      /*获取随机数*/       
      random = RNG_GetRandomNumber();
			SYSTEM_INFO("\r\nRNG 产生的随机数：0x%08x",random);
			

    }

	}
/*********************************************END OF FILE**********************/
