#include "./communication/Comu485.h"

#include "./sys/bsp_systime.h"   




#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./converter/data_convert.h"
#include <stdlib.h>

 #include "./sys/sysio.h"
#include "string.h"

#include "./usart/bsp_485_usart.h"  
#include "./sys/systick.h"







/**
***********************************************************
* @brief 485输出任务处理函数（长度单字节）
* @param
* @return 
***********************************************************
*/
void c485_write_cmd(uint8_t *data,uint16_t size, uint8_t cmd,uint8_t OverGetRX) {      

	uint8_t *frame = NULL;
	uint16_t crc16_res;
	
	//frame = (uint8_t *)mymalloc(SRAMIN, size*2 + 8);
	
	#if (c485_CRC16==1)
	frame = (uint8_t *)malloc(size + 6);
	#else
	frame = (uint8_t *)malloc(size + 4);
	#endif
	
	
	if(frame == NULL) {
		SYSTEM_ERROR("CRC16 memory malloc wrong\n");
		return;
	}
	
	frame[0] = FRAME_HEAD_0;
	frame[1] = FRAME_HEAD_1;
	#if (c485_CRC16==1)	
	frame[2] = size + 3;
	#else	
	frame[2] = size + 1;
	#endif	
	frame[3] = cmd;

	//frame[3] = 75;
	for(int i=0;i<size;i++) {
	
		frame[i+4] = (uint8_t)data[i];

	}
	

	
	
	#if (c485_CRC16==1)
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	//crc16_res = crc_16(&frame[3], 3);
	frame[size + 4] = (uint8_t)(crc16_res & 0xff);
	frame[size + 5] = (uint8_t)((crc16_res & 0xff00) >> 8);
	
	//SYSTEM_DEBUG("crc2=0x%x 0x%x 0x%x",crc16_res,frame[size + 5],frame[size + 6]);
	//SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size + 6,"crc =");
	_485_A_TX_EN();
	//DelayNclock(200);
	Usart_SendArray(USART_485_A,frame,size + 6);
	//DelayNclock(200);
	if(OverGetRX){
	_485_A_RX_EN();
	}
	
		#else
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 6,"Usart_SendArray 82 write TO SCREEN =");
	_485_A_TX_EN();
	DelayNclock(200);
	Usart_SendArray(USART_485_A,frame,size*2 + 6);
	DelayNclock(200);
	_485_A_RX_EN();
  #endif
	//HAL_UART_Transmit(&huart1,frame ,size*2 + 8, 1000);

	
	
	
	
free(frame);
	frame = NULL;
	//myfree(SRAMIN, frame);
}


void c485_write_cmd_print(uint8_t *data,uint16_t size, uint8_t cmd,uint8_t OverGetRX, uint16_t debugprint) {      

	uint8_t *frame = NULL;
	uint16_t crc16_res;
	
	//frame = (uint8_t *)mymalloc(SRAMIN, size*2 + 8);
	
	#if (c485_CRC16==1)
	frame = (uint8_t *)malloc(size + 6);
	#else
	frame = (uint8_t *)malloc(size + 4);
	#endif
	
	
	if(frame == NULL) {
		SYSTEM_ERROR("CRC16 memory malloc wrong\n");
		return;
	}
	
	frame[0] = FRAME_HEAD_0;
	frame[1] = FRAME_HEAD_1;
	#if (c485_CRC16==1)	
	frame[2] = size + 3;
	#else	
	frame[2] = size + 1;
	#endif	
	frame[3] = cmd;

	//frame[3] = 75;
	for(int i=0;i<size;i++) {
	
		frame[i+4] = (uint8_t)data[i];

	}
	

	
	
	#if (c485_CRC16==1)
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	//crc16_res = crc_16(&frame[3], 3);
	frame[size + 4] = (uint8_t)(crc16_res & 0xff);
	frame[size + 5] = (uint8_t)((crc16_res & 0xff00) >> 8);
	
	//SYSTEM_DEBUG("crc2=0x%x 0x%x 0x%x",crc16_res,frame[size + 5],frame[size + 6]);
	//SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size + 6,"crc =");
		if(debugprint==1){
	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size + 6,"485 send TO slave ***----- %d----",GetSysRunTime());
	}
	_485_A_TX_EN();
	//DelayNclock(200);
	Usart_SendArray(USART_485_A,frame,size + 6);
	//DelayNclock(200);
		if(OverGetRX){
	_485_A_RX_EN();
	}
		#else
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 6,"Usart_SendArray 82 write TO SCREEN =");
	_485_A_TX_EN();
	DelayNclock(200);
	Usart_SendArray(USART_485_A,frame,size*2 + 6);
	DelayNclock(200);
	_485_A_RX_EN();
  #endif
	//HAL_UART_Transmit(&huart1,frame ,size*2 + 8, 1000);

	
	
	
	
