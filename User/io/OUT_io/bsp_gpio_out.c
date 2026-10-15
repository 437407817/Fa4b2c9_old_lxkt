/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F429-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "./io/OUT_io/bsp_gpio_out.h"   
#include "./TM/tm_stm32f4_gpio.h"



GPIO_TypeDef * RelayChargePort[8] = {	RelayCharge_GPIO_Port_01, RelayCharge_GPIO_Port_02, RelayCharge_GPIO_Port_03, RelayCharge_GPIO_Port_04, \
						RelayCharge_GPIO_Port_05, RelayCharge_GPIO_Port_06, RelayCharge_GPIO_Port_07, RelayCharge_GPIO_Port_08 };

uint16_t RelayChargePin[8] = {	RelayCharge_GPIO_Pin_01, RelayCharge_GPIO_Pin_02, RelayCharge_GPIO_Pin_03, RelayCharge_GPIO_Pin_04, \
						RelayCharge_GPIO_Pin_05, RelayCharge_GPIO_Pin_06, RelayCharge_GPIO_Pin_07, RelayCharge_GPIO_Pin_08};



GPIO_TypeDef * RelayGatePort[9] = {	RelayGate_GPIO_Port_01, RelayGate_GPIO_Port_02, RelayGate_GPIO_Port_03, RelayGate_GPIO_Port_04, \
						RelayGate_GPIO_Port_05, RelayGate_GPIO_Port_06, RelayGate_GPIO_Port_07, RelayGate_GPIO_Port_08, RelayGate_GPIO_Port_09};

uint16_t RelayGatePin[9] = {	RelayGate_GPIO_Pin_01, RelayGate_GPIO_Pin_02, RelayGate_GPIO_Pin_03, RelayGate_GPIO_Pin_04, \
						RelayGate_GPIO_Pin_05, RelayGate_GPIO_Pin_06, RelayGate_GPIO_Pin_07, RelayGate_GPIO_Pin_08, RelayGate_GPIO_Pin_09};




						
uint8_t  RelayBitState8 = 0x00 ;   //8


						
void TurnOnOffAllRelayGPIO(GPIO_TypeDef** RelayXXXPort,uint16_t* RelayXXXPin,uint8_t num,BitAction BitVal){

	for(uint8_t i=0;i<num;i++){
GPIO_WriteBit(RelayXXXPort[i],RelayXXXPin[i],BitVal);
	}
}	
	






 /**
  * @brief  通过0bxxxxxxxxx状态判断开启关闭Relay的IO，如果引脚高电平代表关闭，低电平代表开启，需要把onstate==1改成onstate==0
  * @param  OnOffBit
  * @retval 无
  */
void TurnOnOffRelayByBit08(GPIO_TypeDef** RelayXXXPort,uint16_t* RelayXXXPin,uint8_t OnOffBit){
	uint8_t onstate;
for(uint8_t i=0;i<8;i++){
	
onstate = (OnOffBit>>i)&(0x0001);
	
if(onstate == 1){
GPIO_SetBits(RelayXXXPort[i],RelayXXXPin[i]);
}else{
GPIO_ResetBits(RelayXXXPort[i],RelayXXXPin[i]);
}
}

}











 




 /**
  * @brief  初始化控制Relay的IO
  * @param  无
  * @retval 无
  */
