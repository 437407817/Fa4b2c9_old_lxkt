/**
  ******************************************************************************
  * @file    bsp_USARTx_A.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   重定向c库printf函数到usart端口，中断接收模式
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./usart/bsp_usart.h"
//#include "./usart/rx_data_queue.h"
#include "./usart/p_data_queue.h"
#include "./TM/tm_stm32f4_usart.h"


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_A_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

#if defined (USARTx_A_RX_DMA_ENABLE)
/**
  * @brief  USARTx TX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USARTx_TX_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
			
		  /*开启DMA时钟*/
  RCC_AHB1PeriphClockCmd(USARTx_A_DMA_CLK, ENABLE);
  
  /* 复位初始化DMA数据流 */
  DMA_DeInit(USART_TX_DMA_STREAM);

  /* 确保DMA数据流复位完成 */
  while (DMA_GetCmdStatus(USART_TX_DMA_STREAM) != DISABLE)  {
  }

  /*usart1 tx对应dma2，通道4，数据流7*/	
  DMA_InitStructure.DMA_Channel = USARTx_A_DMA_CHANNEL;  
  /*设置DMA源：串口数据寄存器地址*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;	 
  /*内存地址(要传输的变量的指针)*/
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)SendBuff;
  /*方向：从内存到外设*/		
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;	
  /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
  DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
  /*外设地址不增*/	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
  /*内存地址自增*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
  /*外设数据单位*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /*内存数据单位 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
  /*DMA模式：不断循环*/
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//如果改为循环，会一直发送卡死	 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	
  /*优先级：中*/	
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
  /*禁用FIFO*/
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
  /*存储器突发传输 16个节拍*/
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  /*外设突发传输 1个节拍*/
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
  /*配置DMA2的数据流7*/		   
  DMA_Init(USART_TX_DMA_STREAM, &DMA_InitStructure);
  
  /*使能DMA*/
  DMA_Cmd(USART_TX_DMA_STREAM, ENABLE);
    /* 等待DMA数据流有效*/
  while(DMA_GetCmdStatus(USART_TX_DMA_STREAM) != ENABLE)
  {
  }   
}
#endif


#if defined (USARTx_A_RX_DMA_ENABLE)
/**
  * @brief  USARTx RX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USARTx_RX_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
		// 开启DMA时钟
		RCC_AHB1PeriphClockCmd(USARTx_A_DMA_CLK, ENABLE);
		
		  /* 复位初始化DMA数据流 */
  DMA_DeInit(USART_RX_DMA_STREAM);

  /* 确保DMA数据流复位完成 */
  while (DMA_GetCmdStatus(USART_RX_DMA_STREAM) != DISABLE)  {
  }

  /*usart1 rx对应dma2，通道4，数据流2*/	
  DMA_InitStructure.DMA_Channel = USARTx_A_DMA_CHANNEL;  
  /*设置DMA源：串口数据寄存器地址*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;	 
  /*内存地址(要传输的变量的指针)*/
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ReceiveBuff;
  /*方向：从内存到外设*/		
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
  /*传输大小DMA_BufferSize=RECEIVEBUFF_SIZE*/	
  DMA_InitStructure.DMA_BufferSize = RECEIVEBUFF_SIZE;
  /*外设地址不增*/	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
  /*内存地址自增*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
  /*外设数据单位*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /*内存数据单位 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
  /*DMA模式：不断循环*/
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
  /*优先级：中*/	
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
  /*禁用FIFO*/
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
  /*存储器突发传输 16个节拍*/
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  /*外设突发传输 1个节拍*/
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
  /*配置DMA2的数据流2*/		   
  DMA_Init(USART_RX_DMA_STREAM, &DMA_InitStructure);
  
  /*使能DMA*/
  DMA_Cmd(USART_RX_DMA_STREAM, ENABLE);
  
  /* 等待DMA数据流有效*/
  while(DMA_GetCmdStatus(USART_RX_DMA_STREAM) != ENABLE)
  {
  }   
}

