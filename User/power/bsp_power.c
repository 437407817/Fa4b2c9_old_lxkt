 /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi  底层应用函数bsp 
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./power/bsp_power.h"
#include "stm32f4xx_pwr.h"
 #include "./sys/sysio.h"
#include "./service/EepromFun.h"




/**
  * @brief  配置PVD.电压监控模式
  * @param  None
  * @retval None
  */




// 配置电压监控模式
void Init_Voltage_Monitoring_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  /*使能 PWR 时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 使能 PVD 中断 */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
      
  /* 配置 EXTI16线(PVD 输出) 来产生上升下降沿中断*/
  EXTI_ClearITPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* 配置PVD级别5 (PVD检测电压的阈值为2.8V，VDD电压低于2.8V时产生PVD中断，具体数据可查询数据手册获知) */
	/*具体级别根据自己的实际应用要求配置*/
  PWR_PVDLevelConfig(PWR_PVDLevel_5);

  /* 使能PVD输出 */
//  PWR_PVDCmd(ENABLE);
}


void enable_pwr(void){

PWR_PVDCmd(ENABLE);
//NVIC_EnableIRQ(PVD_IRQn);
}


void disable_pwr(void){
SYSTEM_INFO(" ==disable_pwr== \n");
PWR_PVDCmd(DISABLE);
//NVIC_DisableIRQ(PVD_IRQn);
}




extern str_PowerDownState GV_PowerDownState;




void PVD_IRQHandler(void)
{
		/*检测是否产生了PVD警告信号*/
		if(PWR_GetFlagStatus (PWR_FLAG_PVDO)==SET)			
		{
			/* 亮红灯，实际应用中应进入紧急状态处理 */
					GV_PowerDownState.PowerDown_State=1;
					SavePowerDownData();
			
		}
    /* 清除中断信号*/
    EXTI_ClearITPendingBit(EXTI_Line16);

}


   
/*********************************************END OF FILE**********************/




