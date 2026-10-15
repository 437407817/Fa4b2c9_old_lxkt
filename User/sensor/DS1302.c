#include "./sensor/DS1302.h"


#include "./sys/sysio.h"




static GPIO_InitTypeDef  GPIO_InitStructure;  

static void DS1302_OUT_GPIO_INIT(void)
{

    // 配置I/O引脚
    GPIO_InitStructure.GPIO_Pin = DS1302_IO_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(DS1302_IO_GPIO_PORT, &GPIO_InitStructure);

}


static void DS1302_IN_GPIO_INIT(void)
{
    // 配置I/O引脚
    GPIO_InitStructure.GPIO_Pin = DS1302_IO_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(DS1302_IO_GPIO_PORT, &GPIO_InitStructure);
}


void DS1302_GPIO_Init(void)
{


    // 使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(DS1302_RST_GPIO_CLK|DS1302_SCLK_GPIO_CLK|DS1302_IO_GPIO_CLK, ENABLE);

    // 配置SCLK引脚
    GPIO_InitStructure.GPIO_Pin = DS1302_SCLK_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DS1302_SCLK_GPIO_PORT, &GPIO_InitStructure);

    // 配置RST引脚
    GPIO_InitStructure.GPIO_Pin = DS1302_RST_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DS1302_RST_GPIO_PORT, &GPIO_InitStructure);

		
		DS1302_RST_L;
		DS1302_SCLK_L;
		

}



  /*****************************************
 * 函数名：void DS1302_WriteReg(uchar add,uchar dat)
 * 描述  ：DS1302写指令和数据
*  输入  ：add:发送地址，dat：所在数据
 * 输出  ：无
 * 调用  ：
 *************************************/
 void DS1302_WriteByte(uint8_t add,uint8_t dat)
 {
	 	DS1302_RST_L;
		DS1302_DELAY;
	  DS1302_SCLK_L;
	 	DS1302_DELAY;
	  DS1302_RST_H;
	 	DS1302_DELAY;

DS1302_WriteAddrOrData(add);
DS1302_WriteAddrOrData(dat);

		DS1302_RST_L;					
 }

 
 
 void DS1302_init(uint8_t *time)
{
    DS1302_GPIO_Init();//GPIO初始化配置
    DS1302_DELAY;
  DS1302_RST_L; //RET=0;
  DS1302_SCLK_L;// CLK=0;
    //下面是对DS1302启动电池，不掉电   设置时间
    DS1302_WriteByte(0x8e,0x00);//WP=0 允许数据写入DS1302
//    DS1302_Write(0x90,0xA7);//充电(1个二极管+8K电阻)
//    DS1302_Write(0x8E,0X80);//开启保护 WP=1
    if(DS1302_Read(0X81)&0X80)//查询DS302时钟是否启动,如果时钟停止走动：启动时钟+初始化时钟
    {
        DS1302_SetTime(time);//设置设置初始时钟
    }
    //否则跳过

}
 
 
  void DS1302_WriteAddrOrData(uint8_t addrordata)
 {
 uint8_t temp1;
 temp1=addrordata;

DS1302_OUT_GPIO_INIT();
	// DS1302_RST_H;
//发送地址
for(uint8_t i=0;i<8;i++)
 {
        if(temp1&0x01)
         {
					 DS1302_IO_H;
				 }     
        else
        { 
				DS1302_IO_L;					
				}   
        temp1=temp1>>1;

				DS1302_SCLK_H;
        DS1302_DELAY;

				DS1302_SCLK_L;
				DS1302_DELAY;
  }


 }
 
 

/*****************************************
 * 函数名：uchar DS1302_Read(uchar add)
 * 描述  ：DS1302读数据
 *  输入  ：add:发送所在地址
 * 输出  ：
 * 调用  ：
 *************************************/
uint8_t DS1302_Read(uint8_t add)
{
  uint8_t suf;

	DS1302_RST_H;
	DS1302_DELAY;
	DS1302_WriteAddrOrData(add);


    DS1302_IN_GPIO_INIT();
  for(uint8_t i=0;i<8;i++)
    {
     suf=suf>>1;//读数据变量
     if(DS1302_io_read)    //IO=1
     {
         suf=suf|0x80;
     }
     else     //IO=0
     {
     suf=suf&0x7f;
     }

		 DS1302_SCLK_H

		 DS1302_DELAY;
 
		 DS1302_SCLK_L;
		 DS1302_DELAY;
    }
    
		DS1302_RST_L;
DS1302_DELAY;

return suf;
}




