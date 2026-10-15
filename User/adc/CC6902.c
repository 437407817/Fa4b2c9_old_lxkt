#include "./adc/CC6902.h"

#include "./sys/bsp_systime.h"   
#include "./sys/sysio.h"


#include "./converter/data_math.h"







#ifdef ADC_CC6902_DMA_ENABLE 

__IO uint16_t ADC_ConvertedValue;

#endif

 __IO uint16_t ADC_CC6902_ConvertedValue;



static void ADC_CC6902_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	RCC_AHB1PeriphClockCmd( ADC_CC6902_GPIO_CLK, ENABLE );
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC_CC6902_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //不上拉不下拉
	// 初始化 ADC IO
	GPIO_Init(ADC_CC6902_PORT, &GPIO_InitStructure);		
		
}
















#ifdef ADC_CC6902_DMA_ENABLE //open DMA or exti 
	// 使能ADC DMA 请求
static void ADC_CC6902_DMA_Config(void){
	 
 DMA_InitTypeDef DMA_InitStructure;
 
 // 打开DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 
 	
	// 复位DMA控制器
	DMA_DeInit(ADC_CC6902_DMA_CHANNEL);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_CC6902->DR ) );
	
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_CC6902_ConvertedValue;
	
	// 数据源来自外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// 缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(ADC_CC6902_DMA_CHANNEL, &DMA_InitStructure);
	
	// 使能 DMA 通道
	DMA_Cmd(ADC_CC6902_DMA_CHANNEL , ENABLE);

 
 }
#endif



#if (ADC_CC6902_IT_ENABLE==1)
 static void ADC_CC6902_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	// 优先级分组
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);

  // 配置中断优先级
  NVIC_InitStructure.NVIC_IRQChannel = ADC_CC6902_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#endif






 

/**
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
 static void ADC_CC6902_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;	
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	// 打开ADC时钟
	RCC_APB2PeriphClockCmd ( ADC_CC6902_CLK, ENABLE );
	
	
	  // -------------------ADC Common 结构体 参数 初始化------------------------
	// 独立ADC模式
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  // 时钟为fpclk x分频	
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  // 禁止DMA直接访问模式	
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  // 采样时间间隔	
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  
	ADC_CommonInit(&ADC_CommonInitStructure);
	// ADC 模式配置
	// 只使用一个ADC，属于独立模式
	  // -------------------ADC Init 结构体 参数 初始化--------------------------
	ADC_StructInit(&ADC_InitStructure);
  // ADC 分辨率
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  // 禁止扫描模式，多通道采集才需要	
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
  // 连续转换	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  //禁止外部边沿触发
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  //外部触发通道，本例子使用软件触发，此值随便赋值即可
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  //数据右对齐	
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //转换通道 1个
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                    

	// 初始化ADC
	ADC_Init(ADC_CC6902, &ADC_InitStructure);
	

	
	// 配置 ADC 通道转换顺序和采样时间
	ADC_RegularChannelConfig(ADC_CC6902, ADC_CC6902_CHANNEL, 1, ADC_SampleTime_480Cycles);
													 



	
	
	
														 
#ifdef ADC_CC6902_DMA_ENABLE //open DMA or exti 

  // 使能DMA请求 after last transfer (Single-ADC mode)
  ADC_DMARequestAfterLastTransferCmd(ADC_CC6902, ENABLE);
	// 使能ADC DMA 请求
	ADC_DMACmd(ADC_CC6902, ENABLE);
#else
	// ADC 转换结束产生中断，在中断服务程序中读取转换值
	ADC_ITConfig(ADC_CC6902, ADC_IT_EOC, ENABLE);
#endif

	
	// 开启ADC ，并开始转换
	ADC_Cmd(ADC_CC6902, ENABLE);
	

	
	// 由于没有采用外部触发，所以使用软件触发ADC转换 
	ADC_SoftwareStartConv(ADC_CC6902);
	
}





uint16_t ADC_CC6902_GetValue(void)
{
		//设置指定ADC的规则组通道，一个序列，采样时间
 	ADC_RegularChannelConfig(ADC_CC6902, ADC_CC6902_CHANNEL, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,采样时间为239.5周期
	 
	ADC_SoftwareStartConv(ADC_CC6902);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC_CC6902, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC_CC6902);	//返回最近一次ADC1规则组的转换结果
}






/**
  * @brief  CC6902不同型号 10A 解决方案
  * @param  ConvertedValue 单片机采样12位数值 CurrentSensitivity 电流灵敏度mA/v 
  * @param  n为几位小数保留 例vol=12.5，n=0时vol=12 n=1时vol=125 n=2时vol=1250 (5V电源与REF3030需要20k 30k分压)
  * @retval 采集的电流mA
  */
