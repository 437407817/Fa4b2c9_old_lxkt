#ifndef __TEST_IIC_H
#define	__TEST_IIC_H


#include "stm32f4xx.h"

#include "./i2c/hard_i2c/bsp_i2c_ee.h"











uint8_t I2C_WriteAndRead_Test(void);
uint8_t I2C_ReadDataShow(uint16_t EEpromAddress,uint16_t NumDataToRead);


void I2C_Test(void);









//============================================================================
uint8_t I2C_ReadTestWrong(uint16_t NumDataToRead);//³ö´íÊý¾Ý


uint8_t I2C_ReadTest01(uint16_t NumDataToRead);
uint8_t I2C_ReadTest02(uint16_t NumDataToRead);

uint8_t I2C_ReadTest03(uint16_t NumDataToRead);
uint8_t I2C_ReadTest04(uint16_t NumDataToRead);


uint8_t I2C_ReadTest(uint16_t NumDataToRead);















#endif /* __TEST_IIC_H */