#endif



 /**
  * @brief  USARTx_A GPIO 配置,工作模式配置。115200 8-N-1 ，中断接收模式
  * @param  无
  * @retval 无
  */
void USART_A_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
		

  USARTx_A_GPIO_APBxClkCmd(USARTx_A_RX_GPIO_CLK|USARTx_A_TX_GPIO_CLK,ENABLE); 

  /* 使能 USART 时钟 */
  USARTx_A_APBxClkCmd(USARTx_A_CLK,ENABLE);
 


  
  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(USARTx_A_RX_GPIO_PORT,USARTx_A_RX_SOURCE, USARTx_A_RX_AF);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(USARTx_A_TX_GPIO_PORT,USARTx_A_TX_SOURCE,USARTx_A_TX_AF);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = USARTx_A_TX_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USARTx_A_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = USARTx_A_RX_PIN;
  GPIO_Init(USARTx_A_RX_GPIO_PORT, &GPIO_InitStructure);
  
  
  /* 配置串USARTx_A 模式 */
  /* 波特率设置：USARTx_A_BAUDRATE */
  USART_InitStructure.USART_BaudRate = USARTx_A_BAUDRATE;
  /* 字长(数据位+校验位)：8 */
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* 停止位：1个停止位 */
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* 校验位选择：不使用校验 */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  /* 硬件流控制：不使用硬件流 */
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  /* USART模式控制：同时使能接收和发送 */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* 完成USART初始化配置 */
  USART_Init(USARTx_A, &USART_InitStructure); 
	
  /* 嵌套向量中断控制器NVIC配置 */
	NVIC_Configuration();
	
	#if defined (USARTx_A_TX_DMA_ENABLE)
	USARTx_TX_DMA_Config();
	#endif /* USARTx_A_RX_DMA_ENABLE */
	
  #if defined (USARTx_A_RX_DMA_ENABLE)
	//使能空闲中断
	USART_ITConfig(USARTx_A,USART_IT_IDLE,ENABLE);
		  /* 配置使用DMA模式 */
  
	USARTx_RX_DMA_Config();
	#else
		/* 使能串口接收中断 */
	USART_ITConfig(USARTx_A, USART_IT_RXNE, ENABLE);
			/* 使能串口接收中断 */
	USART_ITConfig(USARTx_A, USART_IT_IDLE, ENABLE);
	#endif /* USARTx_A_RX_DMA_ENABLE */
	
  /* 使能串口 */
  USART_Cmd(USARTx_A, ENABLE);
	//rx_queue_init();
	//p_rx_queue_init(&GV_qdf_1,&GV_ndb_1);
p_rx_queue_init_all(USARTx_A);
	
	
	#if 1
	#if defined (USARTx_A_TX_DMA_ENABLE)
  USART_DMACmd(USARTx_A, USART_DMAReq_Tx, ENABLE);//开始DMA传输
	#endif /* USARTx_A_RX_DMA_ENABLE */
	
	#if defined (USARTx_A_RX_DMA_ENABLE)
	USART_DMACmd(USARTx_A, USART_DMAReq_Rx, ENABLE);
	#endif /* USARTx_A_RX_DMA_ENABLE */
  #endif
}

/**
@verbatim
             |PINSPACK 1     |PINSPACK 2     |PINSPACK 3
U(S)ARTX     |TX     RX      |TX     RX      |TX     RX

USART1       |PA9    PA10    |PB6    PB7     |-      -
USART2       |PA2    PA3     |PD5    PD6     |-      -
USART3       |PB10   PB11    |PC10   PC11    |PD8    PD9
UART4        |PA0    PA1     |PC10   PC11    |-      -
UART5        |PC12   PD2     |-      -       |-      -
USART6       |PC6    PC7     |PG14   PG9     |-      -
UART7        |PE8    PE7     |PF7    PF6     |-      -
UART8        |PE1    PE0     |-      -       |-      -
@endverbatim
**/
void USART_All_Config(void){
USART_A_Config();
//TM_USART_Init(USART1, TM_USART_PinsPack_1, 115200);
//TM_USART_Init(UART5, TM_USART_PinsPack_1, 115200);


}







