#include "./SeggerRTT/SEGGER_dao.h"
#include "./SeggerRTT/SEGGER_RTT.h"
#include "./sys/bsp_systime.h"   
#include "string.h"
#include <stdlib.h>

#include "stm32fxxx.h"
 #include "./can/bsp_can.h" 



//#include "./TM/tm_stm32f4_gpio.h"//包含此文件，报错，但未知其原因


#include "defines.h"

//#include "./screen/ScreenDataDis.h"
//#include "./usart/p_data_queue.h"



 #include "./sys/sysio.h"

//#include "./test/bsp_test_can.h"   
#include "./usart/rx_data_queue.h"

/**
  * @brief  切换采集通道channel for collection
  * @param  *i 当前通道第几个的状态地址  *openstate 1开启轮训转换采集 0 关闭所有通道
  * @retval 无
  */

CanTxMsg TxMessageSegger;			     //发送缓冲区

void SEGGER_PcDao_CanToMcuTransform(uint8_t *array, uint16_t num){

//Usart_SendArray(pUSARTx,array,num);

}

void SEGGER_PcDao_McuToCanTransform(CAN_TypeDef* CANx1 ,uint8_t *array, uint16_t num){

//Usart_SendArray(pUSARTx,array,num);
	
	
//	for(uint8_t i=0;i<num/8;i++){
//	
//	 CAN_SetMsg(&TxMessageSegger,CAN_Send_Id_1,array+i*8);
//		CAN_Transmit(CANx1, &TxMessageSegger);
//		
//	}
}


	//QUEUE_DATA_TYPE *data_p; 

void SEGGER_PcDao_UsartToMcuTransform(USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num){

static QUEUE_DATA_TYPE *data_p; 


	//	ucCh  = USART_ReceiveData( USARTx_A );
		
						/*获取写缓冲区指针，准备写入新数据*/
		data_p = cbWrite(&rx_queue); 
			for(uint8_t i=0;i<num;i++){
		if (data_p != NULL)	//若缓冲队列未满，开始传输
		{		

			//往缓冲区写入数据，如使用串口接收、dma写入等方式
			*(data_p->head + data_p->len) = *(array+i);
				
			if( ++data_p->len >= QUEUE_NODE_DATA_LEN)
			{
				cbWriteFinish(&rx_queue);
			}


     }else return;
	 }		
		cbWriteFinish(&rx_queue);

}

void SEGGER_PcDao_McuToUsartTransform(USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num){
SYSTEM_DEBUG_ARRAY_MESSAGE(array,num,"SEGGER_PcDao_McuToUsartTransform");
Usart_SendArray(pUSARTx,array,num);

}


/*********************************************END OF FILE**********************/
