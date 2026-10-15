/**
  ******************************************************************************
  * @file    __TEST_SEGGERRTT_.c
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
#include "./test/bsp_test_SeggerRTT.h"  




#include <stdio.h>

#include "./SeggerRTT/SEGGER_RTT.h"
  #include "./sys/bsp_systime.h"   
#include "./test/bsp_test_iic.h"   
#include "./converter/data_convert.h"

volatile int _Cnt;
volatile int _Delay;

/*********************************************************************
*
*       main
*/



static void SeggerRTT_simple_Test(void);




void SeggerRTT_Test(void) {
	uint8_t NumDataToRead=16;
	uint8_t I2c_Buf_ReadTmp[16],I2c_Buf_ReadAsciiTmp[16];
	uint16_t j=0;
		j=NumDataToRead;
sEE_ReadBuffer(I2c_Buf_ReadTmp, 0x0000, (uint16_t *)(&NumDataToRead));
SEGGER_RTT_Write(0,I2c_Buf_ReadTmp,j);

	HexToAscii(I2c_Buf_ReadTmp,I2c_Buf_ReadAsciiTmp,16);
	printf("SeggerRTT_Test 01");
	SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED" SeggerRTT_Test 01 \n");
	SEGGER_RTT_Write(0,I2c_Buf_ReadAsciiTmp,j*2);
	printf("SeggerRTT_Test 02");
	SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED" SeggerRTT_Test 02 \n");
	SEGGER_RTT_printf(0,(char *)I2c_Buf_ReadAsciiTmp);
		char *str1 = "你好Hello, world1!\n";
	char str2[23] = "Hello, world2!\n";
	SEGGER_RTT_printf(0,str1);
	SEGGER_RTT_printf(0,str2);

I2C_ReadDataShow(0x0000,j);
#if 0
SEGGER_RTT_WriteString(0,
                       RTT_CTRL_RESET"Red: " \
                       RTT_CTRL_TEXT_BRIGHT_RED"This text is red. " \
                       RTT_CTRL_TEXT_BLACK"" \
                       RTT_CTRL_BG_BRIGHT_RED"This background is red. " \
                       RTT_CTRL_RESET"Normal text again."
                      );
		
#endif

		

}

void SeggerRTT_Test1(void){

SeggerRTT_simple_Test();

}







































static void SeggerRTT_simple_Test(void) {
  int r;
  int CancelOp;

  do {
    _Cnt = 0;
SEGGER_RTT_WriteString(0,
                       RTT_CTRL_RESET"Red: " \
                       RTT_CTRL_TEXT_BRIGHT_RED"This text is red. " \
                       RTT_CTRL_TEXT_BLACK"" \
                       RTT_CTRL_BG_BRIGHT_RED"This background is red. " \
                       RTT_CTRL_RESET"Normal text again."
                      );
		
	SEGGER_RTT_printf(0, "%sTime:%s%s %.7d\n",
                      RTT_CTRL_RESET,
                      RTT_CTRL_BG_BRIGHT_RED,
                      RTT_CTRL_TEXT_BRIGHT_WHITE,
                      1111111
                 );	
//
// Clear the terminal.
// The first line will not be shown after this command.
//
	SEGGER_RTT_WriteString(0, RTT_CTRL_CLEAR);

SEGGER_RTT_printf(0, "%sTime: %s%s%.7d\n",
                      RTT_CTRL_RESET,
                      RTT_CTRL_BG_BRIGHT_RED,
                      RTT_CTRL_TEXT_BRIGHT_WHITE,
                      2222222
                 );
								 
    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n");
    SEGGER_RTT_WriteString(0, "Press <1> to continue in blocking mode (Application waits if necessary, no data lost)\r\n");
    SEGGER_RTT_WriteString(0, "Press <2> to continue in non-blocking mode (Application does not wait, data lost if fifo full)\r\n");
    do {
      r = SEGGER_RTT_WaitKey();
    } while ((r != '1') && (r != '2'));
    if (r == '1') {
      SEGGER_RTT_WriteString(0, "\r\nSelected <1>. Configuring RTT and starting...\r\n");
      SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
    } else {
      SEGGER_RTT_WriteString(0, "\r\nSelected <2>. Configuring RTT and starting...\r\n");
      SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    }
    CancelOp = 0;
    do {
      //for (_Delay = 0; _Delay < 10000; _Delay++);
      SEGGER_RTT_printf(0, "Count: %d. Press <Space> to get back to menu.\r\n", _Cnt++);
      r = SEGGER_RTT_HasKey();
      if (r) {
        CancelOp = (SEGGER_RTT_GetKey() == ' ') ? 1 : 0;
      }
      //
      // Check if user selected to cancel the current operation
      //
      if (CancelOp) {
        SEGGER_RTT_WriteString(0, "Operation cancelled, going back to menu...\r\n");
        break;
      }
    } while (1);
    SEGGER_RTT_GetKey();
    SEGGER_RTT_WriteString(0, "\r\n");
  } while (1);
}





/*********************************************END OF FILE**********************/
