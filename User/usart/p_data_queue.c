/**
  ******************************************************************************
  * @file    rx_data_queue.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   环形缓冲区，适用于接收外部数据时用作缓冲
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 IOT STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./usart/p_data_queue.h"
#include "./sys/sysio.h"
#include "./usart/bsp_485_usart.h"
#include "./usart/bsp_usart_sd.h"

QUEUE_DATA_BUFF GV_qdf_1;
NODE_DATA_BUFF GV_ndb_1;

//QUEUE_DATA_BUFF GV_qdf_485_1;
//NODE_DATA_BUFF GV_ndb_485_1;

QUEUE_DATA_BUFF GV_qdf_485_B;
NODE_DATA_BUFF GV_ndb_485_B;

/*环形缓冲队列*/

/**
  * @brief  初始化缓冲队列
  * @param  cb:缓冲队列结构体
  * @param  size: 缓冲队列的元素个数
  * @note 	初始化时还需要给cb->elems指针赋值
  */
void p_cbInit(Q_QueueBuffer *cb, int size) 
{
    cb->size  = size;	/* maximum number of elements           */
    cb->read = 0; 		/* index of oldest element              */
    cb->write   = 0; 	 	/* index at which to write new element  */
//    cb->elems = (uint8_t *)calloc(cb->size, sizeof(uint8_t));  //elems 要额外初始化
}
 
//(此函数改成了宏，在头文件)
/**
  * @brief  输出缓冲队列当前的状态信息
  * @param  cb:缓冲队列结构体
  */
//void p_cbPrint(Q_QueueBuffer *cb) 
//{
//    DATA_QUEUE_LOG("size=0x%x, read=%d, write=%d\n", cb->size, cb->read, cb->write);
//	  DATA_QUEUE_LOG("size=0x%x, read_using=%d, write_using=%d\n", cb->size, cb->read_using, cb->write_using);
//}
// 
/**
  * @brief  判断缓冲队列是(1)否(0)已满
  * @param  cb:缓冲队列结构体
  */
int p_cbIsFull(Q_QueueBuffer *cb) 
{
    return cb->write == (cb->read ^ cb->size); /* This inverts the most significant bit of read before comparison */ 
}
 
/**
  * @brief  判断缓冲队列是(1)否(0)全空
  * @param  cb:缓冲队列结构体
  */		
int p_cbIsEmpty(Q_QueueBuffer *cb) 
{
    return cb->write == cb->read; 
}

/**
  * @brief  对缓冲队列的指针加1
  * @param  cb:缓冲队列结构体
  * @param  p：要加1的指针
  * @return  返回加1的结果
  */	
int p_cbIncr(Q_QueueBuffer *cb, int p) 
{
    return (p + 1)&(2*cb->size-1); /* read and write pointers incrementation is done modulo 2*size */
}
 
/**
  * @brief  获取可写入的缓冲区指针
  * @param  cb:缓冲队列结构体
  * @return  可进行写入的缓冲区指针
  * @note  得到指针后可进入写入操作，但写指针不会立即加1，
           写完数据时，应调用cbWriteFinish对写指针加1
  */
Q_QUEUE_DATA_TYPE* p_cbWrite(Q_QueueBuffer *cb) 
{
    if (p_cbIsFull(cb)) /* full, overwrite moves read pointer */
    {
			return NULL;
		}		
		else
		{
			//当wriet和write_using相等时，表示上一个缓冲区已写入完毕，需要对写指针加1
			if(cb->write == cb->write_using)
			{
				cb->write_using = p_cbIncr(cb, cb->write); //未满，则增加1
			}
		}
		
	return  cb->elems[cb->write_using&(cb->size-1)];
}



/**
  * @brief 数据写入完毕，更新写指针到缓冲结构体
  * @param  cb:缓冲队列结构体
  */
void p_cbWriteFinish(Q_QueueBuffer *cb)
{
    cb->write = cb->write_using;
}
 
/**
  * @brief  获取可读取的缓冲区指针
  * @param  cb:缓冲队列结构体
  * @return  可进行读取的缓冲区指针
  * @note  得到指针后可进入读取操作，但读指针不会立即加1，
					 读取完数据时，应调用cbReadFinish对读指针加1
  */
Q_QUEUE_DATA_TYPE* p_cbRead(Q_QueueBuffer *cb) 
{
		if(p_cbIsEmpty(cb))
			return NULL;
		
	//当read和read_using相等时，表示上一个缓冲区已读取完毕(即已调用cbReadFinish)，
	//需要对写指针加1
	if(cb->read == cb->read_using)	
		cb->read_using = p_cbIncr(cb, cb->read);
	
	return cb->elems[cb->read_using&(cb->size-1)];
}


