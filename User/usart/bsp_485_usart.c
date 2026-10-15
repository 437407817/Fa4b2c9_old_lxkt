/**
  ******************************************************************************
  * @file    bsp_USART_485_A.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   重定向c库printf函数到usart端口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  

#include "./usart/p_data_queue.h"
#include "./usart/bsp_485_usart.h"


static void (*pProcUartDataFunc)(uint8_t data);   //函数指针变量，保存应用层回调函数地址



/// 配置USART接收中断
static void NVIC_485_A_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = _485_A_INT_IRQ; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*
 * 函数名：_485_Config
 * 描述  ：USART GPIO 配置,工作模式配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void USART_485_A_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART clock */
	RCC_AHB1PeriphClockCmd(USART_485_A_RX_GPIO_CLK|USART_485_A_TX_GPIO_CLK|_485_A_RE_GPIO_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(USART_485_A_CLK, ENABLE); 

	// USARTx_A_APBxClkCmd(USARTx_A_CLK,ENABLE);
	  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(USART_485_A_RX_GPIO_PORT,USART_485_A_RX_SOURCE, USART_485_A_RX_AF);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(USART_485_A_TX_GPIO_PORT,USART_485_A_TX_SOURCE,USART_485_A_TX_AF);

	
	/* USART GPIO config */
   /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = USART_485_A_TX_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART_485_A_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = USART_485_A_RX_PIN;
  GPIO_Init(USART_485_A_RX_GPIO_PORT, &GPIO_InitStructure);

  
  /* 485收发控制管脚 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = _485_A_RE_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(_485_A_RE_GPIO_PORT, &GPIO_InitStructure);
	  
	/* USART mode config */
	USART_InitStructure.USART_BaudRate = USART_485_A_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART_485_A, &USART_InitStructure); 

	
	NVIC_485_A_Configuration();
	/* 使能串口接收中断 */
	USART_ITConfig(USART_485_A, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART_485_A, USART_IT_IDLE, ENABLE);	
	USART_Cmd(USART_485_A, ENABLE);
//	p_rx_queue_init_all(USART_485_A);
	
	_485_A_RX_EN(); //默认进入接收模式
}


#if 0
/***************** 发送一个字符  **********************/
//使用单字节数据发送前要使能发送引脚，发送后要使能接收引脚。
void _485_SendByte(  uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(USART_485_A,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART_485_A, USART_FLAG_TXE) == RESET);	
	
}
/*****************  发送指定长度的字符串 **********************/
void _485_SendStr_length( uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;

	_485_A_TX_EN()	;//	使能发送数据	
    do 
    {
        _485_SendByte( *(str + k) );
        k++;
    } while(k < strlen);
		
	/*加短暂延时，保证485发送数据完毕*/
	DelayNclock(0xFFF);
		
	_485_A_RX_EN()	;//	使能接收数据
}


/*****************  发送字符串 **********************/
void _485_SendString(  uint8_t *str)
{
	unsigned int k=0;
	
	_485_A_TX_EN()	;//	使能发送数据
	
    do 
    {
        _485_SendByte(  *(str + k) );
        k++;
    } while(*(str + k)!='\0');
	
	/*加短暂延时，保证485发送数据完毕*/
	DelayNclock(0xFFF);
		
	_485_A_RX_EN()	;//	使能接收数据
}

#endif

void _485_A_IRQHandler(void)
{
    bsp_485_A_IRQHandler();

}



//extern QUEUE_DATA_BUFF GV_qdf_485_1;


#if 0

void bsp_485_A_IRQHandler(void)
{
		uint8_t ucCh;
	Q_QUEUE_DATA_TYPE *data_p; 
	
	if(USART_GetITStatus(USART_485_A,USART_IT_RXNE)!=RESET)
	{	
		ucCh  = USART_ReceiveData( USART_485_A );
		//Usart_SendByte( USARTx_A, ucCh);
						/*获取写缓冲区指针，准备写入新数据*/
		data_p = p_cbWrite(&GV_qdf_485_1.q_rx_queue); 
		
		if (data_p != NULL)	//若缓冲队列未满，开始传输
		{		

			//往缓冲区写入数据，如使用串口接收、dma写入等方式
			*(data_p->q_head + data_p->q_len) = ucCh;
				
			if( ++data_p->q_len >= q_QUEUE_NODE_DATA_LEN)
			{
				p_cbWriteFinish(&GV_qdf_485_1.q_rx_queue);
			}
		}else return;	
	}
	
	if ( USART_GetITStatus( USART_485_A, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
			/*写入缓冲区完毕*/
			p_cbWriteFinish(&GV_qdf_485_1.q_rx_queue);
		ucCh = USART_ReceiveData( USART_485_A );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)

	}	
	
}
#endif

/**
***********************************************************
* @brief 注册回调函数
* @param pFunc，函数指针变量，接收传入的回调函数地址
* @return 
***********************************************************
*/
void reg485ComCb(void (*pFunc)(uint8_t data))
{
	pProcUartDataFunc = pFunc;
}


void bsp_485_A_IRQHandler(void)
{
		uint8_t ucCh;
//	Q_QUEUE_DATA_TYPE *data_p; 
	
	if(USART_GetITStatus(USART_485_A,USART_IT_RXNE)!=RESET)
	{	
		ucCh  = USART_ReceiveData( USART_485_A );

		pProcUartDataFunc(ucCh);
	}
	
	if ( USART_GetITStatus( USART_485_A, USART_IT_IDLE ) == SET )  //必须有这句话，否则无法继续接收                                       //数据帧接收完毕
	{

		ucCh = USART_ReceiveData( USART_485_A );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)

	}	
	
}













/*********************************************END OF FILE**********************/
