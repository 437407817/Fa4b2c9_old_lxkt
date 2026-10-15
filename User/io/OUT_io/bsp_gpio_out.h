#ifndef __BSP_RELAY_H
#define	__BSP_RELAY_H


#include "stm32fxxx.h"

#include "./TM/tm_stm32f4_gpio.h"
#include "./service/Workled.h"

//ENx
//充电Charge
#define RelayCharge_GPIO_Clk_01            RCC_AHB1Periph_GPIOE
#define RelayCharge_GPIO_Clk_02            RCC_AHB1Periph_GPIOC
#define RelayCharge_GPIO_Clk_03            RCC_AHB1Periph_GPIOA

#define RelayCharge_GPIO_Port_01           GPIOE
#define RelayCharge_GPIO_Pin_01            GPIO_Pin_3


#define RelayCharge_GPIO_Port_02           GPIOE
#define RelayCharge_GPIO_Pin_02            GPIO_Pin_6

#define RelayCharge_GPIO_Port_03           GPIOC
#define RelayCharge_GPIO_Pin_03            GPIO_Pin_0

#define RelayCharge_GPIO_Port_04           GPIOA
#define RelayCharge_GPIO_Pin_04            GPIO_Pin_0

#define RelayCharge_GPIO_Port_05           GPIOA
#define RelayCharge_GPIO_Pin_05            GPIO_Pin_5

#define RelayCharge_GPIO_Port_06           GPIOC
#define RelayCharge_GPIO_Pin_06            GPIO_Pin_4

#define RelayCharge_GPIO_Port_07           GPIOE
#define RelayCharge_GPIO_Pin_07            GPIO_Pin_7

#define RelayCharge_GPIO_Port_08           GPIOE
#define RelayCharge_GPIO_Pin_08            GPIO_Pin_8


 


#define ChargeChange2A_1A_GPIO_Clk            RCC_AHB1Periph_GPIOD
#define ChargeChange2A_1A_GPIO_Port           GPIOD
#define ChargeChange2A_1A_GPIO_Pin            GPIO_Pin_12

#define DYGate_GPIO_Clk                      RCC_AHB1Periph_GPIOA
#define DYGate_GPIO_Port                     GPIOA
#define DYGate_GPIO_Pin                      GPIO_Pin_15





//CHx
//采样
#define RelayCHX_GPIO_Clk_01            RCC_AHB1Periph_GPIOE
#define RelayCHX_GPIO_Clk_02            RCC_AHB1Periph_GPIOC
#define RelayCHX_GPIO_Clk_03            RCC_AHB1Periph_GPIOA


#define RelayCHX_GPIO_Port_01           GPIOE
#define RelayCHX_GPIO_Pin_01            GPIO_Pin_2

#define RelayCHX_GPIO_Port_02           GPIOE
#define RelayCHX_GPIO_Pin_02            GPIO_Pin_5

#define RelayCHX_GPIO_Port_03           GPIOC
#define RelayCHX_GPIO_Pin_03            GPIO_Pin_2

#define RelayCHX_GPIO_Port_04           GPIOA
#define RelayCHX_GPIO_Pin_04            GPIO_Pin_1

#define RelayCHX_GPIO_Port_05           GPIOA
#define RelayCHX_GPIO_Pin_05            GPIO_Pin_5

#define RelayCHX_GPIO_Port_06           GPIOC
#define RelayCHX_GPIO_Pin_06            GPIO_Pin_4

#define RelayCHX_GPIO_Port_07           GPIOE
#define RelayCHX_GPIO_Pin_07            GPIO_Pin_7

#define RelayCHX_GPIO_Port_08           GPIOE
#define RelayCHX_GPIO_Pin_08            GPIO_Pin_8



//REx
//大门
#define RelayGate_GPIO_Clk_01            RCC_AHB1Periph_GPIOE
#define RelayGate_GPIO_Clk_02            RCC_AHB1Periph_GPIOB
#define RelayGate_GPIO_Clk_03            RCC_AHB1Periph_GPIOA