/**
  * @brief 数据读取完毕，更新读指针到缓冲结构体
  * @param  cb:缓冲队列结构体
  */
void p_cbReadFinish(Q_QueueBuffer *cb) 
{	
		//重置当前读完的数据节点的长度
		cb->elems[cb->read_using&(cb->size-1)]->q_len = 0;
	
    cb->read = cb->read_using;
}



//队列的指针指向的缓冲区全部销毁
void p_camera_queue_free(NODE_DATA_BUFF *ndb)
{
    uint32_t i = 0;

    for(i = 0; i < q_QUEUE_NODE_NUM; i ++)
    {
        if((ndb)->node_data[i].q_head != NULL)
        {
					//若是动态申请的空间才要free
//            free(node_data[i].q_head);
            (ndb)->node_data[i].q_head = NULL;
        }
    }

    return;
}


/**
  * @brief  缓冲队列初始化，分配内存,使用缓冲队列时，
  * @param  无
  * @retval 无
  */
void p_rx_queue_init(QUEUE_DATA_BUFF *qdf,NODE_DATA_BUFF *ndb)
{
  uint32_t i = 0;

  memset((ndb)->node_data, 0, q_QUEUE_NODE_NUM * sizeof(Q_QUEUE_DATA_TYPE));
		 
	/*初始化缓冲队列*/
	p_cbInit(&(qdf)->q_rx_queue,q_QUEUE_NODE_NUM);

    for(i = 0; i < q_QUEUE_NODE_NUM; i ++)
    {
        (ndb)->node_data[i].q_head = (ndb)->node_buff[i];
        
        /*初始化队列缓冲指针，指向实际的内存*/
        (qdf)->q_rx_queue.elems[i] = &(ndb)->node_data[i];
        
        //DATA_QUEUE_LOG("node_data[i].q_head=0x%x,\r\nq_rx_queue.elems[i] =0x%x", (uint32_t)node_data[i].q_head,(uint32_t)q_rx_queue.elems[i]->q_head);

        memset((ndb)->node_data[i].q_head, 0, q_QUEUE_NODE_DATA_LEN);
    }
		
	p_cbPrint_size((qdf)->q_rx_queue);	
}







/**
  * @brief  往队列中写入数据的样例
  */
void p_push_data_to_queue(QUEUE_DATA_BUFF *qdf,char *src_dat,uint16_t src_len)
{
	Q_QUEUE_DATA_TYPE *data_p;
	uint8_t i;
	
	for(i=0;i<src_len;i++)
	{
		/*获取写缓冲区指针，准备写入新数据*/
		data_p = p_cbWrite(&(qdf)->q_rx_queue);
		
		if (data_p != NULL)	//若缓冲队列未满，开始传输
		{		
			//往缓冲区写入数据，如使用串口接收、dma写入等方式
			*(data_p->q_head + i) = src_dat[i];
				data_p->q_len++;
			SYSTEM_DEBUG("\r\ndata_p->q_len =%d",data_p->q_len);
		}else return;	
		
		p_cbPrint_size((qdf)->q_rx_queue);	
	}	
	
	/*写入缓冲区完毕*/
	p_cbWriteFinish(&(qdf)->q_rx_queue);
	
	p_cbPrint_size((qdf)->q_rx_queue);	

}

/**
***********************************************************
* @brief 从队列中取数据的样例
* @param qdf缓冲队列
* @return 
***********************************************************
*/

void p_pull_data_from_queue1(QUEUE_DATA_BUFF *qdf)
{
	Q_QUEUE_DATA_TYPE *rx_data;	
		uint8_t *frame = NULL;
	/*从缓冲区读取数据，进行处理，*/
	rx_data = p_cbRead(&(qdf)->q_rx_queue); 

	if(rx_data != NULL)//缓冲队列非空
	{		
		//加上字符串结束符，方便直接输出字符串
		*(rx_data->q_head+rx_data->q_len) = '\0';
		
	//	SYSTEM_DEBUG("received data：%s",rx_data->q_head);
	//	SYSTEM_DEBUG_ARRAY((uint8_t*)rx_data->q_head,rx_data->q_len);
		SYSTEM_DEBUG();
		frame = (uint8_t *)malloc(rx_data->q_len);
		
    memcpy(frame,rx_data->q_head,rx_data->q_len);
		*(frame+rx_data->q_len) = '\0';
		SYSTEM_DEBUG("received data：%s  ,length: %d",frame,rx_data->q_len);
		SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,rx_data->q_len,"");
	free(frame);
	frame = NULL;
		//使用完数据必须调用cbReadFinish更新读指针
		p_cbReadFinish(&(qdf)->q_rx_queue);
	}
}

//static void (*pProcFunc)(QUEUE_DATA_BUFF *qdf); 





/**
  * @brief  从队列中取数据的样例
  */
