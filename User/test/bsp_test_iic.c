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
#include "./test/bsp_test_iic.h"   
#include "./usart/bsp_usart.h"
#include "./i2c/factory_iic.h"
#include "./sys/sysio.h"
//******************************

#define  EEP_Firstpage      0x0000
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];








	#if 0
	I2C_DeInit(sEE_I2C);
	I2C_HardEE_Init();
	I2C_Test();
	I2C_ReadTest(24);
	#endif



//===============================标准测试========================================


/**
  * @brief  I2C(AT24C02)读写测试
  * @param  无
  * @retval 正常返回1 ，不正常返回0
  */
 uint8_t I2C_WriteAndRead_Test(void)
{
	u16 i;

	printf("写入的数据");
    
	for ( i=0; i<=255; i++ ) //填充缓冲
  {   
    I2c_Buf_Write[i] = i+0+05;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //将I2c_Buf_Write中顺序递增的数据写入EERPOM中 
	sEE_WriteBuffer( I2c_Buf_Write, EEP_Firstpage, 256);

  
  printf("写成功");
   
  printf("读出的数据");
  //将EEPROM读出数据顺序保持到I2c_Buf_Read中

	
   volatile uint16_t NumDataRead = 256;
	
   sEE_ReadBuffer(I2c_Buf_Read, EEP_Firstpage, (uint16_t *)(&NumDataRead));
	 Delay(100);//DMA读数据必须延迟一下才能读，因为主线程块，DMA数据还没传输完成***
  //将I2c_Buf_Read中的数据通过串口打印
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			if(1){
			printf("错误:I2C EEPROM写入与读出的数据不一致");
			return 0;
				}
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  printf("I2C(AT24C02)读写测试成功");
	return 1;
}


/**
  * @brief  I2C(AT24C02)读测试
  * @param  EEpromAddress 从哪读
  * @param  NumDataToRead 读多少个
  * @retval 正常返回1 ，不正常返回0
  */

uint8_t I2C_ReadDataShow(uint16_t EEpromAddress,uint16_t NumDataToRead){
	uint8_t I2c_Buf_ReadTmp[NumDataToRead];
	uint16_t j=0;
		j=NumDataToRead;
sEE_ReadBuffer(I2c_Buf_ReadTmp, EEpromAddress, (uint16_t *)(&NumDataToRead)); //必须把该方法放在方法里面，多次调用外部方法才能正确读成功。
printf("\n\r");
	for(uint16_t i=0; i<j; i++){
printf("0x%02X ", I2c_Buf_ReadTmp[i]);
}
printf("\n ");
return 1;
}


/**
  * @brief  I2C(AT24C02)读测试
  * @param  
  * @retval 正常返回1 ，不正常返回0
  */

uint8_t I2C_ReadTest(uint16_t NumDataToRead){
uint16_t ud=0;
	ud=NumDataToRead;
	
	 IIC_EE_currentDriver->IIC_BufferRead(I2c_Buf_Read, (EEP_Firstpage+0X0000), NumDataToRead);//运行完该函数，NumDataToRead会等于0，因为传入的是指针
	
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,256,"----KKKK-----");
	IIC_EE_currentDriver->IIC_BufferRead(I2c_Buf_Read, (EEP_Firstpage+0X0200), NumDataToRead);
	SYSTEM_DEBUG_ARRAY_MESSAGE(I2c_Buf_Read,256,"----KKPK-----");
	
	
// printf(" ============= \n\r ");

//for (uint16_t i=0; i<ud; i++)
//	{	
//   printf("0x%02X ", I2c_Buf_Read[i]);

//}

// printf(" ============= \n\r ");

return 1;
}


//===============================反例========================================











uint8_t I2c_Buf_Readwrong[16];
//反例，出错数据
uint8_t I2C_ReadTestWrong(uint16_t NumDataToRead){
	uint16_t j=0;
		j=NumDataToRead;
	sEE_ReadBuffer(I2c_Buf_Readwrong, (EEP_Firstpage+0x0020), (uint16_t *)(&NumDataToRead)); //可读出来
		for(uint16_t ii=0; ii<j; ii++){
   printf("0x%02X ", I2c_Buf_Readwrong[ii]);
		}
		sEE_ReadBuffer(I2c_Buf_Readwrong, (EEP_Firstpage+0x0030), (uint16_t *)(&NumDataToRead));  //读不出来
		for(uint16_t ii=0; ii<j; ii++){
   printf("0x%02X ", I2c_Buf_Readwrong[ii]);
		}
			printf("\n ");
return 1;
}

//=============================外部测试===================================

