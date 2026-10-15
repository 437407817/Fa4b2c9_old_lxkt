#include "que.h"


int QueIsEmpty(const QueueType_t* que)
{
    if(que->head == que->tail) {
        return 1;
    }
    return 0;
}

// 定义此宏启用覆盖模式，注释掉则启用拒绝模式
#define ALLOW_OVERWRITE

int QueuePush(QueueType_t* que, unsigned char val)
{
#ifdef ALLOW_OVERWRITE
    // 覆盖模式：队列满时覆盖最早元素
    que->buf[que->tail] = val;
    que->tail = (que->tail + 1) % que->len;
    
    // 如果队列满了，移动head指针（丢弃最早元素）
    if (que->head == que->tail)
    {
        que->head = (que->head + 1) % que->len;
    }
		return QUEUE_OK;
#else
    // 拒绝模式：队列满时不写入新元素
    uint32_t next_tail = (que->tail + 1) % que->len;
    if (next_tail != que->head)  // 队列未满
    {
        que->buf[que->tail] = val;
        que->tail = next_tail;
		return QUEUE_OK;
    }
		
		return QUEUE_OVERLOAD;
    // 队列满时不执行任何操作（可根据需要添加错误处理）
#endif
}

/**
****************************************************************
* @brief   压入一组数据到队列中
* @param   queue, 队列变量指针
* @param   pArray, 待压入队列的数组地址
* @param   len, 待压入队列的元素个数
* @return  实际压入到队列的元素个数
****************************************************************
*/
uint32_t QueuePushArray(QueueType_t *queue, uint8_t *pArray, uint32_t len)
{
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        if(QueuePush(queue, pArray[i]) == QUEUE_OVERLOAD)
        {
            break;
        }
    }
    return i;
}

/**
****************************************************************
* @brief   从队列中弹出一组数据
* @param   queue, 队列变量指针
* @param   pArray, 待弹出队列的数据缓存地址
* @param   len, 待弹出队列的数据的最大长度
* @return  实际弹出数据的数量
****************************************************************
*/
uint32_t QueuePopArray(QueueType_t *queue, uint8_t *pArray, uint32_t len)
{
    uint32_t i;
    for(i = 0; i < len; i++)
    {
        if (QueuePop(queue, &pArray[i]) == QUEUE_EMPTY)
        {
            break;
        }
    }
    return i;
}







int QueuePop(QueueType_t* que, uint8_t *val)
{
    if (QueIsEmpty(que))
    {
        return QUEUE_EMPTY;
    }
    else
    {
        *val = que->buf[que->head];
        que->head = (que->head + 1) % que->len;
    }
    return QUEUE_OK;
}

int QueLen(QueueType_t *que)
{
    return (que->head <= que->tail) ? que->len - (que->tail - que->head) : que->head - que->tail;
}
