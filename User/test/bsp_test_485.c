/**
  ******************************************************************************
  * @file    bsp_test-usart.c
  * @author  fire
  * @version V1.0
  * @date    2023-05-15
  * @brief   应用函数接口
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "./usart/bsp_485_usart.h"  
#include "./test/bsp_test_485.h"   
#include "./usart/p_data_queue.h"
#include "./io/IN_io/bsp_gpio_in.h" 
#include "./usart/bsp_usart_sd.h"
uint8_t UsartRingBuffdata485;
extern uint8_t SendBuff[SENDBUFF_SIZE];
	uint16_t i485=0;

//extern QUEUE_DATA_BUFF GV_qdf_485_1;
extern QUEUE_DATA_BUFF GV_qdf_485_B;


void USART_485_Test(void){

#if(0)
		{
			uint16_t i;
			
			
			
			_485_A_TX_EN();
			
			for(i=0;i<=0xff;i++)
			{
			_485_SendByte(i);	 //发送数据
			}
			
			/*加短暂延时，保证485发送数据完毕*/
			DelayNclock(0xFFF);
			_485_A_RX_EN();
			
			
			
		//	printf("\r\n发送数据成功！\r\n"); //使用调试串口打印调试信息到终端

		}

#endif
//p_queue_Callback(p_ReturnDataToBack,&GV_qdf_485_1);
//p_queue_Callback(void (*pFunc)(),QUEUE_DATA_BUFF *qdf)
static uint16_t i=1;
//_485_A_TX_EN();

//_485_SendByte(i);
//Usart_SendString( USART_485_A,"  485_1输出  \n");
//printf("\r\n==%s\r\n",STR_PARAM(i));

_485_A_RX_EN();

//_485_A_TX_EN();
Test_get_all_data_from_queue(USART_485_A);


i++;

}


void USART_485_B_Test(void){


p_queue_Callback(p_ReturnDataToBack_485_B,&GV_qdf_485_B);
//p_queue_Callback(void (*pFunc)(),QUEUE_DATA_BUFF *qdf)
static uint16_t i=1;
_485_B_TX_EN();

//_485_SendByte(i);
Usart_SendString( USART_485_B,"<Time:>");
//printf("\r\n==%s\r\n",STR_PARAM(i));

_485_B_RX_EN();

//_485_A_TX_EN();
Test_get_all_data_from_queue(USART_485_B);

delay_ms(1000);
i++;

}



void p_ReturnDataToBack_485_B(uint8_t **frame,uint16_t* length){
_485_B_TX_EN();
Usart_SendArray( USART_485_B, *frame, *length);
_485_B_RX_EN();
}



void p_ReturnDataToBack(uint8_t **frame,uint16_t* length){
_485_A_TX_EN();
Usart_SendArray( USART_485_A, *frame, *length);
_485_A_RX_EN();
}

	
void USART_485_Test1(void){


	
	Usart_SendString( USARTx_A,"串口A输出\n");
printf("所有串口都输出 %d\n\n",i485);
	i485++;
#ifdef USARTx_A_RX_DMA_ENABLE
#else
//	 if(Read_RingBuff(&UsartRingBuffdata))            //从环形缓冲区中读取数据
{
 USART_SendData(USARTx_A, UsartRingBuffdata485);
}
#endif /* USARTx_A_RX_DMA_ENABLE */

	#if defined (USARTx_A_TX_DMA_ENABLE)
	  /*填充将要发送的数据*/
  for(uint16_t i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'A';
   //printf("%x ",(uint32_t)&SendBuff[i]);//打印输出地址
  }
  USART_DMACmd(USARTx_A, USART_DMAReq_Tx, ENABLE);//开始DMA传输
	#endif /* USARTx_A_RX_DMA_ENABLE */

	#if defined (USARTx_A_RX_DMA_ENABLE)
	USART_DMACmd(USARTx_A, USART_DMAReq_Rx, ENABLE);
	#endif /* USARTx_A_RX_DMA_ENABLE */







}



/*********************************************END OF FILE**********************/