extern QUEUE_DATA_BUFF GV_qdf_1;



void USARTx_A_IRQHandler(void)
{

	
#if defined (USARTx_A_RX_DMA_ENABLE)
		uint16_t t;
	if(USART_GetITStatus(USARTx_A,USART_IT_IDLE) == SET)          //检查中断是否发生
	{	
		DMA_Cmd(USART_RX_DMA_STREAM,DISABLE);                         //关闭DMA传输

		t = DMA_GetCurrDataCounter(USART_RX_DMA_STREAM);              //获取剩余的数据数量
		
        Usart_SendArray(USARTx_A,ReceiveBuff,RECEIVEBUFF_SIZE-t);       //向电脑返回数据（接收数据数量 = SENDBUFF_SIZE - 剩余未传输的数据数量）
		//Usart_SendString( USARTx_A,"XXXXXX\n");     
		DMA_SetCurrDataCounter(USART_RX_DMA_STREAM,RECEIVEBUFF_SIZE);    //重新设置传输的数据数量

		DMA_Cmd(USART_RX_DMA_STREAM,ENABLE);                          //开启DMA传输
		
		USART_ReceiveData(USARTx_A);                              //读取一次数据，不然会一直进中断
		USART_ClearFlag(USARTx_A,USART_FLAG_IDLE);                //清除串口空闲中断标志位
	}
		#else
	
	#if 0
	uint8_t ucCh;
	QUEUE_DATA_TYPE *data_p; 
	
	if(USART_GetITStatus(USARTx_A,USART_IT_RXNE)!=RESET)
	{	
		ucCh  = USART_ReceiveData( USARTx_A );
		
						/*获取写缓冲区指针，准备写入新数据*/
		data_p = cbWrite(&rx_queue); 
		
		if (data_p != NULL)	//若缓冲队列未满，开始传输
		{		

			//往缓冲区写入数据，如使用串口接收、dma写入等方式
			*(data_p->head + data_p->len) = ucCh;
				
			if( ++data_p->len >= QUEUE_NODE_DATA_LEN)
			{
				cbWriteFinish(&rx_queue);
			}
		}else return;	
	}
	
	if ( USART_GetITStatus( USARTx_A, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
			/*写入缓冲区完毕*/
			cbWriteFinish(&rx_queue);
		ucCh = USART_ReceiveData( USARTx_A );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)

	}	
#endif 

#if 1
	uint8_t ucCh;
	Q_QUEUE_DATA_TYPE *data_p; 
	
	if(USART_GetITStatus(USARTx_A,USART_IT_RXNE)!=RESET)
	{	
		ucCh  = USART_ReceiveData( USARTx_A );
		
						/*获取写缓冲区指针，准备写入新数据*/
		data_p = p_cbWrite(&GV_qdf_1.q_rx_queue); 
		
		if (data_p != NULL)	//若缓冲队列未满，开始传输
		{		
			//往缓冲区写入数据，如使用串口接收、dma写入等方式
			*(data_p->q_head + data_p->q_len) = ucCh;
				
			if( ++data_p->q_len >= q_QUEUE_NODE_DATA_LEN)
			{
				p_cbWriteFinish(&GV_qdf_1.q_rx_queue);
			}
		}else return;	
	}
	
	if ( USART_GetITStatus( USARTx_A, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
			/*写入缓冲区完毕*/
			p_cbWriteFinish(&GV_qdf_1.q_rx_queue);
		//SYSTEM_DEBUG("\n USART_IT_IDLE  \n");
		ucCh = USART_ReceiveData( USARTx_A );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)

	}	
#endif 

	#endif /* USARTx_A_RX_DMA_ENABLE */
	
	
}	









/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/****************** 发送8位的数组 ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint16_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}
/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USARTx_A, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USARTx_A, USART_FLAG_TXE) == RESET);		
	
	//SEGGER_RTT_PutChar(0, ch);
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USARTx_A, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx_A);
}
/*********************************************END OF FILE**********************/
