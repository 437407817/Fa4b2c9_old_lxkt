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
 // #include "./sys/bsp_systime.h"   
#include "./test/bsp_test_soft_iic.h"   
#include "./usart/bsp_usart.h"

#include "./i2c/soft_i2c/bsp_soft_i2c_ee.h"
#include "./i2c/soft_i2c/bsp_soft_i2c_gpio.h"


//******************************






/*
 * eeprom AT24C02 读写测试
 * 正常返回1，异常返回0
 */
uint8_t Soft_i2c_Test(void) 
{
  uint16_t i;
	uint8_t write_buf[EEPROM_SIZE];
  uint8_t read_buf[EEPROM_SIZE];
  
/*-----------------------------------------------------------------------------------*/  
  if (EE_soft_CheckDevice(EEPROM_DEV_ADDR) == 1)
	{
		/* 没有检测到EEPROM */
		printf("没有检测到串行EEPROM!\r\n");
				
		return 0;
	}
/*------------------------------------------------------------------------------------*/  
  /* 填充测试缓冲区 */
	for (i = 0; i < EEPROM_SIZE; i++)
	{		
		write_buf[i] = i;
	}
/*------------------------------------------------------------------------------------*/  
  if (EE_soft_WriteBytes(write_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("写eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		printf("写eeprom成功！\r\n");
	}  

/*-----------------------------------------------------------------------------------*/
  if (EE_soft_ReadBytes(read_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("读eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		printf("读eeprom成功，数据如下：\r\n");
	}
/*-----------------------------------------------------------------------------------*/  
  for (i = 0; i < EEPROM_SIZE; i++)
	{
		if(read_buf[i] != write_buf[i])
		{
			printf("0x%02X ", read_buf[i]);
			printf("错误:EEPROM读出与写入的数据不一致");
			return 0;
		}
    printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15)
		{
			printf("\r\n");	
		}		
	}
  printf("eeprom读写测试成功\r\n");
  return 1;
}


/*********************************************END OF FILE**********************/
