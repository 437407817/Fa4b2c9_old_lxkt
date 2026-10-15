#ifndef __DATA_SORT_H
#define	__DATA_SORT_H

#include "stm32fxxx.h"







#define Ty uint16_t // 以整型为例

void usualSortAscend(Ty* elems,int size);
void usualSortDescend(Ty* elems,int size);

void bubSort(Ty* elems,int size);
void bubSortDescend(Ty* elems,int size) ;

void selectSort(Ty* elems,int size);


void insertSort(Ty* elems,int size);

void shellSort(Ty* elems,int size);



#endif