free(frame);
	frame = NULL;
	//myfree(SRAMIN, frame);
}














#if 0
void c485_read_cmd(uint16_t addr, uint8_t num) {      //83

	uint8_t *frame = NULL;
	uint16_t crc16_res;
	#if (c485_CRC16==1)	
	frame = (uint8_t *)malloc(9);
	#else
	frame = (uint8_t *)malloc(7);
	#endif	
	if(frame == NULL) {
				SYSTEM_ERROR("memory malloc wrong\n");
		return;
	}
	
	frame[0] = 0x5a;
	frame[1] = 0xa5;
#if (CRC16==1)	
	frame[2] = 0x06;
#else
	frame[2] = 0x04;
#endif	
	frame[3] = 0x83;
	frame[4] = (uint8_t)((addr & 0xff00) >> 8);
	frame[5] = (uint8_t)(addr & 0xff);
	frame[6] = num;
	
	#if (c485_CRC16==1)	
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	frame[7] = (uint8_t)((crc16_res & 0xff00) >> 8);
	frame[8] = (uint8_t)(crc16_res & 0xff);
		Usart_SendArray(USART_485_A,frame,9);
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,9,"Usart_SendArray 83 read TO SCREEN =");
	#else
	
		Usart_SendArray(USART_485_A,frame,7);
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,7,"Usart_SendArray 83 read TO SCREEN =");
  #endif


free(frame);
	frame = NULL;
}

#endif




//每个项目不同，需要修改
//uint8_t c485_ReadfromQ_dataFromatVerify(uint8_t** q_data, uint8_t q_len){
//uint16_t crc16_res;
//uint8_t	cl,ch;
//			//SYSTEM_DEBUG_ARRAY((uint8_t*)*frame,rx_data->len);
//		if((q_data[0][0]!=FRAME_HEAD_0)||(q_data[0][1]!=FRAME_HEAD_1)){
//SYSTEM_ERROR("5AA5 data is not right \n");
//	return 1;
//		}
//		
//				if((uint16_t)q_data[0][2]!=q_len-3){
//					SYSTEM_ERROR("num count data is not right,%d != %d\n",q_data[0][2],q_len-3);
//	return 1;
//		}
//				
//			crc16_res = crc_16(&q_data[0][3], q_len-5);
//		
//	cl = (uint8_t)(crc16_res & 0xff);
//	ch = (uint8_t)((crc16_res & 0xff00) >> 8);
//	
//		
//		if((q_data[0][q_len-2]!=cl)||(q_data[0][q_len-1]!=ch)){
//		SYSTEM_ERROR("crc data is not right h=0x%X  l=0x%X \n",ch,cl);
//		return 1;
//		}
//		
//		
//		
//		
//		//SYSTEM_DEBUG("11 q_data[4]: %02x q_data[5]: %02X  ",(uint8_t)*(*q_data+4),(uint8_t)*(*q_data+5));//正确
//		//SYSTEM_DEBUG("22 q_data[4]: %02x q_data[5]: %02x  ",(uint8_t)q_data[0][4],(uint8_t)q_data[0][5]);//正确

//	
//	
//		return 0;


//}