/*****************************************
 * 函数名：void DS1302_SetTime(uchar *ad)
 * 描述  ：DS1302 写入设置时间
 *  输入  ：add:发送所在地址
 * 输出  ：
 * 调用  ：
 *************************************/
void DS1302_SetTime(uint8_t *ad)
  {
   DS1302_WriteByte(0x8e,0x00);   //WP=0 允许数据写入DS1302
/**********以下对时分秒的初始化*************/
        DS1302_WriteByte(DS1302_SEC_REG_ADDR,ad[0]/10*16+ad[0]%10);  //秒
        DS1302_WriteByte(DS1302_MIN_REG_ADDR,ad[1]/10*16+ad[1]%10);   //分
        DS1302_WriteByte(DS1302_HOUR_REG_ADDR,ad[2]/10*16+ad[2]%10);   //时
      /**********以下对年月日的初始化*************/
       DS1302_WriteByte(DS1302_DATE_REG_ADDR,ad[3]/10*16+ad[3]%10);
       DS1302_WriteByte(DS1302_MONTH_REG_ADDR,ad[4]/10*16+ad[4]%10);
       DS1302_WriteByte(DS1302_YEAR_REG_ADDR,ad[5]/10*16+ad[5]%10);

     DS1302_WriteByte(0x8e,0x80);   //0x8e控制字节地址,bit7=WP WP=1 禁止数据写入DS1302
  }
#if 0


/*****************************************
 * 函数名： void DS1302_OFF(void)
 * 描述  ：DS1302时间禁止走时
 *  输入  ：
 * 输出  ：
 * 调用  ：
 *************************************/
  void DS1302_OFF(void)
  {
   uint8_t temp;
   temp=DS1302_Read(0x81);//读取表地址时间
   DS1302_WriteReg(0x8e,0x00);//WP=0 允许数据写入DS1302
   temp=temp|(1<<7);
   DS1302_WriteReg(0x80,temp);//WP=1 禁止数据写入DS1302

  }
/*****************************************
 * 函数名： void DS1302_ON(void)
 * 描述  ：DS1302时间开始运行，走时
 *  输入  ：
 * 输出  ：
 * 调用  ：
 *************************************/
  void DS1302_ON(void)
  {
   uint8_t temp;
   temp=DS1302_Read(0x81);
   DS1302_WriteReg(0x8e,0x00);//WP=0 允许数据写入DS1302
   temp=temp|(0<<7);
   DS1302_WriteReg(0x80,temp);//WP=0 允许数据写入DS1302

  }

#endif



 /*****************************************
 * 函数名：void DS1302_Readtime(void)
 * 描述  ：    DS1302时间读出
 * 输入  ：无
 * 输出  ：无
* 调用  ：
 *************************************/


//6. 从指定寄存器读取数据函数
//同样先操作复位线 RST 进入读取准备状态，向指定寄存器地址写入读取指令（地址加上读模式标志），接着读取数据，最后拉低复位线完成读取操作

//8. 获取 DS1302 时间函数
//从 DS1302 的秒、分、时、日、月、年等寄存器依次读取数据，存储到相应的变量中，以获取当前时间信息。
void DS1302_Readtime(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute,uint8_t *second )
{
	uint8_t mh,nl,value,suf;
	
    suf = DS1302_Read(DS1302_YEAR_REG_ADDR|0x01);
	     mh=(suf&0xf0)>>4;
     nl=suf&0x0f;
     value=mh*10+nl;		
     *year = value;	

     suf = DS1302_Read(DS1302_MONTH_REG_ADDR|0x01);
     mh=(suf&0xf0)>>4;
     nl=suf&0x0f;
     value=mh*10+nl;		
     *month = value;	
	

    suf = DS1302_Read(DS1302_DATE_REG_ADDR|0x01);
	
     mh=(suf&0xf0)>>4;
     nl=suf&0x0f;
     value=mh*10+nl;		
    *day = value;	
	
//数据处理转化十进制

 	   suf=DS1302_Read(DS1302_HOUR_REG_ADDR|0x01);    
	   if((suf&0x80)==0x80){

		 }else{

		 }
			 mh=(suf&0x30)>>4;
     nl=suf&0x0f;
     value=mh*10+nl;		
    *hour = value;	

	
	
	   suf=DS1302_Read(DS1302_MIN_REG_ADDR|0x01);
//数据处理转化十进制
     mh=(suf&0xf0)>>4;
     nl=suf&0x0f;
     value=mh*10+nl;		
    *minute = value;	

	   suf=DS1302_Read(DS1302_SEC_REG_ADDR|0x01);
//数据处理转化十进制
     mh=suf/16;
     nl=suf%16;
     value=mh*10+nl;	
	
	
	  *second = value;	
	
}







































