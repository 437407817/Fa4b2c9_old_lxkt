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
  



#include "./sys/sys_interrupt.h"   
//#include "core_cm4.h"  // 对于 Cortex - M4 内核，其他内核类似

//******************************


int is_interrupt_disabled(void) {
    uint32_t primask = __get_PRIMASK();
    return (primask != 0);
}


int is_faultmask_active(void) {
    uint32_t faultmask = __get_FAULTMASK();
    return (faultmask != 0);
}






// 软件复位函数
void Software_Reset(void) {
	
    // 强制复位AHB1总线上的所有外设
    RCC->AHB1RSTR = 0xFFFFFFFF;
    __asm("nop"); // 确保复位信号稳定
    RCC->AHB1RSTR = 0x00000000;
    
    // 触发系统软件复位
    __asm("dsb"); // 数据同步屏障
    SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos) | 
                 SCB_AIRCR_SYSRESETREQ_Msk;
    __asm("dsb"); // 确保写操作完成
    
    // 等待复位生效
    while(1);
}









/*********************************************END OF FILE**********************/
