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
  * 实验平台:  
  * 论坛    :https://www.cnblogs.com/cukor-zhong-520/p/16950326.html
  * video    :https://www.bilibili.com/video/BV1nN4y1M7JK/
  *
  ******************************************************************************
  */ 

#include "./converter/data_sort.h"
//#include "./usart/bsp_usart.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>

void (*P_swapsort)(Ty* elems,int size);

typedef void (*PSWAP)(Ty* elems,int size);


void swap(Ty* elems,Ty i,Ty j) {
    Ty temp=elems[i];
    elems[i]=elems[j];
    elems[j]=temp;
}
void swaps(Ty* elems_i,Ty* elems_j) {
	
    Ty temp=*elems_i;
    *elems_i=*elems_j;
    *elems_j=temp;
}


void usualSortAscend(Ty* elems,int size){

	P_swapsort = bubSort;
		P_swapsort(elems,size);
	
	//P_swapsort = selectSort;
	//PSWAP ps=NULL;
	//ps = selectSort;

	
}

void usualSortDescend(Ty* elems,int size){


	

PSWAP ps=NULL;
ps = bubSortDescend;
ps(elems,size);
	
}

/*
*********************************************************************************************************
*	函 数 名: 冒泡排序
*	功能说明: 原理：将一段序列的最大值（最小值）拿到最左边或者最右边的操作，使用循环重复操作，（每轮排序都会少一个最大值或最小值），当最后只剩下一个数据的时候整个序列就已经排好序了。
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/



void bubSort(Ty* elems,int size) {
    for (int i = 0;i < size;size--) {    //轮
        for (int j = i + 1;j < size;j++) {    //找剩余元素中的最值
            if (elems[j] < elems[j-1]) {
                swap(elems,j,j-1);
            }
        }
    }
}
//大小排列
void bubSortDescend(Ty* elems,int size) {
    for(int i=0;i<size-1;i++)
        for(int j=i+1;j<size;j++)
            if(elems[i]<elems[j])
                swap(elems,i,j);
}


void bubSort16(Ty* elems,int length){
	uint8_t flag=1;
	uint16_t temp;
	while(length-- && flag){
		flag = 0;
		for( int i = 0;i<length;i++){
				if(elems[i+1]<elems[i]){
					flag=1;
					temp = elems[i+1];
					elems[i+1] = elems[i];
					elems[i] = temp;
				}
		}
	}

}


/*
*********************************************************************************************************
*	函 数 名: 选择排序
*	功能说明: 原理：基本思想和冒泡排序是一样的，选择排序相对于冒泡排序的优点就是减少交换次数。算法思想都是在序列中找到最大值（最小值），
*	然后存放好下次进入循环就访问不到这个最大值（最小值）。当两层循环都结束的时候序列就自然排好了。
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/


void selectSort(Ty* elems,int size) {
    for(int i=0;i<size-1;i++) {
        uint16_t minPos=i;
        for(int j=i+1;j<size;j++)
              if(elems[minPos]>elems[j])
                minPos=j;
        swap(elems,i,minPos);
    }
}



/*
*********************************************************************************************************
*	函 数 名: 插入排序
*	功能说明: 原理：基本思想还是冒泡排序，不过插入排序是两边相靠的冒泡，所以在序列部分有序的情况下，插入排序的效率要比冒泡排序效率高。
* 从序列的尾部开始往前比较，如果当前的数据小于（大于）前一个的数据就进行交换，否则进入下一次循环，直到外层循环遍历完整个序列就自然排好序了。
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/


void insertSort(Ty* elems,int size) {
    for(int i = 1;i < size;i++)
        for(int j = i;j > 0 && elems[j-1] > elems[j];j--)
            swap(elems,j-1,j);
}


////不使用交换函数
//void insertSort(Ty* elems,int size) {
//    for (int i = 1;i < size;i++) {
//        int j = i;
//        int temp = arr[j];
//        for (;j >= 1 && temp < arr[j-1];j--)
//            arr[j] = arr[j-1];
//        arr[j] = temp;
//    }
//}





/*
*********************************************************************************************************
*	函 数 名: 希尔排序
*	功能说明: 原理：希尔排序是建立在插入排序的基础上进行优化的排序算法，所以希尔排序又叫做优化版的插入排序。
* 
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/
void shellSort(Ty* elems,int size) {
    int h = 1;
    while(h < size/3) h = 3*h + 1;
    while(h >= 1) {
        for(int i = h;i < size;i++)
            for(int j = i;j >= h && elems[j] > elems[j-h];j -= h)
                swap(elems,j,j-h);
        h /= 3;
    }
}




/*
*********************************************************************************************************
*	函 数 名: 希尔排序
*	功能说明: 
* 原理：快速排序的核心思想是设立一个轴，然后其他数据都和这个轴作比较，最后把轴放在序列的中间，执行完一遍快速排序后左边的数据都比轴小，
* 右边的数据都比轴大。然后递归下去，当递归结束的时候就拍好序了。快速排序的排序很快，但是当数据形成一边倒的情况的时候就发挥不出快速排序的优势
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/
//uint8_t aa[10];
void quickSort(Ty *elems, int first, int last) {
    if ((first >= last )|| (first < 0 )|| (last < 0))
        return;
    Ty privot = elems[first];
    uint8_t i = first + 1;
    uint8_t j = first + 1;
    while (j <= last) {
        if (elems[j] < privot) {
            swaps(&elems[i], &elems[j]);
            i++;
        }
        j++;
    }
    swaps(&elems[first], &elems[i - 1]);
    quickSort(elems, first, i - 1);
    quickSort(elems, i, last);
}





/*
*********************************************************************************************************
*	函 数 名: 归并排序
*	功能说明: 
* 原理：原理：把要排序的序列拆分成多个含有一个数据的序列，然后按照从小到大（从大到小）进行合并，这样就自然的将无序的序列排好序。
* 
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/
void merge(Ty arr[],int left,int mid,int right,Ty* temp) {
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left;i <= right;i++)
        arr[i] = temp[i];
}

void merge_sort(Ty arr[],int left,int right,Ty* temp) {
    if (left >= right) return;
    int mid = left + ((right - left) >> 1);
    merge_sort(arr,left,mid,temp);
    merge_sort(arr,mid + 1,right,temp);
    merge(arr,left,mid,right,temp);
}

void mergeSort(Ty arr[],int length) {
    Ty* temp = (Ty*)malloc(sizeof(Ty)*length);
   // assert(temp);
    merge_sort(arr,0,length - 1,temp);
    free(temp);
}








/*
*********************************************************************************************************
*	函 数 名: 堆排序
*	功能说明: 
* 原理：原理：把要排序的序列拆分成多个含有一个数据的序列，然后按照从小到大（从大到小）进行合并，这样就自然的将无序的序列排好序。
* 
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/

#if 0
//外堆
//堆的结构体描述
typedef struct Heap {
    Ty* root;
    int size;
}Heap;

//创建堆内存
Heap* creatHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
   // assert(heap);
    heap->root = (Ty*)malloc(sizeof(Ty) * (capacity+1) );
    heap->size = 1;
    return heap;
}
//入堆
//先将要插入的数据插入到堆的尾部，然后向上渗透，爬到对应的位置，就把数据放进去即可
void pushHeap(Heap* heap,Ty data) {
    int current = heap->size++;
    int parent  = current >> 1; 
    heap->root[current] = data;
    while (parent) {
        if (heap->root[current] < heap->root[parent]) {
            swap(heap->root,current,parent);    
            current = parent;
            parent >>= 1;    
        }
        else break;
    }
}
//出堆
//先将堆顶元素保存下来，然后使用堆的尾部覆盖堆顶，然后往下渗透，走到对应的位置，就把数据放进去，然后返回保存的元素
Ty popHeap(Heap* heap) {
    int current = 1;
    int rchild  = 3;
    int n = --heap->size;
    Ty ret = heap->root[1];
    heap->root[1] = heap->root[n];
    while (rchild < n) {
        int small = heap->root[rchild - 1] < heap->root[rchild] ? rchild - 1 : rchild;
        if (heap->root[small] < heap->root[current]) {
            swap(heap->root,current,small);
            current = small;
            rchild  = (current << 1) + 1;
        }
        else break;
    }
    return ret;
}




#endif



//内堆
//在原来数组的基础上直接操作，其实就是入堆和出队直接结合，不需要额外申请空间
void heapify(Ty arr[],int current,int length) {
    int rchild = (current << 1) + 2;
    int large;
    while (rchild <= length && (arr[large = rchild == length ? rchild-1 : (arr[rchild-1] > arr[rchild] ? rchild-1 : rchild)] > arr[current])) {
        swap(arr,large,current);
        current = large;
        rchild  = (current << 1) + 2;
    }
}

void heapSort(Ty arr[],int length) {
    int current = length >> 1;
    while (current >= 0) heapify(arr,current--,length);
    while (length) {
        swap(arr,0,--length);
        heapify(arr,0,length);
    }
}





/*
*********************************************************************************************************
*	函 数 名: 计数排序
*	功能说明: 
* 原理：
* 
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/
void countSort(Ty arr[],int length,int max) {
    int* count = (int*)calloc(max,sizeof(int));
    for (int i = 0;i < length;i++) {
        count[arr[i]]++;
    }
    for (int i = 0,j = 0;i < max;i++) {
        while (count[i]--)
            arr[j++] = i;
    }
    free(count);
}



/*
*********************************************************************************************************
*	函 数 名: 基数排序
*	功能说明: 
* 原理：
* 
*	形    参：
*	返 回 值: 
*********************************************************************************************************
*/
void redixSort(Ty arr[], int length) {
    int i;
    int j;
    int ii;
    int jj;
    int temp[10][10];
    for (ii = 0; ii < 10; ii++)
        for (jj = 0; jj < 10; jj++)
            temp[ii][jj] = -1;
    for (int k = 10; k < 10000; k *= 10) {
        for (i = 0; i < length; i++) {
            int index = (arr[i] % k) / (k / 10);
            j = 0;
            while (temp[index][j] != -1)
                j++;
            temp[index][j] = arr[i];
        }
        i = 0;
        for (ii = 0; ii < 10; ii++) {
            for (jj = 0; jj < length && temp[ii][jj] != -1; jj++) {
                arr[i++] = temp[ii][jj];
                temp[ii][jj] = -1;
            }
        }
    }
}













/**************************END OF FILE************************************/











