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

#include "./spi/flash/bsp_spi_flash.h"
#include "./sys/bsp_systime.h" 
#include "./test/bsp_test_spi.h"  



//******************************

void SPI_Test01(void);
void SPI_Test02(void);


__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;

void SPI_Test(void)
{




//SPI_Test01();
SPI_Test02();


}


void SPI_Test01(void)
{




	/* 获取 Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();	
	Delay( 200 );
	
	/* 获取 SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();	
	printf("\r\n FlashID is 0x%X,\
	Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);



}



void SPI_Test02(void)
{




	/* 获取 Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();	
	Delay( 200 );
	
	/* 获取 SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();	
	printf("\r\n FlashID is 0x%X,\
	Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);



}
	#if 0
//	__IO uint32_t DeviceID = 0,FlashID=0;
//	FlashID = sFLASH_ReadID();
//	/* 获取 SPI Flash ID */
//	sFLASH_Init();Delay( 200 );
//	printf("\r\n FlashID is 0x%X\r\n", FlashID);



	#endif


/*********************************************END OF FILE**********************/
