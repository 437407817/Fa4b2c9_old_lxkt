#ifndef QUE_H
#define QUE_H
#include <stdint.h>


typedef struct {
	 uint32_t head;
   uint32_t tail;
	 uint32_t len;
   unsigned char  *buf;
  
}QueueType_t;


typedef enum
{
	QUEUE_OK = 0,       //队列正常
	QUEUE_ERROR,        //队列错误
	QUEUE_OVERLOAD,     //队列已满
	QUEUE_EMPTY         //队列已空
} QueueStatus_t;


/* 使用宏创建队列 */
#define creat_que(que_name, len)	\
    unsigned char que_buf_##que_name[len] = {0}; \
    QueueType_t que_##que_name = { len, 0, 0,que_buf_##que_name}; \
    static QueueType_t* que_name = &que_##que_name
			
		
		
		

int QueIsEmpty(const QueueType_t* que);
int QueuePush(QueueType_t* que, unsigned char val);
int QueuePop(QueueType_t* que, unsigned char *val);
/**
****************************************************************
* @brief   压入一组数据到队列中
* @param   queue, 队列变量指针
* @param   pArray, 待压入队列的数组地址
* @param   len, 待压入队列的元素个数
* @return  实际压入到队列的元素个数
****************************************************************
*/
uint32_t QueuePushArray(QueueType_t *queue, uint8_t *pArray, uint32_t len);

/**
****************************************************************
* @brief   从队列中弹出一组数据
* @param   queue, 队列变量指针
* @param   pArray, 待弹出队列的数据缓存地址
* @param   len, 待弹出队列的数据的最大长度
* @return  实际弹出数据的数量
****************************************************************
*/
uint32_t QueuePopArray(QueueType_t *queue, uint8_t *pArray, uint32_t len);
		
		
		
		
int QueLen(QueueType_t *que);

#endif
