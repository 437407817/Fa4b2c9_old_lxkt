/**
  ******************************************************************************
  * @file    bsp_test-all.c
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
  

 #include "./sys/bsp_systime.h"   
#include "./test/bsp_test_gpio_out.h"  
#include "./sys/sysio.h"
#include "./io/OUT_io/bsp_gpio_out.h"   
  
//#include "./TM/tm_stm32f4_gpio.h"




extern GPIO_TypeDef * RelayGatePort[8] ;
extern uint16_t RelayGatePin[8] ;
extern GPIO_TypeDef * RelayChargePort[8] ;
extern uint16_t RelayChargePin[8] ;





void Relay_TestOpenAndClose(void);

void Relay_TestOpenAndClose02(void);

void Relay_Test01(void);




void GPIO_Out_Test(void){
static uint8_t ir=0;
	//Relay_Test01();
	if(ir==0){
	TM_SE_X_ON(1);	TM_SE_X_ON(2);	TM_SE_X_ON(3);	TM_SE_X_ON(4);	TM_SE_X_ON(5);	TM_CHARGE_ON;
	ir=1;
	}else{
		TM_SE_X_OFF(1);	TM_SE_X_OFF(2);			TM_SE_X_OFF(3);	TM_SE_X_OFF(4);			TM_SE_X_OFF(5);	TM_CHARGE_OFF;
	ir=0;
	}
	

}









void Relay_TestOpenAndClose(void){
static uint8_t ir=0;
	ir++;
	if(ir%2==1){
		TurnOnOffAllRelayGPIO(RelayGatePort,RelayGatePin,9,1);
	}else{
		TurnOnOffAllRelayGPIO(RelayGatePort,RelayGatePin,9,0);
	}
SYSTEM_INFO("\n Relay_Test \n");
	Delay(4000);


}


void Relay_TestOpenAndClose02(void){
static uint8_t ir=0;
	
TurnOnOffRelayByBit08(RelayGatePort,RelayGatePin,ir);
	ir++;
SYSTEM_INFO("\n Relay_Test \n");
	Delay(3000);


}


void Relay_Test01(void){

TurnOnOffRelayByBit08(RelayGatePort,RelayGatePin,0xff);
	Delay(3000);
	GPIO_ResetBits(ChargeChange2A_1A_GPIO_Port, ChargeChange2A_1A_GPIO_Pin);Delay(3000);
TurnOnOffRelayByBit08(RelayChargePort,RelayChargePin,(uint8_t)(~0xff));
GPIO_SetBits(ChargeChange2A_1A_GPIO_Port, ChargeChange2A_1A_GPIO_Pin);


}




/*********************************************END OF FILE**********************/
