#ifndef __SCREEN_H
#define	__SCREEN_H


#include "stm32fxxx.h"







#define DW_CRC16   0


void SCREEN_write_cmd(uint16_t addr, uint16_t *buf, uint16_t size);
void SCREEN_write_cmd_print(uint16_t addr, uint16_t *buf, uint16_t size, uint16_t debugprint);
void SCREEN_read_cmd(uint16_t addr, uint8_t num);


void SCREEN_DataSolveDV_cmd(uint16_t* addr, uint16_t **Data ,uint8_t numall,uint8_t *Array );



uint8_t DW_SCREEN_ReadfromQ_dataFromatVerify(uint8_t** q_data, uint8_t q_len);



#endif /* __SCREEN_H */

