#include "./screen/Screen.h"

#include "./sys/bsp_systime.h"   




#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./converter/data_convert.h"
#include <stdlib.h>

 #include "./sys/sysio.h"
#include "string.h"

#include "./sys/systick.h"




















/**
***********************************************************************
包格式：帧头0  帧头1  数据长度  功能字   数据  数据  CRC校验高   CRC校验低
        0x5a   0xa5    0x03      0x06    0x00  0x01      0xFB     0xFB
***********************************************************************
5AA5 05 82 1000 0002 :解释：通过指令往 0000 地址里面赋值 2，屏上的显示，数据变量整数类型 2
5AA5 04 83 1000 01    解释：从 1000 地址开始读 1 个字长度，数据指令最大容许长度 0x7c

*/
//creat_ticktime(1)

//单片机是小端数据模式，该函数会自动转化成大端模式后发送
void SCREEN_write_cmd(uint16_t addr, uint16_t *buf, uint16_t size) {      //82

//	Cal_start_ticktime(1);
	uint8_t *frame = NULL;
	#if (DW_CRC16==1)	
	uint16_t crc16_res;
		#endif
	//frame = (uint8_t *)mymalloc(SRAMIN, size*2 + 8);
	
	#if (DW_CRC16==1)
	frame = (uint8_t *)malloc(size*2 + 8);
	#else
	frame = (uint8_t *)malloc(size*2 + 6);
	#endif
//	SYSTEM_INFO("SCREEN_write_cmd 1  %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
	
	if(frame == NULL) {
		SYSTEM_ERROR("DW_CRC16 memory malloc wrong\n");
		return;
	}
	
	frame[0] = 0x5a;
	frame[1] = 0xa5;
	#if (DW_CRC16==1)	
	frame[2] = size*2 + 5;
	#else	
	frame[2] = size*2 + 3;
	#endif	
	frame[3] = 0x82;
	frame[4] = (uint8_t)((addr & 0xff00) >> 8);
	frame[5] = (uint8_t)(addr & 0xff);
	
	for(int i=0;i<size;i++) {
		frame[2*i+6] = (uint8_t)((buf[i] & 0xff00) >> 8);
		frame[2*i+7] = (uint8_t)(buf[i] & 0xff);
	}
	#if (DW_CRC16==1)
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	frame[size*2 + 6] = (uint8_t)(crc16_res & 0xff);
	frame[size*2 + 7] = (uint8_t)((crc16_res & 0xff00) >> 8);
	
//SYSTEM_DEBUG("crc2=0x%x 0x%x 0x%x",crc16_res,frame[size*2 + 6],frame[size*2 + 7]);
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 8,"write TO SCREEN =");
	
	Usart_SendArray(USARTx_A,frame,size*2 + 8);
		#else
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 6,"SCREEN write 82 write TO SCREEN =");
//	SYSTEM_INFO("SCREEN_write_cmd 2  %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
//	Cal_diff_ticktime(1);
	Usart_SendArray(USARTx_A,frame,size*2 + 6);
  #endif
	//HAL_UART_Transmit(&huart1,frame ,size*2 + 8, 1000);


//	SYSTEM_INFO("SCREEN_write_cmd 3  %d \n",Calculate_diffRunTime(&starttime2,&overtime2));
	
	
free(frame);
	frame = NULL;
	//myfree(SRAMIN, frame);
}



//单片机是小端数据模式，该函数会自动转化成大端模式后发送
void SCREEN_write_cmd_print(uint16_t addr, uint16_t *buf, uint16_t size, uint16_t debugprint) {      //82

	uint8_t *frame = NULL;
	#if (DW_CRC16==1)	
	uint16_t crc16_res;
		#endif
	//frame = (uint8_t *)mymalloc(SRAMIN, size*2 + 8);
	
	#if (DW_CRC16==1)
	frame = (uint8_t *)malloc(size*2 + 8);
	#else
	frame = (uint8_t *)malloc(size*2 + 6);
	#endif
	
	
	if(frame == NULL) {
		SYSTEM_ERROR("DW_CRC16 memory malloc wrong\n");
		return;
	}
	
	frame[0] = 0x5a;
	frame[1] = 0xa5;
	#if (DW_CRC16==1)	
	frame[2] = size*2 + 5;
	#else	
	frame[2] = size*2 + 3;
	#endif	
	frame[3] = 0x82;
	frame[4] = (uint8_t)((addr & 0xff00) >> 8);
	frame[5] = (uint8_t)(addr & 0xff);
	
	for(int i=0;i<size;i++) {
		frame[2*i+6] = (uint8_t)((buf[i] & 0xff00) >> 8);
		frame[2*i+7] = (uint8_t)(buf[i] & 0xff);
	}
	#if (DW_CRC16==1)
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	frame[size*2 + 6] = (uint8_t)(crc16_res & 0xff);
	frame[size*2 + 7] = (uint8_t)((crc16_res & 0xff00) >> 8);
	
//SYSTEM_DEBUG("crc2=0x%x 0x%x 0x%x",crc16_res,frame[size*2 + 6],frame[size*2 + 7]);
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 8,"write TO SCREEN =");
	
	Usart_SendArray(USARTx_A,frame,size*2 + 8);
		#else
	if(debugprint==1){
	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,size*2 + 6,"SCREEN write 82 data TO SCREEN ===");
	}
