#ifndef __CANFUN_H
#define	__CANFUN_H


#include "stm32fxxx.h"

#include "./GV_variable.h"


  #include "./system_config.h"
#include "./defines.h"

void CanDataSendAlwaysFun(void);
void User_CanGetId1Process(uint8_t *data, uint8_t len);

#endif /* __WORKLED_H */

