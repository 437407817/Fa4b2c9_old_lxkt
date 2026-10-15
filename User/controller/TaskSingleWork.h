#ifndef __TASKSINGLEWORK_H
#define	__TASKSINGLEWORK_H


#include "stm32fxxx.h"









void Handle_CheckStop_CommuOverTimeFalg(void);

void Handle_SendVolDataToScreenAndAskSlave(void);


void Handle_CheckStop_ALLBoard_FinishWork(void);




void Handle_SendCapacityDataToScreen(void);
void Handle_SendSDTimeDataToScreen(void);
void Handle_SendSlaveAskdataAfter50MS(void);

void Handle_SaveSdData(void);
void Handle_FeedIWatchDog(void);
void Handle_test(void);


void Handle_ImmediateSaveSd(void);
void Handle_getTime(void);
uint8_t IFCommuBoardAllNotOverTime(uint8_t overtime);

void Handle_showdata(void);

void Handle_ChangeCheckStop_ALLBoard_FinishWork_time(void);


#endif /* __TASKSINGLEWORK_H */




