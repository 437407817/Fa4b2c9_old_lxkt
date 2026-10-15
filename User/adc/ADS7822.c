#include "./adc/ADS7822.h"

#include "./sys/bsp_systime.h"   



#include "./sys/sysio.h"
#include "./TM/tm_stm32f4_gpio.h"


#ifdef ADCx_DMA_ENABLE 

__IO uint16_t ADC_ConvertedValue;

#endif










static void ADS7822_Config(void)
{
	
	#if 1
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd( ADS7822_CS_GPIO_Clk|ADS7822_CLK_GPIO_Clk|ADS7822_OUT_GPIO_Clk, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = ADS7822_CS_GPIO_Pin;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

	    /*设置引脚为不上拉也不下拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(ADS7822_CS_GPIO_Port, &GPIO_InitStructure);	
	
				/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = ADS7822_CLK_GPIO_Pin;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(ADS7822_CLK_GPIO_Port, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
		GPIO_InitStructure.GPIO_Pin = ADS7822_OUT_GPIO_Pin;
		GPIO_Init(ADS7822_OUT_GPIO_Port, &GPIO_InitStructure);

#else



			
			
		TM_GPIO_Init(ADS7822_CS_GPIO_Port, ADS7822_CS_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
		TM_GPIO_Init(ADS7822_CLK_GPIO_Port, ADS7822_CLK_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
		TM_GPIO_Init(ADS7822_OUT_GPIO_Port, ADS7822_OUT_GPIO_Pin, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
			//TM_GPIO_SetPinLow(ADS7822_CS_GPIO_Port, ADS7822_CS_GPIO_Pin);
			//TM_GPIO_SetPinLow(ADS7822_CLK_GPIO_Port, ADS7822_CLK_GPIO_Pin);
			//GPIO_SetBits(ADS7822_CLK_GPIO_Port,ADS7822_CLK_GPIO_Pin);
#endif				
			ADS7822_CS_H;ADS7822_SCK_L;//这样设置，第一个周期就采集到数据，不用等第二次采集
			
}




uint16_t ADS7822_CatchVolBit(void){
uint16_t ADS7822_byte=0;
uint16_t ADS7822_Vbit=0;	

ADS7822_CS_L;
delay_us(7);
	
for(uint16_t bit_ctr = 0; bit_ctr < 15 ;bit_ctr++)
{
  ADS7822_byte = (ADS7822_byte<<1);
  ADS7822_SCK_H;
	delay_us(7);
	if(ADS7822_READBIT == 1){
	ADS7822_byte|=1;
	}
	ADS7822_SCK_L;	
	delay_us(7);

}
ADS7822_CS_H;
ADS7822_Vbit = ADS7822_byte & 0x0fff;

return ADS7822_Vbit;
}


uint32_t ADS7822_VolDispose(uint16_t  ADS7822_Vbit){
#if 0
  uint32_t  ADS7822_VAL;
	ADS7822_VAL=(30*34*(uint32_t)ADS7822_Vbit)/(0x0fff);
	SYSTEM_DEBUG(" *--ADS7822_VAL=  %d  %d   ",ADS7822_VAL ,ADS7822_Vbit);
#endif	
	
	//return ((uint32_t)ADS7822_Vbit*30*34)/(0x0fff);
	return ((uint32_t)ADS7822_Vbit*30*73)/(0x0fff);
	//return ADS7822_VAL;
}


/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADS7822_Init(void)
{

	ADS7822_Config();
	
	
}
unsigned int ADS_get_value(void);


void ADS7822_Test(void)
{

	

	
	 SYSTEM_INFO("\n ADS7822 = %d  %d \n", ADS7822_CatchVolBit(),ADS7822_VolDispose(ADS7822_CatchVolBit()));
}










/*********************************************END OF FILE**********************/
