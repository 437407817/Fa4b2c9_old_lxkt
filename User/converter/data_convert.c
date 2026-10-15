/**
  ******************************************************************************
  * @file    data_convert.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   can驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103-霸道 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f4xx.h"
#include "./converter/data_convert.h"
//#include "./usart/bsp_usart.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
 #include "./sys/sysio.h"

const uint8_t CRCTABH[256]={
        	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
            0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
            0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
            0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
            0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
            0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
            0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
            0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
            0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
            0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
            0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
        };

const uint8_t CRCTABL[256]={ 
        	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
            0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
            0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
            0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
            0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
            0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
            0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
            0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
            0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
            0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
            0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
            0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
            0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
            0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
            0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
            0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
            0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
            0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
            0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
            0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
            0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
            0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
            0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
            0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
            0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
            0x43, 0x83, 0x41, 0x81, 0x80, 0x40
        };
				
uint16_t crc_16(uint8_t* buf, uint16_t length)
{
	uint16_t  i=0;
	uint8_t index,crcl,crch;
	uint16_t v;

	crcl=0xFF;
	crch=0xFF;
	for(i=0;i<length;i++)//
	{
		index=crcl^buf[i];
		crcl=crch^CRCTABH[index];
		crch=CRCTABL[index]; 
	}


	v=crch;
	v<<=8;
	v+=crcl;
	//v|=crcl;
	//SYSTEM_DEBUG("crc=0x%x",v);
	
	return v;
}




// 函数：将无符号整数转换为二进制字符串
void print_binary(unsigned int num) {
    char binary_str[33]; // 存储二进制表示，最多 32 位 + 1 个 '\0'
    binary_str[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        binary_str[i] = (num & 1)? '1' : '0';
        num >>= 1;
    }
    SYSTEM_DEBUG("%s\n", binary_str);
}

void print_binary1(unsigned int num) {
    char binary[33]; // 32位二进制数 + 结尾的\0
    int i = 0;

    for (i = 0; i < 32; i++) {
        binary[i] = (num & (1 << (31 - i))) ? '1' : '0';
    }

    binary[i] = '\0';

    SYSTEM_DEBUG("%s\n", binary);
}





void VpChange16HL(uint16_t* pt,uint16_t num){
	//uint16_t* vp =pt;
	
uint16_t count=num/2;
	if(num%2!=0)return;
	
	for(uint16_t i=0;i<count;i++){
		*(pt+i)=(((*(pt+i) << 8)&0xFF00) | (*(pt+i)  >> 8));
//*((pt)+i)=0;
	}

}
	
//	uint16_t a[3]={0x1234,0x5678,0x6789};
//	uint16_t *frame =&a[0];
//	SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,6," vxcxcxcxc=");
//	VpChange16HL(frame,6);
//		SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,6," vxcxcxcxc=");
//	
//	


void StructCopyAndVpReserve(uint8_t *aim_struct,uint8_t *origin_struct,uint8_t stuct_size,uint16_t *aim_struct_fromChange,uint8_t count){

	
	memmove(&*aim_struct,&*origin_struct,stuct_size);
	
	VpChange16HL((uint16_t *)aim_struct_fromChange,count);
	
	
 //VpChange16HL(BigD_GV_CommSlaveBoardState.StopParalleltChargeVol,16*12);

	
}












void StructOnlyVpReserve(uint8_t *aim_struct_fromChange,uint8_t count){

	
	
	VpChange16HL((uint16_t *)aim_struct_fromChange,count);
	
	
}



uint16_t CreateFalseRandNum(uint16_t BeginNum,uint16_t EndNum){
	
	if(EndNum>BeginNum){
return (rand() % (EndNum+1-BeginNum))+BeginNum;
	}else{
		
	return 0;
	
	}

}



void U16CovertToU8lH(uint16_t* a16,uint8_t* bL8,uint8_t* bH8){
	
(*bL8) = (uint8_t)(*a16);	
(*bH8) = (uint8_t)((*a16)>>8);
	
}

//复制数组
void copyArray(uint8_t* original , uint8_t* copied , uint8_t num){

    for (uint8_t loop = 0; loop < num; loop++) {
        copied[loop] = original[loop];
      //  printf("%x  %x  \n",  original[loop],copied[loop]);
    }

}

//数组打印
void DataArrayPrintf(uint8_t* arraydata, uint8_t num){
    for (uint8_t loop = 0; loop < num; loop++) {
        
       printf("%x ",  arraydata[loop]);
    }

}

//https://blog.csdn.net/u010761559/article/details/83508834
//HEX是256数，ASCII是字符
//HEX转ASCII函数,计算机存储是HEX存储256，但要显示成0xFF的话，需转成ASCII，不带空格
//串口软件ASCII是一个字符代表一个位7F代表两个字符，HEX是7F带表一个字符，传输过程中都是一个字符一个字符传。
uint8_t HexToAscii(uint8_t *pHexStr,uint8_t *pAscStr,uint8_t Len)
{
	char Nibble[2];
	uint8_t Buffer[2048];
	uint8_t i = 0;
	uint8_t j = 0;

	for(i=0;i<Len;i++)
	{
		Nibble[0]=pHexStr[i] >> 4 & 0X0F;
		Nibble[1]=pHexStr[i] & 0x0F;
		for(j=0;j<2;j++)
		{
			if(Nibble[j]<10)
			{
				Nibble[j]=Nibble[j]+0x30;
			}
			else if(Nibble[j]<16)
			{
				Nibble[j]=Nibble[j]-10+'A';
			}
			else
			{
				return 0;
			}
		}
		memcpy(Buffer+i*2,Nibble,2);
	}
	Buffer[2*Len]=0x00;
	memcpy(pAscStr,Buffer,2*Len);
	pAscStr[2*Len]=0x00;
	return 1;
}

// HEX字符转数字（例如 'A' → 10, '5' → 5）
static uint8_t hex_char_to_nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0; // 非法字符默认返回0
}

// 将code[16]中的HEX数据转换为ASCII字符串（结果最大8字节+终止符）
void hex_to_ascii(const char code[16], char* ascii_out, size_t out_size) {
    size_t hex_len = strlen(code);
    size_t ascii_len = hex_len / 2; // 两个HEX字符对应一个ASCII字符
    
    // 确保输出缓冲区足够大（+1 为终止符）
    if (out_size < ascii_len + 1) {
        ascii_len = out_size - 1; // 截断以适应缓冲区
    }
    
    for (size_t i = 0; i < ascii_len; i++) {
        // 每两个HEX字符转换为一个ASCII字符
        uint8_t high_nibble = hex_char_to_nibble(code[i*2]);
        uint8_t low_nibble = hex_char_to_nibble(code[i*2 + 1]);
        ascii_out[i] = (high_nibble << 4) | low_nibble;
    }
    
    ascii_out[ascii_len] = '\0'; // 添加字符串终止符
}




//ASCII转HEX函数,把显示的0x('FF''FE''FC')转计算机存储是HEX存储256，不带空格
uint8_t  AsciiToHex(uint8_t * pAscii, uint8_t** pHex, uint8_t nLen)
{
	uint16_t nHexLen = nLen / 2;
	uint8_t Nibble[2] = {0};
	int i = 0;
	int j = 0;

	if (nLen%2)
	{
		return 1;
	}

	for (i = 0; i < nHexLen; i ++)
	{
		Nibble[0] = *pAscii ++;		
		Nibble[1] = *pAscii ++;
		for (j = 0; j < 2; j ++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble [j] = Nibble[j] - '0';
			else
				return 1;//Nibble[j] = Nibble[j] - 'a' + 10;
			
		}	// for (int j = ...)
		pHex[0][i] = Nibble[0] << 4;	// Set the high nibble
		pHex[0][i] |= Nibble[1];	//Set the low nibble
	}	// for (int i = ...)
	
	
	return 0;
}

//pHex内部创建一个指针指向他，则传入一级指针即可，但使用后需要释放内存
uint8_t  AsciiToHex03(uint8_t * pAscii, uint8_t* pHex, uint8_t nLen)
{
	uint16_t nHexLen = nLen / 2;
	uint8_t Nibble[2] = {0};
	 uint8_t* pHexTMP = pHex;
	int i = 0;
	int j = 0;

	if (nLen%2)
	{
		return 1;
	}

	for (i = 0; i < nHexLen; i ++)
	{
		Nibble[0] = *pAscii ++;		
		Nibble[1] = *pAscii ++;
		for (j = 0; j < 2; j ++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble [j] = Nibble[j] - '0';
			else
				return 1;//Nibble[j] = Nibble[j] - 'a' + 10;
			
		}	// for (int j = ...)
		pHexTMP[i] = Nibble[0] << 4;	// Set the high nibble
		pHexTMP[i] |= Nibble[1];	//Set the low nibble
	}	// for (int i = ...)
	
	
	return 0;
}






//pHex由于是一维指针，并且内部没有创建指针，则传参时pHex必须是数组
char  AsciiToHex02(unsigned char * pAscii, unsigned char * pHex, int nLen)
{
	int nHexLen = nLen / 2;
	unsigned char Nibble[2] = {0};
	int i = 0;
	int j = 0;

	if (nLen%2)
	{
		return 1;
	}

	for (i = 0; i < nHexLen; i ++)
	{
		Nibble[0] = *pAscii ++;		
		Nibble[1] = *pAscii ++;
		for (j = 0; j < 2; j ++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble [j] = Nibble[j] - '0';
			else
				return 1;//Nibble[j] = Nibble[j] - 'a' + 10;
			
		}	// for (int j = ...)
		pHex[i] = Nibble[0] << 4;	// Set the high nibble
		pHex[i] |= Nibble[1];	//Set the low nibble
	}	// for (int i = ...)
	return 0;
}







//ASCII去空格函数
void  AsciiRemoveSpace01(uint8_t **pAscii,uint16_t nLen,uint16_t* retlen){
uint16_t spacenum=0;
	uint16_t i;
	for( i=0;i<nLen;i++){
	
			if ((pAscii[0][i] <= 'F' && pAscii[0][i] >= 'A')||(pAscii[0][i] <= 'f' && pAscii[0][i] >= 'a')||(pAscii[0][i] >= '0' && pAscii[0][i] <= '9'))
				pAscii[0][i-spacenum]=pAscii[0][i];
			else
				spacenum++;

//		if(pAscii[0][i]==' '){
//		spacenum++;
//		}else{
//		pAscii[0][i-spacenum]=pAscii[0][i];
//		}
}
*retlen =i-spacenum;


}



//ASCII去空格函数
void  AsciiRemoveSpace02(uint8_t *pAscii,uint16_t nLen,uint16_t* retlen){
uint16_t spacenum=0;
	uint8_t *pAsciitmp =pAscii;
	uint16_t i;
	for( i=0;i<nLen;i++){

if ((pAsciitmp[i] <= 'F' && pAsciitmp[i] >= 'A')||(pAsciitmp[i] <= 'f' && pAsciitmp[i] >= 'a')||(pAsciitmp[i] >= '0' && pAsciitmp[i] <= '9'))
		pAsciitmp[i-spacenum]=pAsciitmp[i];
else
		spacenum++;	

//		if(pAscii[i]==' '){
//		spacenum++;
//		}else{
//		pAscii[i-spacenum]=pAscii[i];
//		}

}
*retlen =i-spacenum;


}



// 定义一个函数来将ASCII字符转换为整数
uint8_t asciiToDigit(char c) {
    return c - '0';
}






//void memset_uint16_Big(uint16_t** stru_data,uint16_t data ,uint16_t count){

//	
//for(uint16_t i=0;i<count;i++){

//memset(&stru_data[0][i],(data>>8)&0xff,1);
//memset(&stru_data[0][i]+1,(data)&0xff,1);
//}

//}


//设置大端uint16数据整体为某值
void memset_uint16_Big(uint16_t* stru_data, uint16_t data, uint16_t count) {
    for (uint16_t i = 0; i < count; i++) {
        // 计算每个元素的地址
        uint8_t* elem = (uint8_t*)(&stru_data[i]);

        // 设置高字节
        elem[0] = (data >> 8) & 0xFF;
        // 设置低字节
        elem[1] = data & 0xFF;
    }
}

//设置小端uint16数据整体为某值//stru_data需要修改的地址起始指针，data需要修改成什么数，count需要修改多少个
void memset_uint16_Small(uint16_t* stru_data,uint16_t data ,uint16_t count){

    for (uint16_t i = 0; i < count; i++) {
        // 计算每个元素的地址
        uint8_t* elem = (uint8_t*)(&stru_data[i]);

        // 设置低字节
        elem[0] = (data ) & 0xFF;
        // 设置高字节
        elem[1] = (data >> 8) & 0xFF;
    }

}





void ConvertCNtoGBKhexReverse(char *org_str ,uint16_t sLen,char *aim_array){

//str="电池正常\0";
//uint16_t sLen=strlen(str);
	
	
for(uint8_t i=0;i<sLen/2;i++)
	{
		aim_array[i*2+1]=*org_str++;//0
		aim_array[i*2]=*org_str++;//0
	}

}




void ConvertCNtoGBKhex(char *org_str,uint16_t sLen,char *aim_array){

//str="电池正常\0";
//		sLen=strlen(str);
for(uint16_t i=0;i<sLen;i++)
	{
		aim_array[i*2]=*org_str++;//0
//		Buff[i*2+1]=*str++;//0
	}
//char* str


}






/**************************END OF FILE************************************/