int16_t ADC_CC6902_10A_calculateData(uint16_t ConvertedValue){

uint8_t n=1;
//	SYSTEM_DEBUG(" *--  %d  %d  %d  %d  %d ",ConvertedValue,((int32_t)ConvertedValue - 2048),((int32_t)ConvertedValue - 2048 ) *25 ,(((int32_t)ConvertedValue - 2048 ) *25*power(10,n)),
//	(((int32_t)ConvertedValue - 2048 ) *25*power(10,n))/4096);
//SYSTEM_DEBUG(" *--  %d   ,%d ",(int32_t)ConvertedValue,(((int32_t)ConvertedValue - 2048 ) *25*(10^n))/4096);
	
//return (int16_t)(((int32_t)ConvertedValue - 2048 ) *100*(10^n))/16384;
return (int16_t)((((int32_t)ConvertedValue - 2048 ) *25*power(10,n))/4095);
}

//0v---*12.5A---0---0v

//1.5v---0A---2048---2.5v

//3v---12.5A---4096---5v

//通过公式求Ip，例如10A的芯片，VCC=5V，Ip=12.5A,再通过y=kx+b,y=12.5,x=4096,y=-12.5,x=0,计算K和b
//y=12.5*2(x-2048)/4096,12.5是最大上限值Imax
//Imax=((Vcc/2)*1000)/Q   Q为灵敏度
//y=(Vcc*1000)*(X-2048)/(4096*Q)
//3/5

/**
  * @brief  CC6902不同型号5A 10A 20A解决方案，电源电压5V
  * @param  ConvertedValue 单片机采样12位数值 CurrentSensitivity 电流灵敏度mA/v   5A-400 5B-185 10A-200 20A-100 30A-67
  * @retval 采集的电流mA
  */
int16_t ADC_CC6902_XA_calculateData(uint16_t ConvertedValue,uint16_t CurrentSensitivity)
{

uint8_t n=1;
//return (((int32_t)ConvertedValue - 2048 ) *10*1000*(10^n))/(4096*2*CurrentSensitivity);
	
return (int16_t)((((int32_t)ConvertedValue - 2048 ) *5000*power(10,n))/(4096*CurrentSensitivity));

}



/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADC_CC6902_Init(void)
{
	
	ADC_CC6902_GPIO_Config();
#ifdef ADC_CC6902_DMA_ENABLE //open DMA or exti 
	ADC_CC6902_DMA_Config();
#else
	#if (ADC_CC6902_IT_ENABLE==1)
	
	ADC_CC6902_NVIC_Config();
	#endif

#endif

	ADC_CC6902_Mode_Config();

}










#if (ADC_CC6902_IT_ENABLE==1)


void ADC_CC6902_IRQHandler(void)
{	
	if (ADC_GetITStatus(ADC_CC6902,ADC_IT_EOC)==SET) 
	{
		// 读取ADC的转换值
		ADC_CC6902_ConvertedValue = ADC_GetConversionValue(ADC_CC6902);
		
		//切换电池测量点*********************************
	}
	ADC_ClearITPendingBit(ADC_CC6902,ADC_IT_EOC);
}
#endif	/*!< ADCx_DMA_ENABLE */






/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADC_CC6902_TEST(void){



SYSTEM_INFO("\n CC6902++++ = %X = %d mA\n", ADC_CC6902_GetValue(), ADC_CC6902_10A_calculateData(ADC_CC6902_GetValue()));	
	
}

















/*********************************************END OF FILE**********************/
