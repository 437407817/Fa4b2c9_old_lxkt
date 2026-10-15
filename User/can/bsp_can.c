/**
  ******************************************************************************
  * @file    bsp_485_A_USART.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
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

#include "./can/bsp_can.h"

CanRxMsg RxMessage;				 //接收缓冲区

/*
 * 函数名：CAN_GPIO_Config
 * 描述  ：CAN的GPIO 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_GPIO_Config(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;   	

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN_TX_GPIO_CLK|CAN_RX_GPIO_CLK, ENABLE);
	//重映射引脚
	//GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	
	  /* 引脚源*/
  GPIO_PinAFConfig(CAN_TX_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
  GPIO_PinAFConfig(CAN_RX_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT); 
	 /* Configure CAN TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
	         
// 复用推挽输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* Configure CAN RX  pins */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	             // 上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
}

/*
 * 函数名：CAN_NVIC_Config
 * 描述  ：CAN的NVIC 配置,第1优先级组，0，0优先级
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_NVIC_Config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		/* Configure one bit for preemption priority */
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);
	 	/*中断设置*/
		NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;	   //CAN1 RX0中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * 函数名：CAN_Mode_Config
 * 描述  ：CAN的模式 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_Mode_Config(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	/************************CAN通信参数设置**********************************/
	/* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

	/*CAN寄存器初始化*/
	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_InitStructure);

	/*CAN单元初始化*/
	CAN_InitStructure.CAN_TTCM=DISABLE;			   //MCR-TTCM  关闭时间触发通信模式使能
	CAN_InitStructure.CAN_ABOM=ENABLE;			   //MCR-ABOM  自动离线管理 
	CAN_InitStructure.CAN_AWUM=ENABLE;			   //MCR-AWUM  使用自动唤醒模式
	CAN_InitStructure.CAN_NART=DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
	CAN_InitStructure.CAN_RFLM=DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
	CAN_InitStructure.CAN_TXFP=DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //正常工作模式
	#if 1
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW 重新同步跳跃宽度 2个时间单元
	 
	/* ss=1 bs1=5 bs2=3 位时间宽度为(1+5+3) 波特率即为时钟周期tq*(1+3+5)  */
	CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 时间段1 占用了5个时间单元
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元	
	
	/* CAN Baudrate = 1 MBps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB1 = 45 MHz) */
	CAN_InitStructure.CAN_Prescaler =5;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 45/(1+5+3)/5=1 Mbps
	 #endif
	 #if 0
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      //BTR-SJW 重新同步跳跃宽度 1个时间单元
    CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;     //BTR-TS1 时间段1 占用了13个时间单元
    CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      //BTR-TS1 时间段2 占用了2个时间单元
    CAN_InitStructure.CAN_Prescaler =9;         //BTR-BRP 波特率分频器  定义了时间单元的时间长度 45/(1+13+2)/9=250Kbps
    #endif
	
	
	
	CAN_Init(CANx, &CAN_InitStructure);
}

/*
 * 函数名：CAN_Filter_Config
 * 描述  ：CAN的过滤器 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/*CAN筛选器初始化*/
	CAN_FilterInitStructure.CAN_FilterNumber=0;						//筛选器组0
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;	//工作在掩码模式
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	//筛选器位宽为单个32位。
	/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */

	CAN_FilterInitStructure.CAN_FilterIdHigh= ((CAN_Get_Id_1<<3)>>16) & 0xffff;		//要筛选的ID高位 
	CAN_FilterInitStructure.CAN_FilterIdLow= ((CAN_Get_Id_1<<3)& 0xffff) | CAN_ID_EXT; //要筛选的ID低位 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= ((CAN_Get_Id_2<<3)>>16) & 0xffff;			//筛选器高16位每位必须匹配
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= ((CAN_Get_Id_2<<3)& 0xffff) | CAN_ID_EXT; 		//筛选器低16位每位必须匹配
	
	
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//筛选器被关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;			//使能筛选器
	CAN_FilterInit(&CAN_FilterInitStructure);
	

	/*CAN通信中断使能*/
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
	//发送中断使能
  // CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
	
}


/*
 * 函数名：CAN_Config
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void CAN_Config_Init(void)
{
  CAN_GPIO_Config();
  CAN_NVIC_Config();
  CAN_Mode_Config();
  CAN_Filter_Config();   
}





void CAN_RX_IRQHandler(void)
{

	/*从邮箱中读出报文*/
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
	//printf("\r\n 进入canid：%x \r\n",RxMessage.ExtId);
	/* 比较ID是否为0x */ 
	if((RxMessage.ExtId==CAN_Get_Id_1) && (RxMessage.IDE==CAN_ID_EXT) && (RxMessage.DLC==8) )
	{
		if(RxMessage.Data[0]==0x5A){
		//	 printf("\r\nCAN_Get_Id_1 RxMessage.Data[0] %x：\r\n",RxMessage.Data[0]);	
		}else {
			
		}
	
	}
	else
	{

	};
	
}









/**
  * @brief  初始化 Rx Message数据结构体
  * @param  RxMessage: 指向要初始化的数据结构体
  * @retval None
  */
void Init_RxMes(CanRxMsg *ReceiveMessage)
{
  uint8_t ubCounter = 0;

	/*把接收结构体清零*/
  ReceiveMessage->StdId = 0x00;
  ReceiveMessage->ExtId = 0x00;
  ReceiveMessage->IDE = CAN_ID_STD;
  ReceiveMessage->DLC = 0;
  ReceiveMessage->FMI = 0;
  for (ubCounter = 0; ubCounter < 8; ubCounter++)
  {
    ReceiveMessage->Data[ubCounter] = 0x00;
  }
}


/*
 * 函数名：CAN_SetMsg
 * 描述  ：CAN通信报文内容设置,设置一个数据内容为0-7的数据包
 * 输入  ：发送报文结构体
 * 输出  : 无
 * 调用  ：外部调用
 */	 
void CAN_SetMsg(CanTxMsg *TxMessage,uint32_t SendId ,uint8_t Data[8])
{	  
	uint8_t ubCounter = 0;

  //TxMessage.StdId=0x00;						 
  TxMessage->ExtId=SendId;					 //使用的扩展ID
  TxMessage->IDE=CAN_ID_EXT;					 //扩展模式
  TxMessage->RTR=CAN_RTR_DATA;				 //发送的是数据
  TxMessage->DLC=8;							 //数据长度为8字节
	
	/*设置要发送的数据0-7*/
	for (ubCounter = 0; ubCounter < 8; ubCounter++)
  {
    TxMessage->Data[ubCounter] = Data[ubCounter];
  }
}
/**************************END OF FILE************************************/