void p_pull_data_from_queue(QUEUE_DATA_BUFF *qdf)
{
	
uint8_t *frame = NULL;

uint16_t leng=0;//必须为0

p_copy_data_from_queue(qdf,&frame,&leng);
	
	if(qdf->q_rx_queue.p_queuecb != NULL){
	(*qdf->q_rx_queue.p_queuecb)(&frame,&leng);
	}
	
			SYSTEM_DEBUG("usart test received length: %d",leng);
	     SYSTEM_DEBUG("usart test received data：%s  ,length: %d",frame,leng);
      SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)frame,leng,"");
		free(frame);
	frame = NULL;
	leng=0;
}

void p_queue_Callback(void (*pFunc)(uint8_t **frame,uint16_t* length),QUEUE_DATA_BUFF *qdf){
qdf->q_rx_queue.p_queuecb=pFunc;

}

void p_clear_queue_Callback(QUEUE_DATA_BUFF *qdf){
qdf->q_rx_queue.p_queuecb=NULL;

}
//void p_ReturnDataToBack(uint8_t **frame,uint16_t* length){

//Usart_SendArray( USART_485_A, *frame, *length);

//}






/**
  * @brief  frame：传入指针来获取队列的值，length：获取队列的长度
  * @param  无
  * @retval 无 https://blog.csdn.net/qq_33706673/article/details/84669784
  */
void p_copy_data_from_queue(QUEUE_DATA_BUFF *qdf,uint8_t **frame,uint16_t* length)
{
	Q_QUEUE_DATA_TYPE *rx_data;	
	//	uint8_t *frame = NULL;
	/*从缓冲区读取数据，进行处理，*/
	rx_data = p_cbRead(&(qdf)->q_rx_queue); 

	if(rx_data != NULL)//缓冲队列非空
	{		

		*length=rx_data->q_len;

		*frame = (uint8_t *)malloc(rx_data->q_len);
		
memcpy(*frame,rx_data->q_head,rx_data->q_len);
		*(*frame+rx_data->q_len) = '\0';
//		SYSTEM_DEBUG(" ==xxxxx====length: %d",*length);
//		SYSTEM_DEBUG("received data：%s  ,length: %d",*frame,rx_data->q_len);
//		SYSTEM_DEBUG_ARRAY((uint8_t*)*frame,rx_data->q_len);
//	free(frame);
//	frame = NULL;
		//使用完数据必须调用cbReadFinish更新读指针
		p_cbReadFinish(&(qdf)->q_rx_queue);
	}
}

/**
***********************************************************
* @brief 初始化函数
* @param USARTx，串口号
* @return 
***********************************************************
*/
void p_rx_queue_init_all(USART_TypeDef* USARTx){
if(USARTx == USARTx_A)
{
	p_rx_queue_init(&GV_qdf_1,&GV_ndb_1);
}

//if(USARTx == USART_485_A)
//{
////	p_rx_queue_init(&GV_qdf_485_1,&GV_ndb_485_1);
//	
//}


if(USARTx == USART_485_B)
{
	p_rx_queue_init(&GV_qdf_485_B,&GV_ndb_485_B);
	
}



}


void Test_get_all_data_from_queue(USART_TypeDef* USARTx){


if(USARTx == USARTx_A)
{
	p_pull_data_from_queue(&GV_qdf_1);

	//p_cbPrint_buff(GV_ndb_1.node_buff[0]);
	//SYSTEM_DEBUG(" 0: %d = %d = %d = %d ",GV_ndb_1.node_buff[0][0],GV_ndb_1.node_buff[0][1],GV_ndb_1.node_buff[0][2],GV_ndb_1.node_buff[0][3]);

}

//if(USARTx == USART_485_A)
//{
//	
//	p_pull_data_from_queue(&GV_qdf_485_1);
//	//p_cbPrint_size(GV_qdf_485_1.q_rx_queue);
//	//p_cbPrint_buff(GV_ndb_485_1.node_buff[0]);
////p_cbPrint_buff(GV_ndb_485_1.node_buff[1]);p_cbPrint_buff(GV_ndb_485_1.node_buff[2]);p_cbPrint_buff(GV_ndb_485_1.node_buff[3]);
//	
//}


if(USARTx == USART_485_B)
{
	
	p_pull_data_from_queue(&GV_qdf_485_B);
	//p_cbPrint_size(GV_qdf_485_1.q_rx_queue);
	//p_cbPrint_buff(GV_ndb_485_1.node_buff[0]);
//p_cbPrint_buff(GV_ndb_485_1.node_buff[1]);p_cbPrint_buff(GV_ndb_485_1.node_buff[2]);p_cbPrint_buff(GV_ndb_485_1.node_buff[3]);
	
}


}




