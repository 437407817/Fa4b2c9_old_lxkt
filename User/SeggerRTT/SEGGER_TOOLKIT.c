#include "./SeggerRTT/SEGGER_TOOLKIT.h"
#include "./SeggerRTT/SEGGER_RTT.h"
#include "./sys/bsp_systime.h"   


#include "./SeggerRTT/SEGGER_dao.h"

#include "./io/OUT_io/bsp_gpio_out.h" 

#include "./converter/data_convert.h"
#include <stdlib.h>

 #include "./sys/sysio.h"
#include "string.h"


/**
  * @brief  切换采集通道channel for collection
  */


#include "./communication/SD_485DataFun.h"
#include "./usart/bsp_usart_sd.h"
#include "./service/EepromFun.h"
#include "./sys/sys_interrupt.h" 


/**
  * @brief  切换采集通道channel for collection
  * @param  *i 当前通道第几个的状态地址  *openstate 1开启轮训转换采集 0 关闭所有通道
  * @retval 无
  */



void SEGGER_HostDataToUsart(void){
uint16_t NumBytes = SEGGER_PCsendDataCount;
uint8_t * Hex_in;
uint8_t  Hex_in02[50];	
	uint8_t *acIn = NULL;
	uint16_t relength=0;
	
		acIn = (uint8_t *)malloc(NumBytes);
	
NumBytes = SEGGER_RTT_Read(0, acIn, NumBytes);//注意是&acIn[0]或acIn，不能是&acIn
	
if (NumBytes!=0) {
//SYSTEM_DEBUG("pc data------\n");
	
	
	if(SEGGER_hostDataEliminateSpace != 1){
		//不带去空格，直接发送
	Usart_SendArray(USARTx_A,(uint8_t *)acIn,NumBytes);
	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t *)acIn,NumBytes,"");
	
	}else{
	
	 //带去空格发送，包括其他非0-e字符
	AsciiRemoveSpace02(acIn,NumBytes,&relength);
		
		if(0){
			Usart_SendArray(USARTx_A,(uint8_t *)acIn,relength);//接收pc到的数据发送，一样的数据，不是串口需要的HEX
	
		}

		SYSTEM_DEBUG_ARRAY_MESSAGE_HorA(1,(uint8_t *)acIn,relength,"segger pc get1=");//
		//SYSTEM_DEBUG_ARRAY_MESSAGE_HorA(0,(uint8_t *)acIn,relength,"segger pc get0=");//
		Hex_in = (uint8_t *)malloc(relength);//在里面创建必须在里面释放
		AsciiToHex(acIn, &Hex_in, relength);
		//AsciiToHex03(acIn, Hex_in, relength);
		//AsciiToHex02(acIn,Hex_in02,relength);		
		if(Hex_in[0]==0xFF){
		switch(Hex_in[1]){
			case 01:SEGGER_PcDao_McuToUsartTransform(USARTx_A, Hex_in+2, relength/2-2);break;   //01:向单片机内部发送，发送给串口FF 01 5A A5 05 82 70 14 00 03 串口屏图标发生改变
		  case 02:SEGGER_PcDao_UsartToMcuTransform(USARTx_A, Hex_in+2, relength/2-2);break;   //02:通过模拟串口发送给mcu
		 // case 03:SEGGER_PcDao_CanToMcuTransform(Hex_in+2, relength/2-2);break;   //03:通过CAN发送给mcu
		 // case 04:SEGGER_PcDao_McuToCanTransform(Hex_in+2, relength/2-2);break;   //04:通过向单片机内部发送，发送给CAN
			
			


			case 07:SEGGER_PcDao_McuToUsartTransform(USART_485_B, Hex_in+2, relength/2-2);break; 

			
			case 0x09:Software_Reset();break; 
			default:break;
		}
		
		}else if(Hex_in[0]==0xFE){
			
			
			
			segger_outfun(Hex_in,relength/2-2);
			

		}else{
		
			
			
			
			//		Hex_in02[0]=0xaa;Hex_in02[1]=0xa1;Hex_in02[2]=0xa2;Hex_in02[3]=0xa3;Hex_in02[4]=0xa4;
//		Hex_in02[5]=0x1a;Hex_in02[6]=0x11;Hex_in02[7]=0x12;Hex_in02[8]=0x13;Hex_in02[9]=0x14;	
//		Usart_SendArray(USARTx_A,(uint8_t *)Hex_in02,10);
//			delay_ms(10);
//   Usart_SendArray(USARTx_A,(uint8_t *)Hex_in02,10);
//				delay_ms(10);

	
		//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)Hex_in,relength/2,"usrat ***************");
		//	delay_ms(1);
   //Usart_SendArray(USARTx_A,Hex_in,relength/2);
		   Usart_SendArray(USARTx_A,Hex_in,relength/2);	//5A A5 05 82 70 14 00 03 串口屏图标发生改变
		
		}
		
		
		
		
	  free(Hex_in);
    Hex_in = NULL;
		
	}
	 	

}
//		free(Hex_in);//不能放这里，会出问题
//    Hex_in = NULL;
free(acIn);
acIn = NULL;

}

__weak void segger_outfun(uint8_t * tmp,uint16_t retlen){

SYSTEM_INFO("You need to implement this function ( void segger_outfun(uint8_t * tmp) )./n");
SEGGER_UNUSED(tmp);

}



//void SYSTEM_DEBUG_SEGGER_CANDataToHost(CanTxMsg* ptr_cantxmsg){
//	SYSTEM_DEBUG_ARRAY_MESSAGE(ptr_cantxmsg->Data,8,"CAN_TX send message : StdId = %03X  ExtId = %08X ",ptr_cantxmsg->StdId,ptr_cantxmsg->ExtId);
//}







/*********************************************END OF FILE**********************/
