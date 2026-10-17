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
#include "./sys/sysio.h"
#include <string.h>
#include "./sys/bsp_random.h" 
//CanTxMsg TxMessage20E8,TxMessage21E8;			     //发送缓冲区
//extern CanRxMsg RxMessage;				 //接收缓冲区
//uint8_t TxData20E8[8]={0x01,0x00,0x00,0x00,0x00,0x00,0x46,0xFF};
//uint8_t TxData21E8[8]={0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF};
//uint8_t TxDataRETURN[8]={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00};

typedef struct
{
    uint16_t vol[8];
    uint16_t cur[8];
    int16_t temp[8];
    uint8_t status[16];
}DeviceData_t;




void TestCanSplitSend(void)
{
    DeviceData_t devData;
    uint16_t ret;

    // 给结构体填充测试数据，实际项目这里填业务真实数据
    memset(&devData, 0, sizeof(DeviceData_t));
    devData.vol[0]  = 12345;
    devData.cur[0]  = 6789;
    devData.temp[0] = 25;
    devData.status[0] = 0x01;
RNG_Random_setArray((uint16_t *)&devData,sizeof(devData)/ sizeof(uint16_t),0,0xFFFF);
    // 调用分包发送；0x18000001为CAN扩展帧ID
    ret = CANx_SendExtFrame_StructSplit(0x18000001, (uint8_t *)&devData, sizeof(DeviceData_t));

if(ret == 0)
{
    SYSTEM_DEBUG("can send over------------- ");
}
else
{
    // 如果某一次因为总线忙发送失败，不要让单片机崩溃，打印个日志跳过即可
    SYSTEM_DEBUG("can send error, fail at pkg: %d", ret);
    
    // 【核心防卡死】如果连续发生发送失败或总线异常，建议在这里执行一次CAN外设软件复位，防止硬件锁死
    // CAN_DeInit(CANx);
    // CANx_Mode_Init();
}
}




 void CAN_Test(void){
// SYSTEM_DEBUG("CANx_Send begin------------- ");
 	 TestCanSplitSend();
//	SYSTEM_DEBUG("CANx_SendExtFrame_StructSplit over------------- ");
	 
//	 CAN_SetMsg(&TxMessage20E8,CAN_Send_Id_1,TxData20E8);
//  // CAN_SetMsg(&TxMessage21E8,CAN_Send_Id_2,TxData21E8);
// 			CAN_Transmit(CANx, &TxMessage20E8);
//		//	CAN_Transmit(CANx, &TxMessage21E8);
//	 
// if(((RxMessage.ExtId==CAN_Get_Id_1)||(RxMessage.ExtId==CAN_Get_Id_2)) && (RxMessage.IDE==CAN_ID_EXT) && (RxMessage.DLC==8) )
// {	
//TxDataRETURN[7]++;
// Init_RxMes(&RxMessage);
//// printf("RxMessage.ExtId IS %x \n",RxMessage.ExtId);
// CAN_SetMsg(&TxMessage21E8,CAN_Send_Id_2,TxDataRETURN);
// CAN_Transmit(CANx, &TxMessage21E8);
// }

	 
#if 0	 
	 CanTxMsg TxMessage;
    TxMessage.ExtId = 0x18000001;
    TxMessage.IDE = CAN_ID_EXT;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 8;
    for(int i=0; i<8; i++) {
        TxMessage.Data[i] = i;
    }
    
    // 直接调底层发送
    uint8_t status = CAN_Transmit(CANx, &TxMessage);
    if(status == CAN_TxStatus_NoMailBox) {
        // 邮箱满
        SYSTEM_DEBUG("Mailbox Full!\n");
    } else {
        SYSTEM_DEBUG("Send Success, Mailbox: %d\n", status);
    }
	 
	 #endif
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
}

















//******************************





















/*********************************************END OF FILE**********************/
