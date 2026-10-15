/**
  ******************************************************************************
  * @file    data_convert.c
  * @author  fire
  * @version V1.0
  * @date    2024-03-11
  * @brief   can驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103-霸道 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./converter/ADCfilter.h"
//#include "./usart/bsp_usart.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "./sys/bsp_systime.h"   

#include "./converter/data_sort.h"
#include "./sys/sysio.h"
/*
*********************************************************************************************************
*	函 数 名: power
*	功能说明: 求n的k次方
*	形    参：n底  k次方
*	返 回 值: 
*********************************************************************************************************
*/

//函数指针
//int (*fun)(int x,int y);

//https://blog.csdn.net/pl0020/article/details/131322442
//https://blog.csdn.net/m0_46577050/article/details/122310716
//https://zhuanlan.zhihu.com/p/644281252

//typedef uint16_t (*P_ADCfilter)(void);


ADCfilterData_ITEM_t  GV_ADCfilterData={.adcSumDatatmp=0,.pointer=NULL};




//typedef uint16_t (*pointer)(void);



/**
  * @brief  Get the output average value of measurements for n times    算术平均滤波法侧重于平滑信号，减小噪声和波动。
  * @param  pf_Adc: function pointer.
  * @param  Ntimes: times of measure.
  * @retval average value of output.
  */
uint16_t Fun_AdcAverageNTimesfilter(P_ADCfilter fp_AdcCatchvol,uint8_t Ntimes){
uint16_t adcCatchvoltmp=0;
	GV_ADCfilterData.adcSumDatatmp=0;
	
	for(uint8_t i=0;i<Ntimes;i++){
	//GV_ADCfilterData.adcSumDatatmp+=(*fp_AdcCatchvol)();
		adcCatchvoltmp=fp_AdcCatchvol();
		GV_ADCfilterData.adcSumDatatmp+=adcCatchvoltmp;
		//VOFA_Chart_OneCurve_d(adcCatchvoltmp);
		//GV_ADCfilterData.adcSumDatatmp+=fp_AdcCatchvol();
		
		
				//delay_us(50);
	}
	GV_ADCfilterData.adcOutData=GV_ADCfilterData.adcSumDatatmp/Ntimes;

//GV_ADCfilterData.pointer=	fp_AdcCatchvol;
//	(*(GV_ADCfilterData.pointer))();
//	(*(fp_AdcCatchvol))();	
	
	return GV_ADCfilterData.adcOutData;

	
}




/**
  * @brief  Get the output moving Average value of measure for 3 times    
  * @param  adcNowCatchdata: Get value now.
  * @param  activedChannel: which actived channel.
  * @retval the value of output.
  */
uint16_t Fun_AdcmovingAverage3Timesfilter(uint16_t adcNowCatchdata,uint8_t activedChannel){
GV_ADCfilterData.adc_ChannelofTunnel=activedChannel;
GV_ADCfilterData.adcNowOutputData_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]=(uint16_t)(((uint32_t)GV_ADCfilterData.adcOldData01_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]
	+(uint32_t)GV_ADCfilterData.adcOldData02_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]+(uint32_t)adcNowCatchdata)/3);
GV_ADCfilterData.adcOldData02_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]=GV_ADCfilterData.adcOldData01_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel];//最快适中
GV_ADCfilterData.adcOldData01_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]=(uint16_t)adcNowCatchdata;
	
return GV_ADCfilterData.adcNowOutputData_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel];
}



//一阶滞后滤波算法  一阶滞后滤波法侧重于快速响应信号的变化，较快地跟踪信号的动态变化。
uint16_t Fun_FirstOrderHysteresisFilter(uint16_t adcNowCatchdata,uint8_t activedChannel,uint8_t ax){
	assert_param((ax>=0)&&(ax<=100));
GV_ADCfilterData.adc_ChannelofTunnel=activedChannel;
	
GV_ADCfilterData.adcNowOutputData_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]=((uint32_t)GV_ADCfilterData.adcOldData01_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]*ax+(uint32_t)adcNowCatchdata*(100-ax))/100;
	GV_ADCfilterData.adcOldData01_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel]=(uint16_t)adcNowCatchdata;
return GV_ADCfilterData.adcNowOutputData_Uncalibrate[GV_ADCfilterData.adc_ChannelofTunnel];
}



//初始化一个长度为 n 的数组，将输入的采样值存入数组中。对数组进行排序，可以使用冒泡排序等方法。输出排序后的数组中的中间值，即中位数。
void aaa(P_ADCfilter pfilter,uint8_t i){





}










/**************************END OF FILE************************************/