#if 0



//4. 单字节读取函数
//依据 DS1302 的通信规则，在时钟线 SCLK 的下降沿从 DS1302 中逐位读取一个字节的数据。
uint8_t DS1302_ReadByte(void)
{
    uint8_t i, data = 0;
    for (i = 0; i < 8; i++)
    {
        data >>= 1;
        //GPIO_SetBits(DS1302_SCLK_GPIO_PORT, DS1302_SCLK_GPIO_PIN);
			DS1302_SCLK_H;
			DS1302_DELAY;
        if (DS1302_io_read)
        {
            data |= 0x80;
        }
				DS1302_DELAY;
        //GPIO_ResetBits(DS1302_SCLK_GPIO_PORT, DS1302_SCLK_GPIO_PIN);
				DS1302_SCLK_L;
				DS1302_DELAY;
    }
    return data;
}





//6. 从指定寄存器读取数据函数
//同样先操作复位线 RST 进入读取准备状态，向指定寄存器地址写入读取指令（地址加上读模式标志），接着读取数据，最后拉低复位线完成读取操作
uint8_t DS1302_Read(uint8_t regAddr)
{
    uint8_t data;
    //GPIO_ResetBits(DS1302_RST_GPIO_PORT, DS1302_RST_GPIO_PIN);
		DS1302_RST_L;
		DS1302_DELAY;
	
    //GPIO_SetBits(DS1302_RST_GPIO_PORT, DS1302_RST_GPIO_PIN);
	  DS1302_RST_H;
		DS1302_DELAY;
    DS1302_WriteByte(regAddr | DS1302_READ_MODE);
    data = DS1302_ReadByte();

    //GPIO_ResetBits(DS1302_RST_GPIO_PORT, DS1302_RST_GPIO_PIN);

		DS1302_RST_L;
		DS1302_DELAY;
    return data;
}



//7. 设置 DS1302 时间函数
//先解除写保护，然后依次将秒、分、时、日、月、年等时间数据写入对应的寄存器，最后再恢复写保护，防止误写入。
void DS1302_SetTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t month, uint8_t year)
{
    // 解除写保护
    DS1302_WriteReg(DS1302_WP_REG_ADDR, 0x00);

    // 写入时间数据到各寄存器
    DS1302_WriteReg(DS1302_SEC_REG_ADDR, second);
    DS1302_WriteReg(DS1302_MIN_REG_ADDR, minute);
    DS1302_WriteReg(DS1302_HOUR_REG_ADDR, hour);
    DS1302_WriteReg(DS1302_DATE_REG_ADDR, day);
    DS1302_WriteReg(DS1302_MONTH_REG_ADDR, month);
    DS1302_WriteReg(DS1302_YEAR_REG_ADDR, year);

    // 恢复写保护
    DS1302_WriteReg(DS1302_WP_REG_ADDR, 0x80);
}



//8. 获取 DS1302 时间函数
//从 DS1302 的秒、分、时、日、月、年等寄存器依次读取数据，存储到相应的变量中，以获取当前时间信息。
void DS1302_GetTime(uint8_t *second, uint8_t *minute, uint8_t *hour, uint8_t *day, uint8_t *month, uint8_t *year)
{
    *second = DS1302_Read(DS1302_SEC_REG_ADDR);
    *minute = DS1302_Read(DS1302_MIN_REG_ADDR);
    *hour = DS1302_Read(DS1302_HOUR_REG_ADDR);
    *day = DS1302_Read(DS1302_DATE_REG_ADDR);
    *month = DS1302_Read(DS1302_MONTH_REG_ADDR);
    *year = DS1302_Read(DS1302_YEAR_REG_ADDR);
}


#endif





















/*********************************************END OF FILE**********************/
