#ifndef __RX_DATA_QUEUE_H_
#define __RX_DATA_QUEUE_H_

#include "stm32fxxx.h"
#include "./sys/sysio.h"
#include <string.h>
#include <stdio.h>

//缓冲队列的个数需要为2的幂
#define QUEUE_NODE_NUM        (16)            //缓冲队列的大小（有多少个缓冲区）
#define QUEUE_NODE_DATA_LEN   (2*48 )       //单个接收缓冲区大小



//队列的调试输出接口
#define DATA_QUEUE_LOG  				SYSTEM_DEBUG
#define DATA_QUEUE_LOG_ARRAY 	  SYSTEM_DEBUG_ARRAY

//队列的主体数据类型接口
//数据主体
typedef struct 
{
	char  *head; 	//缓冲区头指针	
	uint16_t len; //接收到的数据长度

}QUEUE_DATA_TYPE;


//队列结构
typedef struct {
	int         size;  /* 缓冲区大小          */
	int         read; /* 读指针              */
	int         write;   /* 写指针  */
	int read_using;	/*正在读取的缓冲区指针*/
	int write_using;		/*正在写入的缓冲区指针*/
	QUEUE_DATA_TYPE    *elems[QUEUE_NODE_NUM];  /* 缓冲区地址                   */
} QueueBuffer;


extern QueueBuffer rx_queue;






//输出队列的状态信息
#define cbPrint(cb)		    DATA_QUEUE_LOG("size=0x%x, read=%d, write=%d\n", cb.size, cb.read, cb.write);\
	  DATA_QUEUE_LOG("size=0x%x, read_using=%d, write_using=%d\n", cb.size, cb.read_using, cb.write_using);


QUEUE_DATA_TYPE* cbWrite(QueueBuffer *cb);
QUEUE_DATA_TYPE* cbRead(QueueBuffer *cb);
void cbReadFinish(QueueBuffer *cb);
void cbWriteFinish(QueueBuffer *cb);
//void cbPrint(QueueBuffer *cb);
QUEUE_DATA_TYPE* cbWriteUsing(QueueBuffer *cb) ;
int cbIsFull(QueueBuffer *cb) ; 
int cbIsEmpty(QueueBuffer *cb) ;

void rx_queue_init(void);
void pull_data_from_queue(void);
void push_data_to_queue(char *src_dat,uint16_t src_len);
void copy_data_from_queue(uint8_t **frame,uint16_t* length);

#endif