void RelayCharge_GPIO_Config(void)
{		
	
	#if 0
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RelayCharge_GPIO_Clk_01 | RelayCharge_GPIO_Clk_02 | RelayCharge_GPIO_Clk_03, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_01;	

		/*设置引脚模式为输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
     /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCharge_GPIO_Port_01, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_02;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCharge_GPIO_Port_02, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_03;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCharge_GPIO_Port_03, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_04;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCharge_GPIO_Port_04, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_05;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCharge_GPIO_Port_05, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_06;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCharge_GPIO_Port_06, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_07;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCharge_GPIO_Port_07, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCharge_GPIO_Pin_08;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCharge_GPIO_Port_08, &GPIO_InitStructure);


		GPIO_SetBits(RelayCharge_GPIO_Port_01, RelayCharge_GPIO_Pin_01);
		GPIO_SetBits(RelayCharge_GPIO_Port_02, RelayCharge_GPIO_Pin_02);
		GPIO_SetBits(RelayCharge_GPIO_Port_03, RelayCharge_GPIO_Pin_03);
		GPIO_SetBits(RelayCharge_GPIO_Port_04, RelayCharge_GPIO_Pin_04);	
		GPIO_SetBits(RelayCharge_GPIO_Port_05, RelayCharge_GPIO_Pin_05);
		GPIO_SetBits(RelayCharge_GPIO_Port_06, RelayCharge_GPIO_Pin_06);	
		GPIO_SetBits(RelayCharge_GPIO_Port_07, RelayCharge_GPIO_Pin_07);	
		GPIO_SetBits(RelayCharge_GPIO_Port_08, RelayCharge_GPIO_Pin_08);

		GPIO_ResetBits(RelayCharge_GPIO_Port_01, RelayCharge_GPIO_Pin_01);
		GPIO_ResetBits(RelayCharge_GPIO_Port_02, RelayCharge_GPIO_Pin_02);
		GPIO_ResetBits(RelayCharge_GPIO_Port_03, RelayCharge_GPIO_Pin_03);
		GPIO_ResetBits(RelayCharge_GPIO_Port_04, RelayCharge_GPIO_Pin_04);	
		GPIO_ResetBits(RelayCharge_GPIO_Port_05, RelayCharge_GPIO_Pin_05);
		GPIO_ResetBits(RelayCharge_GPIO_Port_06, RelayCharge_GPIO_Pin_06);	
		GPIO_ResetBits(RelayCharge_GPIO_Port_07, RelayCharge_GPIO_Pin_07);	
		GPIO_ResetBits(RelayCharge_GPIO_Port_08, RelayCharge_GPIO_Pin_08);


#endif
















}




#if 0
typedef struct
{
	GPIO_TypeDef* gpio;
	uint32_t pin;
} TMI_GPIO_t;

static TMI_GPIO_t RE_gpioList[] = 
{
	{ TM_RE_1_PORT, TM_RE_1_PINS},  // key1
	{ TM_RE_2_PORT, TM_RE_2_PINS}, // key2
	{ TM_RE_3_PORT, TM_RE_3_PINS},  // key3
	{ TM_RE_4_PORT, TM_RE_4_PINS}  // key3
};


#define RE_NUM_MAX (sizeof(RE_gpioList) / sizeof(RE_gpioList[0]))


/**
***********************************************************
* @brief RE_GPIO硬件初始化
* @param
* @return 
***********************************************************
*/
void RE_GPIO_DrvInit(void)
{
	for (uint8_t i = 0; i < RE_NUM_MAX; i++)
	{
    TM_GPIO_Init(RE_gpioList[i].gpio, RE_gpioList[i].pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
		TM_GPIO_SetPinLow(RE_gpioList[i].gpio, RE_gpioList[i].pin);
		
	}
}



#endif


void TM_OUT_RE_Init(void) {
	
	
	
	
	
    /* Set pins as output */
    TM_GPIO_Init(TM_RE_1_PORT, TM_RE_1_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	  
    TM_GPIO_Init(TM_RE_2_PORT, TM_RE_2_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	  TM_GPIO_Init(TM_RE_3_PORT, TM_RE_3_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
    TM_GPIO_Init(TM_RE_4_PORT, TM_RE_4_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);	
    /* Turn leds off */
    TM_RE_1_OFF;
	TM_RE_2_OFF;
	TM_RE_3_OFF;
	TM_RE_4_OFF;
	
	
}


void TM_OUT_SE_Init(void) {
    /* Set pins as output */
    TM_GPIO_Init(TM_SE_1_PORT, TM_SE_1_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	  
    TM_GPIO_Init(TM_SE_2_PORT, TM_SE_2_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	  TM_GPIO_Init(TM_SE_3_PORT, TM_SE_3_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
    TM_GPIO_Init(TM_SE_4_PORT, TM_SE_4_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);	
	  TM_GPIO_Init(TM_SE_5_PORT, TM_SE_5_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);	
    /* Turn leds off */
    TM_SE_X_OFF(1);
    TM_SE_X_OFF(2);
    TM_SE_X_OFF(3);
    TM_SE_X_OFF(4);
    TM_SE_X_OFF(5);	
	
}


void TM_OUT_CHARGE_Init(void) {
    /* Set pins as output */
    TM_GPIO_Init(TM_CHARGE_PORT, TM_CHARGE_PINS, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	  

    TM_CHARGE_OFF;	
	
}








/**
  * @brief  初始化控制Relay的IO
  * @param  无
  * @retval 无
  */
void RelayXXA_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd( ChargeChange2A_1A_GPIO_Clk | DYGate_GPIO_Clk, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = ChargeChange2A_1A_GPIO_Pin;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(ChargeChange2A_1A_GPIO_Port, &GPIO_InitStructure);	
	
	
	
	
	   GPIO_InitStructure.GPIO_Pin = DYGate_GPIO_Pin;	
	
	   GPIO_Init(DYGate_GPIO_Port, &GPIO_InitStructure);



		
		 GPIO_SetBits(ChargeChange2A_1A_GPIO_Port, ChargeChange2A_1A_GPIO_Pin);
		
     GPIO_ResetBits(DYGate_GPIO_Port, DYGate_GPIO_Pin);
		
}





/**
  * @brief  初始化控制Relay的IO
  * @param  无
  * @retval 无
  */
void RelayCHX_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RelayCHX_GPIO_Clk_01 | RelayCHX_GPIO_Clk_02 | RelayCHX_GPIO_Clk_03, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_01;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCHX_GPIO_Port_01, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_02;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCHX_GPIO_Port_02, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_03;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCHX_GPIO_Port_03, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_04;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCHX_GPIO_Port_04, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_05;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCHX_GPIO_Port_05, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_06;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayCHX_GPIO_Port_06, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_07;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCHX_GPIO_Port_07, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayCHX_GPIO_Pin_08;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayCHX_GPIO_Port_08, &GPIO_InitStructure);


		GPIO_SetBits(RelayCHX_GPIO_Port_01, RelayCHX_GPIO_Pin_01);
		

		GPIO_SetBits(RelayCHX_GPIO_Port_02, RelayCHX_GPIO_Pin_02);
    
		
		GPIO_SetBits(RelayCHX_GPIO_Port_03, RelayCHX_GPIO_Pin_03);
		
			
		GPIO_SetBits(RelayCHX_GPIO_Port_04, RelayCHX_GPIO_Pin_04);
		
				
		GPIO_SetBits(RelayCHX_GPIO_Port_05, RelayCHX_GPIO_Pin_05);
		
				
		GPIO_SetBits(RelayCHX_GPIO_Port_06, RelayCHX_GPIO_Pin_06);
		
				
		GPIO_SetBits(RelayCHX_GPIO_Port_07, RelayCHX_GPIO_Pin_07);
		
				
		GPIO_SetBits(RelayCHX_GPIO_Port_08, RelayCHX_GPIO_Pin_08);
		
}





/**
  * @brief  初始化控制Relay的IO
  * @param  无
  * @retval 无
  */
void RelayGate_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RelayGate_GPIO_Clk_01 | RelayGate_GPIO_Clk_02 | RelayGate_GPIO_Clk_03, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_01;	

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayGate_GPIO_Port_01, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_02;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayGate_GPIO_Port_02, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_03;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayGate_GPIO_Port_03, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_04;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayGate_GPIO_Port_04, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_05;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayGate_GPIO_Port_05, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_06;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(RelayGate_GPIO_Port_06, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_07;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayGate_GPIO_Port_07, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_08;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayGate_GPIO_Port_08, &GPIO_InitStructure);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = RelayGate_GPIO_Pin_09;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(RelayGate_GPIO_Port_09, &GPIO_InitStructure);





#if 0
		GPIO_SetBits(RelayGate_GPIO_Port_01, RelayGate_GPIO_Pin_01);
		GPIO_SetBits(RelayGate_GPIO_Port_02, RelayGate_GPIO_Pin_02);	
		GPIO_SetBits(RelayGate_GPIO_Port_03, RelayGate_GPIO_Pin_03);		
		GPIO_SetBits(RelayGate_GPIO_Port_04, RelayGate_GPIO_Pin_04);		
		GPIO_SetBits(RelayGate_GPIO_Port_05, RelayGate_GPIO_Pin_05);	
		GPIO_SetBits(RelayGate_GPIO_Port_06, RelayGate_GPIO_Pin_06);	
		GPIO_SetBits(RelayGate_GPIO_Port_07, RelayGate_GPIO_Pin_07);	
		GPIO_SetBits(RelayGate_GPIO_Port_08, RelayGate_GPIO_Pin_08);
		GPIO_SetBits(RelayGate_GPIO_Port_09, RelayGate_GPIO_Pin_08);
#else

		GPIO_ResetBits(RelayGate_GPIO_Port_01, RelayGate_GPIO_Pin_01);
		GPIO_ResetBits(RelayGate_GPIO_Port_02, RelayGate_GPIO_Pin_02);	
		GPIO_ResetBits(RelayGate_GPIO_Port_03, RelayGate_GPIO_Pin_03);		
		GPIO_ResetBits(RelayGate_GPIO_Port_04, RelayGate_GPIO_Pin_04);		
		GPIO_ResetBits(RelayGate_GPIO_Port_05, RelayGate_GPIO_Pin_05);	
		GPIO_ResetBits(RelayGate_GPIO_Port_06, RelayGate_GPIO_Pin_06);	
		GPIO_ResetBits(RelayGate_GPIO_Port_07, RelayGate_GPIO_Pin_07);	
		GPIO_ResetBits(RelayGate_GPIO_Port_08, RelayGate_GPIO_Pin_08);
    GPIO_ResetBits(RelayGate_GPIO_Port_09, RelayGate_GPIO_Pin_09);

#endif



}



void OUT_Io_GPIO_Config(void){

TM_OUT_RE_Init();
TM_OUT_SE_Init();	
TM_OUT_CHARGE_Init();
//RelayCharge_GPIO_Config();
//RelayXXA_GPIO_Config();
//RelayCHX_GPIO_Config();
//RelayGate_GPIO_Config();

}














/*********************************************END OF FILE**********************/
