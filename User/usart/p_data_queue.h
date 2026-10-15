#ifndef __P_DATA_QUEUE_H_
#define __P_DATA_QUEUE_H_

#include "stm32fxxx.h"
#include "./sys/sysio.h"
#include <string.h>
#include <stdio.h>



#if 0
//缓冲队列的个数需要为2的幂
#define q_QUEUE_NODE_NUM        (16)            //缓冲队列的大小（有多少个缓冲区）
#define q_QUEUE_NODE_DATA_LEN   (2*48 )       //单个接收缓冲区大小
#endif
//缓冲队列的个数需要为2的幂
#define q_QUEUE_NODE_NUM        (16)            //缓冲队列的大小（有多少个缓冲区）
#define q_QUEUE_NODE_DATA_LEN   (2*130 )       //单个接收缓冲区大小


//队列的调试输出接口
//#define DATA_QUEUE_LOG  				SYSTEM_DEBUG
//#define DATA_QUEUE_LOG_ARRAY 	  SYSTEM_DEBUG_ARRAY

//队列的主体数据类型接口
//数据主体
typedef struct 
{
	char  *q_head; 	//缓冲区头指针	
	uint16_t q_len; //接收到的数据长度

}Q_QUEUE_DATA_TYPE;


//队列结构
typedef struct {
	int         size;  /* 缓冲区大小          */
	int         read; /* 读指针              */
	int         write;   /* 写指针  */
	int read_using;	/*正在读取的缓冲区指针*/
	int write_using;		/*正在写入的缓冲区指针*/
	Q_QUEUE_DATA_TYPE    *elems[q_QUEUE_NODE_NUM];  /* 缓冲区地址     */   
  void (*p_queuecb)(uint8_t **frame,uint16_t* length);	
} Q_QueueBuffer;


typedef struct {

Q_QueueBuffer q_rx_queue;
//char (*ptr)[q_QUEUE_NODE_DATA_LEN];
}QUEUE_DATA_BUFF;



typedef __align(4) struct str_nood_data_buff{


char node_buff[q_QUEUE_NODE_NUM][q_QUEUE_NODE_DATA_LEN];   /* 数据缓冲区          */
Q_QUEUE_DATA_TYPE  node_data[q_QUEUE_NODE_NUM];	
	
}NODE_DATA_BUFF;





//typedef union {
//NODE_DATA_BUFF nodedf;
//unsigned char bytes[sizeof(NODE_DATA_BUFF)];
//} UNION_NODE_DATA;




//输出队列的状态信息
#define p_cbPrint_size(cb)		    SYSTEM_DEBUG("\n %s :size=0x%x,read=%d, write=%d,read_using=%d,  write_using=%d \n",STR_PARAM(cb), cb.size, cb.read, cb.write,cb.read_using ,cb.write_using);

#define p_cbPrint_buff(bf)		    do{SYSTEM_DEBUG_ARRAY((uint8_t *)bf,sizeof(bf))}while(0)





Q_QUEUE_DATA_TYPE* p_cbWrite(Q_QueueBuffer *cb);
Q_QUEUE_DATA_TYPE* p_cbRead(Q_QueueBuffer *cb);
void p_cbReadFinish(Q_QueueBuffer *cb);
void p_cbWriteFinish(Q_QueueBuffer *cb);
//void cbPrint(Q_QueueBuffer *cb);
Q_QUEUE_DATA_TYPE* p_cbWriteUsing(Q_QueueBuffer *cb) ;
int p_cbIsFull(Q_QueueBuffer *cb) ; 
int p_cbIsEmpty(Q_QueueBuffer *cb) ;


void p_rx_queue_init_all(USART_TypeDef* USARTx);
void p_queue_Callback(void (*pFunc)(uint8_t **frame,uint16_t* length),QUEUE_DATA_BUFF *qdf);
void p_clear_queue_Callback(QUEUE_DATA_BUFF *qdf);

void p_rx_queue_init(QUEUE_DATA_BUFF *qdf,NODE_DATA_BUFF *ndb);
void p_pull_data_from_queue(QUEUE_DATA_BUFF *qdf);
void p_push_data_to_queue(QUEUE_DATA_BUFF *qdf,char *src_dat,uint16_t src_len);

void p_copy_data_from_queue(QUEUE_DATA_BUFF *qdf,uint8_t **frame,uint16_t* length);

void Test_get_all_data_from_queue(USART_TypeDef* USARTx);
#endif