#define RelayGate_GPIO_Port_01           GPIOE
#define RelayGate_GPIO_Pin_01            GPIO_Pin_4

#define RelayGate_GPIO_Port_02           GPIOC
#define RelayGate_GPIO_Pin_02            GPIO_Pin_1

#define RelayGate_GPIO_Port_03           GPIOA
#define RelayGate_GPIO_Pin_03            GPIO_Pin_2

#define RelayGate_GPIO_Port_04           GPIOA
#define RelayGate_GPIO_Pin_04            GPIO_Pin_6

#define RelayGate_GPIO_Port_05           GPIOB
#define RelayGate_GPIO_Pin_05            GPIO_Pin_0

#define RelayGate_GPIO_Port_06           GPIOE
#define RelayGate_GPIO_Pin_06            GPIO_Pin_9

#define RelayGate_GPIO_Port_07           GPIOE
#define RelayGate_GPIO_Pin_07            GPIO_Pin_10

#define RelayGate_GPIO_Port_08           GPIOE
#define RelayGate_GPIO_Pin_08            GPIO_Pin_11

#define RelayGate_GPIO_Port_09           GPIOE
#define RelayGate_GPIO_Pin_09            GPIO_Pin_12











//##RE

#define TM_RE_1_PORT           GPIOA
#define TM_RE_1_PINS           GPIO_PIN_8

#define TM_RE_2_PORT           GPIOC
#define TM_RE_2_PINS           GPIO_PIN_9

#define TM_RE_3_PORT           GPIOC
#define TM_RE_3_PINS           GPIO_PIN_8

#define TM_RE_4_PORT           GPIOC
#define TM_RE_4_PINS           GPIO_PIN_6

#define TM_RE_1_OFF            TM_GPIO_SetPinLow(TM_RE_1_PORT, TM_RE_1_PINS)
#define TM_RE_1_ON             TM_GPIO_SetPinHigh(TM_RE_1_PORT, TM_RE_1_PINS)

#define TM_RE_2_OFF            TM_GPIO_SetPinLow(TM_RE_2_PORT, TM_RE_2_PINS)
#define TM_RE_2_ON             TM_GPIO_SetPinHigh(TM_RE_2_PORT, TM_RE_2_PINS)

#define TM_RE_3_OFF            TM_GPIO_SetPinLow(TM_RE_3_PORT, TM_RE_3_PINS)
#define TM_RE_3_ON             TM_GPIO_SetPinHigh(TM_RE_3_PORT, TM_RE_3_PINS)

#define TM_RE_4_OFF            TM_GPIO_SetPinLow(TM_RE_4_PORT, TM_RE_4_PINS)
#define TM_RE_4_ON             TM_GPIO_SetPinHigh(TM_RE_4_PORT, TM_RE_4_PINS)

#define TM_RE_X_OFF(X)            TM_RE_##X##_OFF
#define TM_RE_X_ON(X)            TM_RE_##X##_ON

//-----------------------------


#define TurnFan_ON		TM_RE_1_ON;TM_RE_2_ON;TM_RE_3_ON;TM_RE_4_ON
#define TurnFan_OFF		TM_RE_1_OFF;TM_RE_2_OFF;TM_RE_3_OFF;TM_RE_4_OFF







#define TM_SE_1_PORT           GPIOI
#define TM_SE_1_PINS           GPIO_PIN_8

#define TM_SE_2_PORT           GPIOC
#define TM_SE_2_PINS           GPIO_PIN_13

#define TM_SE_3_PORT           GPIOC
#define TM_SE_3_PINS           GPIO_PIN_14

#define TM_SE_4_PORT           GPIOC
#define TM_SE_4_PINS           GPIO_PIN_15

#define TM_SE_5_PORT           GPIOI
#define TM_SE_5_PINS           GPIO_PIN_11

