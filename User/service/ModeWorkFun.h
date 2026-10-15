


#ifndef __MODEWORKFUN_H
#define __MODEWORKFUN_H




#include "./GV_variable.h"




void SlaveAllChangeRunStateBy(uint8_t i_state,uint8_t count);


void Mode_Constant_Current_Charge_Start(void);
void Mode_Constant_Voltage_Charge_Start(void);

void Mode_DisCharge_Start(void);

void Mode_MaintainCharge_Start(void);

void Mode_Serial_DisCharge_Start(void);
void Mode_Serial_Charge_Start(void);




void Mode_Charge_Stop(void);

void Mode_MaintainState_Stop(void);
void Mode_Serial_Charge_Stop(void);
void Mode_Serial_DisCharge_Stop(void);
void Mode_Constant_Voltage_Charge_Stop(void);







#endif /* __STM32Fxxx_H */
