#ifndef __ADCFILTER_H
#define	__ADCFILTER_H

#include "stm32fxxx.h"




#define FDNUM 24 





typedef struct ADCfilterData_ITEM
{

uint16_t adcOldData01_Uncalibrate[FDNUM];
uint16_t adcOldData02_Uncalibrate[FDNUM];
uint16_t adcNowOutputData_Uncalibrate[FDNUM];
	

uint32_t adcSumDatatmp;		//连续采样10次的值的和临时量
uint16_t adcOutData; 
	
uint8_t adc_ChannelofTunnel;
uint16_t (*pointer)(void);
}ADCfilterData_ITEM_t;



typedef uint16_t (*P_ADCfilter)(void);

uint16_t Fun_AdcAverageNTimesfilter(P_ADCfilter fp_AdcCatchvol,uint8_t Ntimes);
uint16_t Fun_AdcmovingAverage3Timesfilter(uint16_t adcNowCatchdata,uint8_t activedChannel);
#endif