//#define TM_SE_X_OFF(X)            TM_SE_##X##_OFF
#define TM_SE_X_OFF(X)            TM_GPIO_SetPinLow(TM_SE_##X##_PORT, TM_SE_##X##_PINS)
#define TM_SE_X_ON(X)            TM_GPIO_SetPinHigh(TM_SE_##X##_PORT, TM_SE_##X##_PINS)





#define Turnled_OFF(X)   TM_SE_X_OFF(X) 
#define Turnled_ON(X)   TM_SE_X_ON(X) 

#define TurnParrelCharge_led_OFF  Turnled_OFF(1)
#define TurnParrelCharge_led_ON  Turnled_ON(1);TurnFinish_led_OFF

#define TurnParrelDisCharge_led_OFF  Turnled_OFF(2)
#define TurnParrelDisCharge_led_ON  Turnled_ON(2);TurnFinish_led_OFF

#define TurnMaintain_led_OFF  Turnled_OFF(3)
#define TurnMaintain_led_ON  Turnled_ON(3);TurnFinish_led_OFF

#define TurnFinish_led_OFF  Turnled_OFF(4)
#define TurnFinish_led_ON  turnOffAllLights();SYSTEM_DEBUG("----turnOffAllLights----");Turnled_ON(4)

#define TurnWrong_led_OFF  Turnled_OFF(5)
#define TurnWrong_led_ON  Turnled_ON(5);SYSTEM_DEBUG("----turnOffAllLights----");TurnFinish_led_OFF

//#define TurnWork_led_OFF  Turnled_OFF(1);Turnled_OFF(2);Turnled_OFF(3);Turnled_OFF(4)
#define TurnWork_led_OFF  turnOffAllLights();SYSTEM_DEBUG("----turnOffAllLights----");Turnled_OFF(4)


#define TM_SE_X_STATE(X)         TM_GPIO_GetOutputPinValue(TM_SE_##X##_PORT, TM_SE_##X##_PINS)

//#define GETParrelCharge_led_STATE TM_SE_X_STATE(1) 
//#define GETPParrelDisCharge_led_STATE TM_SE_X_STATE(2) 
//#define GETPMaintain_led_STATE TM_SE_X_STATE(3) 

#define GetLed_STATE(X)   TM_SE_X_STATE(X)



#define GetWrongLed_STATEAndled_ON  if(GetWrongLed_STATE!=1){TurnWrong_led_ON;}			


#define GetWrongLed_STATE  TM_SE_X_STATE(5)

#define TM_CHARGE_PORT           GPIOA
#define TM_CHARGE_PINS           GPIO_PIN_1

#define TM_CHARGE_OFF            TM_GPIO_SetPinLow(TM_CHARGE_PORT, TM_CHARGE_PINS)
#define TM_CHARGE_ON             TM_GPIO_SetPinHigh(TM_CHARGE_PORT, TM_CHARGE_PINS)



void TM_OUT_RE_Init(void);
void TM_OUT_SE_Init(void);
void TM_OUT_CHARGE_Init(void);


typedef enum {
	STATE_ZERO = 0,
	STATE_ONE
}E_ONOFF;


//void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
//void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#define RelayChargeON_01            GPIO_SetBits(RelayCharge_GPIO_Port_01,RelayCharge_GPIO_Pin_01);
#define RelayChargeOFF_01           GPIO_ResetBits(RelayCharge_GPIO_Port_01,RelayCharge_GPIO_Pin_01);



void RelayCharge_GPIO_Config(void);
void RelayXXA_GPIO_Config(void);
void RelayCHX_GPIO_Config(void);
void RelayGate_GPIO_Config(void);



void OUT_Io_GPIO_Config(void);

void TurnOnOffAllRelayGPIO(GPIO_TypeDef** RelayXXXPort,uint16_t* RelayXXXPin,uint8_t num,BitAction BitVal);
void TurnOnOffRelayByBit08(GPIO_TypeDef** RelayXXXPort,uint16_t* RelayXXXPin,uint8_t OnOffBit);



#endif /* __BSP_RELAY_H */
