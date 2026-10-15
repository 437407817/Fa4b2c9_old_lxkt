/**
  ******************************************************************************
  * @file    bsp_test-can.c
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
 #include "./can/bsp_can.h" 
#include "./test/bsp_test_can.h"   
#include "./sys/bsp_systime.h"  

CanTxMsg TxMessage20E8,TxMessage21E8;			     //发送缓冲区
extern CanRxMsg RxMessage;				 //接收缓冲区
uint8_t TxData20E8[8]={0x01,0x00,0x00,0x00,0x00,0x00,0x46,0xFF};
uint8_t TxData21E8[8]={0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF};
uint8_t TxDataRETURN[8]={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00};


 void CAN_Test(void){
 
 	 
	
	 
	 CAN_SetMsg(&TxMessage20E8,CAN_Send_Id_1,TxData20E8);
  // CAN_SetMsg(&TxMessage21E8,CAN_Send_Id_2,TxData21E8);
 			CAN_Transmit(CANx, &TxMessage20E8);
		//	CAN_Transmit(CANx, &TxMessage21E8);
	 
 if(((RxMessage.ExtId==CAN_Get_Id_1)||(RxMessage.ExtId==CAN_Get_Id_2)) && (RxMessage.IDE==CAN_ID_EXT) && (RxMessage.DLC==8) )
 {	
TxDataRETURN[7]++;
 Init_RxMes(&RxMessage);
// printf("RxMessage.ExtId IS %x \n",RxMessage.ExtId);
 CAN_SetMsg(&TxMessage21E8,CAN_Send_Id_2,TxDataRETURN);
 CAN_Transmit(CANx, &TxMessage21E8);
 }

}

















//******************************





















/*********************************************END OF FILE**********************/