void I2C_Test(void){
Delay_Ms(500);
I2C_WriteAndRead_Test();Delay_Ms(2000);
	
	
	I2C_ReadTest(256);
//	I2C_ReadTest(256);I2C_ReadTest(256);I2C_ReadTest(256);
	//Delay_Ms(2000);//I2C_ReadTest(10);
	//Delay_Ms(2000);I2C_ReadTest02(16);
	//	Delay_Ms(1000);I2C_ReadTest03(16);
	//	Delay_Ms(1000);I2C_ReadTest04(16);
	//Delay_Ms(1000);I2C_ReadTest01(16);
	Delay_Ms(1000);I2C_ReadDataShow(0x0000,16);	
	Delay_Ms(1000);I2C_ReadDataShow(0x0010,16);	
	Delay_Ms(1000);I2C_ReadDataShow(0x0020,16);	
	Delay_Ms(1000);I2C_ReadDataShow(0x0030,16);	
	Delay_Ms(1000);I2C_ReadDataShow(0x0040,8);	

}


//===============================其他不重要========================================

void I2C_Test1(void){
Delay_Ms(500);
	
	for (uint8_t i=0; i<16; i++ ) //填充缓冲
  {   
    I2c_Buf_Write[i] = i+0+07;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }
	
//sEE_WriteBuffer( I2c_Buf_Write, EEP_Firstpage, 16);
	Delay_Ms(1000);I2C_ReadDataShow(EEP_Firstpage,16);	
	
	
	

}



















#if 1




#endif
uint8_t I2c_Buf_Read01[16];
uint8_t I2c_Buf_Read02[16];
uint8_t I2c_Buf_Read03[16];

uint8_t I2C_ReadTest02(uint16_t NumDataToRead){
	uint16_t j=0;
		j=NumDataToRead;
	sEE_ReadBuffer(I2c_Buf_Read01, (EEP_Firstpage+0x0000), (uint16_t *)(&NumDataToRead)); 
		for(uint16_t ii=0; ii<j; ii++){
   printf("0x%02X ", I2c_Buf_Read01[ii]);
		}
			printf("\n ");
		Delay_Ms(1000);

return 1;
}


uint8_t I2C_ReadTest03(uint16_t NumDataToRead){
	uint16_t j=0;
		j=NumDataToRead;
	sEE_ReadBuffer(I2c_Buf_Read02, (EEP_Firstpage+0x0010), (uint16_t *)(&NumDataToRead)); 
		for(uint16_t ii=0; ii<j; ii++){
   printf("0x%02X ", I2c_Buf_Read02[ii]);
		}
	
			printf("\n ");
return 1;
}







#if 1
uint8_t I2C_ReadTest01(uint16_t NumDataToRead){
uint16_t ud=0,j=0;
	uint8_t un=16;
	ud=NumDataToRead/un;
	// sEE_ReadBuffer(I2c_Buf_Read, EEP_Firstpage, NumDataToRead);

	j=un;
printf("ud=0x%02X \n", ud);
for (uint16_t i=0; i<ud; i++)
	{	
		printf("i=0x%02X \n", i);
		sEE_ReadBuffer(I2c_Buf_Read, (0x0000), (uint16_t *)(&j)); 
		for(uint16_t ii=0; ii<un; ii++){
		
		
		//sEE_ReadBuffer(I2c_Read,i,1);
		//sEE_ReadBuffer(I2c_Buf_Read,i,1);
   printf("0x%02X ", I2c_Buf_Read[ii]);
			
		}
		printf("\n ");
		
		
				printf("i=0x%02X \n", i);
		sEE_ReadBuffer(I2c_Buf_Read, (0x0010), (uint16_t *)(&j)); 
		for(uint16_t ii=0; ii<un; ii++){
		
		
		//sEE_ReadBuffer(I2c_Read,i,1);
		//sEE_ReadBuffer(I2c_Buf_Read,i,1);
   printf("0x%02X ", I2c_Buf_Read[ii]);
			
		}
		printf("\n ");
		Delay_Ms(500);
						printf("i=0x%02X \n", i);
		sEE_ReadBuffer(I2c_Buf_Read, (0x0020), (uint16_t *)(&j)); 
		for(uint16_t ii=0; ii<un; ii++){
		
		
		//sEE_ReadBuffer(I2c_Read,i,1);
		//sEE_ReadBuffer(I2c_Buf_Read,i,1);
   printf("0x%02X ", I2c_Buf_Read[ii]);
			
		}
		printf("\n ");
		
		
}
return 1;
}
#endif






#if 0
uint8_t I2C_ReadTest(uint16_t NumDataToRead){
uint8_t I2c_Read[1];
	// sEE_ReadBuffer(I2c_Buf_Read, EEP_Firstpage, NumDataToRead);
	
for (uint16_t i=0; i<NumDataToRead; i++)
	{	
		
		I2C_EE_BufferRead(I2c_Buf_Read, i, 2); 
		
		//sEE_ReadBuffer(I2c_Read,i,1);
		//sEE_ReadBuffer(I2c_Buf_Read,i,1);
   printf("0x%02X ", I2c_Buf_Read[i]);
		
}
return 1;
}
#endif



/*********************************************END OF FILE**********************/