//	
	Usart_SendArray(USARTx_A,frame,size*2 + 6);
  #endif
	//HAL_UART_Transmit(&huart1,frame ,size*2 + 8, 1000);

	
	
	
	
free(frame);
	frame = NULL;
	//myfree(SRAMIN, frame);
}






void SCREEN_read_cmd(uint16_t addr, uint8_t num) {      //83

	uint8_t *frame = NULL;
	#if (DW_CRC16==1)	
	uint16_t crc16_res;
	#endif
	if(num > 0x7c) {
				SYSTEM_ERROR("Data read is too much than 0x7c\n");
		return;
	}
	
	
	#if (DW_CRC16==1)	
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
#if (DW_CRC16==1)	
	frame[2] = 0x06;
#else
	frame[2] = 0x04;
#endif	
	frame[3] = 0x83;
	frame[4] = (uint8_t)((addr & 0xff00) >> 8);
	frame[5] = (uint8_t)(addr & 0xff);
	frame[6] = num;
	
	#if (DW_CRC16==1)	
	crc16_res = crc_16(&frame[3], frame[2]-2);
	
	frame[7] = (uint8_t)(crc16_res & 0xff);	
	frame[8] = (uint8_t)((crc16_res & 0xff00) >> 8);

		Usart_SendArray(USARTx_A,frame,9);
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,9,"Usart_SendArray 83 read TO SCREEN =");
	#else
	
		Usart_SendArray(USARTx_A,frame,7);
	//SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,7,"SCREEN read 83 read TO SCREEN =");
  #endif


free(frame);
	frame = NULL;
}




/**
***********************************************************************
包格式：帧头0  帧头1  帧数据长度  地址高  地址低  数据长度   数据  数据   CRC校验高   CRC校验低
        0x5a   0xa5    0x03       0x60     0x01     0x01      0x01  0x01   0xFB        0xFB
***********************************************************************

5AA5 04 83 1000 01    解释：从 1000 地址开始读 1 个字长度，数据指令最大容许长度 0x7c
5AA5 04 83 1000 01 0000   解释：从 1000 地址返回1个0000数据
*/

//每个项目不同，需要修改
uint8_t DW_SCREEN_ReadfromQ_dataFromatVerify(uint8_t** q_data, uint8_t q_len){

#if (DW_CRC16==1)		
uint16_t crc16_res;
uint8_t	cl,ch;
#endif		
			//SYSTEM_DEBUG_ARRAY((uint8_t*)*frame,rx_data->len);

		
		
		
				//SYSTEM_DEBUG_ARRAY((uint8_t*)*frame,rx_data->q_len);
		if((q_data[0][0]!=0x5A)||(q_data[0][1]!=0xA5)||(q_data[0][3]!=0x83)){
			//*Datanum=0;
			SYSTEM_ERROR("screen data is not 5A A5 83 :0x%x 0x%x 0x%x  \n",q_data[0][0],q_data[0][1],q_data[0][3]);

	return 1;
		}

				if(q_data[0][2]!=q_len-3){
				//	*Datanum=0;
			SYSTEM_ERROR("screen count data is not right %d\n",q_len-3);
		
	return 1;
		}

#if (DW_CRC16==1)	
			crc16_res = crc_16(&q_data[0][3], q_len-5);
		
	cl = (uint8_t)(crc16_res & 0xff);
	ch = (uint8_t)((crc16_res & 0xff00) >> 8);
	
		
		if((q_data[0][q_len-2]!=cl)||(q_data[0][q_len-1]!=ch)){
		SYSTEM_ERROR("crc data is not right h=0x%X  l=0x%X \n",ch,cl);
		return 1;
		}
		
#endif			
		
		
		//SYSTEM_DEBUG("11 q_data[4]: %02x q_data[5]: %02X  ",(uint8_t)*(*q_data+4),(uint8_t)*(*q_data+5));//正确
		//SYSTEM_DEBUG("22 q_data[4]: %02x q_data[5]: %02x  ",(uint8_t)q_data[0][4],(uint8_t)q_data[0][5]);//正确

	
	
		return 0;


}















/*********************************************END OF FILE**********************/
