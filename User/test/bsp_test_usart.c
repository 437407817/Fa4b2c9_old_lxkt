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
#include "./usart/bsp_usart.h"  
#include "./test/bsp_test_usart.h"   
//#include "./usart/rx_data_queue.h"
#include "./usart/p_data_queue.h"



uint8_t UsartRingBuffdata;
extern uint8_t SendBuff[SENDBUFF_SIZE];
	uint16_t i=0;


void USART_Test(void){


	Test_get_all_data_from_queue(USARTx_A);
//	Usart_SendString( USARTx_A,"串口A输出\n");
printf("所有串口都输出 %d\n\n",i);
i++;








}







	
void USART_Test1(void){


	
	Usart_SendString( USARTx_A,"串口A输出\n");
printf("所有串口都输出 %d\n\n",i);
	i++;
#ifdef USARTx_A_RX_DMA_ENABLE
#else
//	 if(Read_RingBuff(&UsartRingBuffdata))            //从环形缓冲区中读取数据
{
 USART_SendData(USARTx_A, UsartRingBuffdata);
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
