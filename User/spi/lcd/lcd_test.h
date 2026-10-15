
#ifndef __LCD_TEST_H
#define	__LCD_TEST_H

#include "stm32f10x.h"




void LCD_Test(void);

void DrawTestPage(u8 *str);
void Display_ButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void menu_test(void);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);

#endif /* __LCD_TEST_H */
