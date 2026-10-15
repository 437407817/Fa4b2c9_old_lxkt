#ifndef __DISSTATEFUN_H
#define	__DISSTATEFUN_H


#include "stm32fxxx.h"


























void RunMaintainWork_ChangeIn(void);





void MaintainState_Delay_PauseResume(void);
void MaintainState_Pause(void);
void MaintainState_PauseResume(void);

void MaintainState_Delay_Pause(void);
void MaintainState_SerialRun_Start(void);

void ChargerParallelNeedBitSetOpen(void);
	
	void SwitchMaster_SlaveParllelCharger(void);
void MaintainState_ParallelRun_Start(void);

void MaintainState_ParallelRun_Pause(void);
void MaintainState_SerialRun_Pause(void);
void MaintainState_SerialRun_PauseResume(void);
void MaintainState_ParallelRun_PauseResume(void);

void MaintainState_SerialRun_Stop(void);
void MaintainState_ParallelRun_Stop(void);
void MaintainState_Delay_Stop(void);
void MaintainStateRun_Start(void);
void MaintainStateRun_Stop(void);

void MaintainState_DelayRun_Start(void);

void MaintainState_Delay_Stop(void);

void MaintainState_Runwhile_CheckStop(void);




#endif /* __DISWORKFUN_H */

