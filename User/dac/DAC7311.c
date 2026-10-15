#include "./dac/DAC7311.h"

#include "./sys/bsp_systime.h"   



#include "./sys/sysio.h"
#include "./TM/tm_stm32f4_gpio.h"











static void DAC7311_Config(void)
{
	
	#if 0
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd( DAC7311_DIN_GPIO_SCLK|DAC7311_SCLK_GPIO_SCLK|DAC7311_SYNC_GPIO_SCLK, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = DAC7311_DIN_GPIO_Pin;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_SYNC;   

	    /*设置引脚为不上拉也不下拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(DAC7311_DIN_GPIO_Port, &GPIO_InitStructure);	
	
				/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = DAC7311_SCLK_GPIO_Pin;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(DAC7311_SCLK_GPIO_Port, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
		GPIO_InitStructure.GPIO_Pin = DAC7311_SYNC_GPIO_Pin;
		GPIO_Init(DAC7311_SYNC_GPIO_Port, &GPIO_InitStructure);

#else



			
			
		TM_GPIO_Init(DAC7311_DIN_GPIO_Port, DAC7311_DIN_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
		TM_GPIO_Init(DAC7311_SCLK_GPIO_Port, DAC7311_SCLK_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
		TM_GPIO_Init(DAC7311_SYNC_GPIO_Port, DAC7311_SYNC_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
			//TM_GPIO_SetPinLow(DAC7311_DIN_GPIO_Port, DAC7311_DIN_GPIO_Pin);
			//TM_GPIO_SetPinLow(DAC7311_SCLK_GPIO_Port, DAC7311_SCLK_GPIO_Pin);
			//GPIO_SetBits(DAC7311_SCLK_GPIO_Port,DAC7311_SCLK_GPIO_Pin);
#endif				
			//DAC7311_DIN_H;DAC7311_SCK_L;//这样设置，第一个周期就采集到数据，不用等第二次采集
			DAC7311_SYNC_H;DAC7311_SCLK_L;
			
}




void DAC7311_WriteData(uint16_t Data){
	uint16_t temp;
	uint8_t	ui;
	
	temp=Data << 2;//7311需要移两位
	temp &= 0x3FFF;//选择模式为Normal
	DAC7311_SYNC_H;
	DAC7311_SCLK_H;
	delay_us(10);
	DAC7311_SYNC_L;//使能输入移位寄存器
	delay_us(10);
	
	for(ui=0; ui<16; ui++)
	{
		
		DAC7311_SCLK_H;
		
		if(0x8000 == (temp & 0x8000))
		{
			DAC7311_DIN_H;
		}
		else
		{
			DAC7311_DIN_L;
		}
		delay_us(10);
		DAC7311_SCLK_L;
		delay_us(10);
		temp <<=1;
	}
	
	DAC7311_SYNC_H;



}

/**
  * @brief  ADC
  * @param  无
  * @retval 外接2倍放大电路
  */
uint32_t DAC7311_VolDispose_mv(uint16_t  DAC7311_Vbit){
#if 0
  uint32_t  DAC7311_VAL;
	DAC7311_VAL=(30*34*(uint32_t)DAC7311_Vbit)/(0x0fff);
	SYSTEM_DEBUG(" *--DAC7311_VAL=  %d  %d   ",DAC7311_VAL ,DAC7311_Vbit);
#endif	
	DAC7311_WriteData(DAC7311_Vbit/2);
	//return ((uint32_t)DAC7311_Vbit*30*34)/(0x0fff);
	return (((uint32_t)DAC7311_Vbit*3000*2)/(0x07ff));
	//return DAC7311_VAL;
}


/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void DAC7311_Init(void)
{

	DAC7311_Config();
	
	
}



void DAC7311_Test(void)
{

	static uint16_t it=0;
  it+=10;
	
	 SYSTEM_INFO("\n DAC7311 = 0x%x ==%d\n", it,DAC7311_VolDispose_mv(it));
	
}










/*********************************************END OF FILE**********************/
