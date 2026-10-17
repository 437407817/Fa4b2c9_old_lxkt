/**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  fire
  * @version V1.1
  * @date    2026-xx-xx
  * @brief   CAN驱动，适配STM32F429 PCLK1=45MHz(系统时钟180M)
  *          时序和原版可运行例程保持一致：总TQ=9, SJW=2tq
  ******************************************************************************
  * @attention
  * 实验平台:野火  STM32 F429 开发板
  ******************************************************************************
  */
#include "./can/bsp_can.h"
#include <string.h>
 #include "./sys/sysio.h"
CAN_RxFifo_t g_canRxFifo;

/**
 * @brief 统一CAN GPIO初始化函数，引脚全部由头文件宏定义
 */
void CAN_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    // 开启GPIO时钟
    RCC_AHB1PeriphClockCmd(CAN_RX_GPIO_RCC, ENABLE);
    if(CAN_RX_GPIO_RCC != CAN_TX_GPIO_RCC)
    {
        RCC_AHB1PeriphClockCmd(CAN_TX_GPIO_RCC, ENABLE);
    }
    // 开启CAN外设时钟
    RCC_APB1PeriphClockCmd(RCC_APBxPeriph_CANx, ENABLE);

    // RX引脚配置
    GPIO_InitStruct.GPIO_Pin = CAN_RX_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStruct);

    // TX引脚配置
    GPIO_InitStruct.GPIO_Pin = CAN_TX_PIN;
    GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStruct);

    // 复用功能映射
    GPIO_PinAFConfig(CAN_RX_GPIO_PORT, CAN_RX_PIN_SOURCE, CAN_AF_NUM);
    GPIO_PinAFConfig(CAN_TX_GPIO_PORT, CAN_TX_PIN_SOURCE, CAN_AF_NUM);
}

/**
 * @brief CAN内核初始化，波特率由bsp_can.h宏配置
 *        PCLK1 = 45MHz(SYSCLK=180M)，位时序总TQ=9，和原版可用例程完全一致
 */
void CANx_Mode_Init(void)
{
    CAN_InitTypeDef CAN_InitStruct;
    uint16_t prescaler;
    uint8_t bs1,bs2;

    CAN_DeInit(CANx);
#if (!CAN_SELECT_1)
    CAN_SlaveStartBank(14);
#endif

/*
PCLK1=45MHz，总位时间 = 1(SYNC_SEG)+BS1+BS2 = 9TQ
公式：波特率 = 45000000 / prescaler / 9
*/
#if (CAN_BAUD_CFG == CAN_BAUD_1M)
    prescaler = 5;  bs1=CAN_BS1_5tq;  bs2=CAN_BS2_3tq;
#elif (CAN_BAUD_CFG == CAN_BAUD_500K)
    prescaler = 10; bs1=CAN_BS1_5tq;  bs2=CAN_BS2_3tq;
#elif (CAN_BAUD_CFG == CAN_BAUD_250K)
    prescaler = 20; bs1=CAN_BS1_5tq;  bs2=CAN_BS2_3tq;
#elif (CAN_BAUD_CFG == CAN_BAUD_125K)
    prescaler = 40; bs1=CAN_BS1_5tq;  bs2=CAN_BS2_3tq;
#else
#error "CAN_BAUD_CFG 未定义或者配置错误，请在bsp_can.h选择波特率"
#endif

    CAN_InitStruct.CAN_Prescaler = prescaler;
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStruct.CAN_SJW = CAN_SJW_2tq;    // 和老好使程序一致 SJW=2tq
    CAN_InitStruct.CAN_BS1 = bs1;
    CAN_InitStruct.CAN_BS2 = bs2;

    CAN_InitStruct.CAN_TTCM = DISABLE;
    CAN_InitStruct.CAN_ABOM = ENABLE;    // 自动离线管理
    CAN_InitStruct.CAN_AWUM = ENABLE;    // 自动唤醒（原版开启）
    CAN_InitStruct.CAN_NART = DISABLE;   // 禁止报文自动重传
    CAN_InitStruct.CAN_RFLM = DISABLE;   // FIFO不锁定
    CAN_InitStruct.CAN_TXFP = DISABLE;   // 发送优先级由ID决定

    CAN_Init(CANx, &CAN_InitStruct);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = CANx_RX_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

//    CAN_ITConfig(CANx, CANx_IT_FMPx, ENABLE);

    // 清空接收FIFO
    g_canRxFifo.wr_ptr = 0;
    g_canRxFifo.rd_ptr = 0;
    g_canRxFifo.count = 0;
}

/**
 * @brief 配置过滤器Bank，支持掩码模式/列表模式，32bit扩展帧过滤
 * @param bankNum 过滤器编号 CAN1(0~13) CAN2(14~27)
 * @param filterMode 掩码/列表模式
 * @param id1 第一个扩展ID(29bit)
 * @param id2 列表模式：第二个ID；掩码模式填0
 * @param mask 掩码模式：掩码，列表模式填0
 * @retval 0
 * @note 修复原来ID移位BUG，标准库32bit扩展帧过滤器正确组装
 */
uint8_t CANx_SetFilterBank(uint8_t bankNum, CAN_Filter_Mode_t filterMode,
                           uint32_t id1, uint32_t id2, uint32_t mask)
{
    CAN_FilterInitTypeDef filterInit;
    uint32_t tempId1,tempId2,tempMask;

    filterInit.CAN_FilterNumber = bankNum;
    filterInit.CAN_FilterScale = CAN_FilterScale_32bit;

    // ===== 野火原版标准算法：扩展ID左移3位，低3位：IDE(bit2),RTR(bit1),bit0保留=====
    // 扩展帧数据帧：IDE=1, RTR=0
    tempId1  = (id1 << 3) | CAN_ID_EXT | CAN_RTR_DATA;
    tempMask = (mask << 3) | (CAN_ID_EXT | CAN_RTR_DATA); //掩码也要同步左移3位

    if(filterMode == CAN_FILTER_MASK_MODE)
    {
        filterInit.CAN_FilterMode = CAN_FilterMode_IdMask;
        filterInit.CAN_FilterIdHigh  = (tempId1  & 0xFFFF0000U) >> 16U;
        filterInit.CAN_FilterIdLow   = tempId1  & 0xFFFFU;

        filterInit.CAN_FilterMaskIdHigh = (tempMask & 0xFFFF0000U) >>16U;
        filterInit.CAN_FilterMaskIdLow  = tempMask & 0xFFFFU;
    }
    else
    {
        //列表模式
        tempId2 = (id2 <<3) | CAN_ID_EXT | CAN_RTR_DATA;
        filterInit.CAN_FilterMode = CAN_FilterMode_IdList;
        filterInit.CAN_FilterIdHigh  = (tempId1  & 0xFFFF0000U) >> 16U;
        filterInit.CAN_FilterIdLow   = tempId1  & 0xFFFFU;

        filterInit.CAN_FilterMaskIdHigh = (tempId2 & 0xFFFF0000U) >>16U;
        filterInit.CAN_FilterMaskIdLow  = tempId2 & 0xFFFFU;
    }

    filterInit.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    filterInit.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&filterInit);
    return 0;
}

/**
 * @brief 发送扩展数据帧
 * @param extId 29位扩展ID
 * @param pBuf 数据缓存指针
 * @param len 数据长度0~8
 * @retval 0成功 1无邮箱 2参数错误
 */
uint8_t CANx_SendExtFrame(uint32_t extId, uint8_t *pBuf, uint8_t len)
{
    CanTxMsg TxMsg;
    uint8_t mailbox;
    if(pBuf == NULL || len > 8)
    {
        return 2;
    }
    TxMsg.ExtId = extId;
    TxMsg.IDE = CAN_ID_EXT;
    TxMsg.RTR = CAN_RTR_DATA;
    TxMsg.DLC = len;
    for(uint8_t i=0; i<len; i++)
    {
        TxMsg.Data[i] = pBuf[i];
    }
    mailbox = CAN_Transmit(CANx, &TxMsg);
    if(mailbox == CAN_TxStatus_NoMailBox)
        return 1;
    return 0;
}

/**
 * @brief 发送扩展远程帧
 * @param extId 29bit扩展ID
 * @param reqDlc 请求长度0~8
 * @retval 0成功 1无邮箱 2参数错误
 */
uint8_t CANx_SendExtRemoteFrame(uint32_t extId, uint8_t reqDlc)
{
    CanTxMsg TxMsg;
    uint8_t mailbox;
    if(reqDlc > 8)
    {
        return 2;
    }
    TxMsg.ExtId = extId;
    TxMsg.IDE = CAN_ID_EXT;
    TxMsg.RTR = CAN_RTR_REMOTE;
    TxMsg.DLC = reqDlc;
    mailbox = CAN_Transmit(CANx, &TxMsg);
    if(mailbox == CAN_TxStatus_NoMailBox)
        return 1;
    return 0;
}

/* ========== 接收环形FIFO底层函数，临界区改用全局中断锁 ========== */
uint8_t CANx_RxFifo_Push(CAN_RxMsg_t *msg)
{
    __disable_irq();   // 全局关中断临界区
    uint8_t ret = 0;
    if(g_canRxFifo.count >= CAN_RX_FIFO_DEPTH)
    {
        ret = 1; //FIFO满，丢帧
    }
    else
    {
        memcpy(&g_canRxFifo.buf[g_canRxFifo.wr_ptr], msg, sizeof(CAN_RxMsg_t));
        g_canRxFifo.wr_ptr++;
        if(g_canRxFifo.wr_ptr >= CAN_RX_FIFO_DEPTH)
            g_canRxFifo.wr_ptr = 0;
        g_canRxFifo.count++;
    }
    __enable_irq();
    return ret;
}

uint8_t CANx_RxFifo_Pop(CAN_RxMsg_t *msg)
{
    __disable_irq();//rtos  taskENTER_CRITICAL(); // 进入临界区  不能在中断里直接用 taskENTER_CRITICAL()
    uint8_t ret = 0;
    if(g_canRxFifo.count == 0)
    {
        ret = 1;
    }
    else
    {
        memcpy(msg, &g_canRxFifo.buf[g_canRxFifo.rd_ptr], sizeof(CAN_RxMsg_t));
        g_canRxFifo.rd_ptr++;
        if(g_canRxFifo.rd_ptr >= CAN_RX_FIFO_DEPTH)
            g_canRxFifo.rd_ptr = 0;
        g_canRxFifo.count--;
    }
    __enable_irq();//taskEXIT_CRITICAL();  // 退出临界区
    return ret;
}

uint8_t CANx_RxFifo_IsEmpty(void)
{
    __disable_irq();
    uint8_t empty = (g_canRxFifo.count == 0);
    __enable_irq();
    return empty;
}

void CAN1_RX0_IRQHandler(void)
{
	SYSTEM_DEBUG("-------CAN--IT-------");
    if(CAN_GetITStatus(CANx, CANx_IT_FMPx) != RESET)
    {
        CAN_RxMsg_t rxMsg;
        CanRxMsg rawRx;
        CAN_Receive(CANx, CAN_FIFO0, &rawRx);

        rxMsg.StdId = rawRx.StdId;
        rxMsg.ExtId = rawRx.ExtId;
        rxMsg.IDE   = rawRx.IDE;
        rxMsg.RTR   = rawRx.RTR;
        rxMsg.DLC   = rawRx.DLC;
//			SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)rawRx.Data,8," CAN IT DATA :");
        if(rxMsg.DLC > 8) rxMsg.DLC = 8;
        for(uint8_t i=0; i<rxMsg.DLC; i++)
        {
            rxMsg.Data[i] = rawRx.Data[i];
        }
        CANx_RxFifo_Push(&rxMsg);
				CAN_ClearITPendingBit(CANx, CAN_IT_FMP0); // 手动清除FMP0中断标志！！
    }
		    // 清除错误相关中断标志，防止反复进中断
   
}
#include "./service/CanFun.h"
void CANx_config_Init(void)
{
    CAN_GPIO_Init();
    CANx_Mode_Init();
    //配置过滤器bank0，接收ID=0x18000001，掩码完全匹配
    CANx_SetFilterBank(0, CAN_FILTER_MASK_MODE, CAN_GET_ID_1, 0, 0x1FFFFFFFU);
	// 测试时改用全0掩码，放行所有扩展帧
//CANx_SetFilterBank(0, CAN_FILTER_MASK_MODE, 0x1314, 0, 0x1FFFFFFFU);
	//mask=0，掩码全部位为0，全部报文放过
//CANx_SetFilterBank(0, CAN_FILTER_MASK_MODE, 0, 0, 0x00000000U);
	CAN_ITConfig(CANx, CANx_IT_FMPx, ENABLE);
	
	
	//注册回调：收到CAN_GET_ID_1，就自动执行 User_CanGetId1Process
CAN_SetRxGetId1Callback(User_CanGetId1Process);
}

// 保存外部回调函数，初始为NULL
static CAN_RxCallbackFunc g_canGetId1Callback = NULL;

/**
 * @brief 注册CAN_GET_ID_1报文的回调处理函数
 * @param cb 外部业务处理函数指针，传NULL取消回调
 */
void CAN_SetRxGetId1Callback(CAN_RxCallbackFunc cb)
{
    g_canGetId1Callback = cb;
}


void CANx_IT_DataDispose(void){
    CAN_RxMsg_t rxMessage; // 定义一个接收消息结构体变量
        // 检查 FIFO 中是否有数据（也可以直接用 CANx_RxFifo_Pop 的返回值判断）
        if (CANx_RxFifo_Pop(&rxMessage) == 0)
        {
            // 成功从 FIFO 弹出一帧数据！
            
            // 1. 判断是扩展帧还是标准帧
            if (rxMessage.IDE == CAN_ID_EXT)
            {
                // 打印或处理 29 位扩展 ID
                // rxMessage.ExtId 即为扩展 ID
                // rxMessage.DLC 为数据长度 (0~8)
                // rxMessage.Data[] 为数据内容
                
                // 示例：如果你配置的 ID 是 0x18000001
                if (rxMessage.ExtId == CAN_GET_ID_1)
                {
                    // 处理该报文的业务逻辑
									                    // 将Data数组、DLC长度传入外部业务函数
                    g_canGetId1Callback(rxMessage.Data, rxMessage.DLC);
												
//									SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)rxMessage.Data,8," CAN GET DATA :");
                }
//								SYSTEM_DEBUG_ARRAY_MESSAGE((uint8_t*)rxMessage.Data,8," CAN GET DATA :");
            }
            else
            {
                // 标准帧处理 (如果你的过滤器也放行了标准帧)
                // rxMessage.StdId
            }

            // 示例：打印收到的数据
            // printf("ExtId: 0x%08X, DLC: %d\r\n", rxMessage.ExtId, rxMessage.DLC);
        }
}


/**
 * @brief 结构体大数据分包发送（固定8字节DLC，不足8字节自动补零补齐）
 * @param extId CAN扩展帧ID
 * @param pData 原始结构体数据指针
 * @param dataTotalLen 结构体总字节长度
 * @retval 0全部发送成功; >0 代表失败的包号，0xFFFF参数错误
 */
uint16_t CANx_SendExtFrame_StructSplit(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen)
{
    uint16_t pktIndex = 1;     // 包序号从0001开始
    uint16_t offset = 0;       // 原始数据偏移
    uint8_t  txBuf[8];         // CAN发送缓存，固定8字节
    uint8_t  sendLen;
    uint8_t  ret;

    if(pData == NULL || dataTotalLen == 0)
    {
        return 0xFFFF;  // 参数错误
    }

    while(offset < dataTotalLen)
    {
        // 1. 总线离线检测
        if ((CANx->ESR & CAN_ESR_BOFF) != RESET)
        {
            return pktIndex; 
        }

        // 2. 【关键】每次循环开始先清空整帧缓存（自动实现不足处的 0x00 补齐）
        memset(txBuf, 0, sizeof(txBuf));

        // 3. 填充前2字节的包序号（大端模式）
        txBuf[0] = (pktIndex >> 8) & 0xFF;
        txBuf[1] = pktIndex & 0xFF;

        // 4. 计算当前包需要拷贝多少原始结构体数据：最多6字节
        sendLen = dataTotalLen - offset;
        if(sendLen > 6)
        {
            sendLen = 6;
        }

        // 5. 将结构体数据拷贝到 txBuf[2] 开始的位置
        // 如果是最后一包，且 sendLen < 6，那么 txBuf[2 + sendLen] 到 txBuf[7] 的位置
        // 会保持步骤2中 memset 带来的 0x00，完美实现自动补齐！
        memcpy(&txBuf[2], pData + offset, sendLen);

        // 6. 强制固定 DLC 为 8（确保每一帧发到总线上的数据包长度都绝对是 8 字节）
        uint8_t canDlc = 8;

        // 7. 带超时保护的硬件邮箱发送
        uint32_t timeout = 0x5FFFF;
        do {
            ret = CANx_SendExtFrame(extId, txBuf, canDlc);
            if(ret == 0)
            {
                break; // 发送成功
            }
            
            if ((CANx->ESR & CAN_ESR_BOFF) != RESET)
            {
                return pktIndex;
            }

            timeout--;
            if(timeout == 0)
            {
                return pktIndex;  // 超时返回失败包号
            }
        } while(1);

        offset += sendLen;
        pktIndex++;

        if(pktIndex > 0xFFFF)
        {
            break;
        }
    }

    return 0; // 全部发送成功
}

uint16_t CANx_SendExtFrame_StructSplit01(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen)
{
    uint16_t pktIndex = 1;     // 包序号从0001开始
    uint16_t offset = 0;       // 原始数据偏移
    uint8_t  txBuf[8];         // CAN发送缓存，一帧最多8字节
    uint8_t  sendLen;
    uint8_t  ret;

    if(pData == NULL || dataTotalLen == 0)
    {
        return 0xFFFF;  // 参数错误
    }

    while(offset < dataTotalLen)
    {
        // ========= 1. 硬件状态保险：检测总线是否离线(Bus-Off) =========
        // 如果CAN硬件检测到总线严重错误进入离线状态，直接终止发送，防止白白超时卡顿
        if ((CANx->ESR & CAN_ESR_BOFF) != RESET)
        {
            return pktIndex; 
        }

        // ========= 2. 填充包序号（大端） =========
        txBuf[0] = (pktIndex >> 8) & 0xFF;
        txBuf[1] = pktIndex & 0xFF;

        // 当前包需要拷贝多少原始数据：最多6字节
        sendLen = dataTotalLen - offset;
        if(sendLen > 6)
        {
            sendLen = 6;
        }

        // 拷贝结构体数据到txBuf[2]开始
        memcpy(&txBuf[2], pData + offset, sendLen);

        // CAN整帧有效长度 = 包头2 + 数据sendLen
        uint8_t canDlc = 2 + sendLen;

        // ========= 3. 带有超时保护的邮箱等待重试机制 =========
        uint32_t timeout = 0x5FFFF; // 适当缩短超时阈值，避免不必要的长时间阻塞
        do {
            ret = CANx_SendExtFrame(extId, txBuf, canDlc);
            if(ret == 0)
            {
                break; // 发送成功，跳出重试循环，发下一包
            }
            
            // 每次循环顺便检测一下总线有没有挂掉
            if ((CANx->ESR & CAN_ESR_BOFF) != RESET)
            {
                return pktIndex;
            }

            timeout--;
            if(timeout == 0)
            {
                return pktIndex;  // 超时未等到空闲邮箱，返回当前失败的包号
            }
        } while(1);

        offset += sendLen;
        pktIndex++;

        // 防溢出：最多到0xFFFF
        if(pktIndex > 0xFFFF)
        {
            break;
        }
    }

    return 0; // 全部发送成功
}
/**
 * @brief 结构体大数据分包发送（加入邮箱等待，防止瞬时溢出）
 */
uint16_t CANx_SendExtFrame_StructSplit2(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen)
{
    uint16_t pktIndex = 1;     // 包序号从0001开始
    uint16_t offset = 0;       // 原始数据偏移
    uint8_t  txBuf[8];         // CAN发送缓存，一帧最多8字节
    uint8_t  sendLen;
    uint8_t  ret;

    if(pData == NULL || dataTotalLen == 0)
    {
        return 0xFFFF;  // 参数错误
    }

    while(offset < dataTotalLen)
    {
        // ========= 填充包序号（大端） =========
        txBuf[0] = (pktIndex >> 8) & 0xFF;
        txBuf[1] = pktIndex & 0xFF;

        // 当前包需要拷贝多少原始数据：最多6字节
        sendLen = dataTotalLen - offset;
        if(sendLen > 6)
        {
            sendLen = 6;
        }

        // 拷贝结构体数据到txBuf[2]开始
        memcpy(&txBuf[2], pData + offset, sendLen);

        // CAN整帧有效长度 = 包头2 + 数据sendLen
        uint8_t canDlc = 2 + sendLen;

        // 调用底层发送扩展帧（增加等待邮箱空出的重试机制，防止瞬间邮箱满）
        uint32_t timeout = 0xFFFFFF; 
        do {
            ret = CANx_SendExtFrame(extId, txBuf, canDlc);
            if(ret == 0)
            {
                break; // 发送成功，跳出重试循环，发下一包
            }
            timeout--;
            if(timeout == 0)
            {
                return pktIndex;  // 超时未等到空闲邮箱，返回当前失败的包号
            }
        } while(1);

        offset += sendLen;
        pktIndex++;

        // 防溢出：最多到0xFFFF
        if(pktIndex > 0xFFFF)
        {
            break;
        }
    }

    return 0;
}

/**
 * @brief 结构体大数据分包发送，每包前2字节为包序号(大端，从0x0001开始)，后面6字节有效数据
 * @param extId CAN扩展帧ID
 * @param pData 原始结构体数据指针
 * @param dataTotalLen 结构体总字节长度
 * @retval 0全部发送成功; >0 代表失败的包号，0xFFFF参数错误
 */
//uint16_t CANx_SendExtFrame_StructSplit2(uint32_t extId, uint8_t *pData, uint16_t dataTotalLen)
//{
//    uint16_t pktIndex = 1;
//    uint16_t offset = 0;
//    uint8_t  txBuf[8];
//    uint8_t  sendLen;
//    uint8_t  ret;

//    if(pData == NULL || dataTotalLen == 0)
//    {
//        return 0xFFFF;
//    }

//    while(offset < dataTotalLen)
//    {
//        txBuf[0] = (pktIndex >> 8) & 0xFF;
//        txBuf[1] = pktIndex & 0xFF;

//        sendLen = dataTotalLen - offset;
//        if(sendLen > 6)
//        {
//            sendLen = 6;
//        }
//        memcpy(&txBuf[2], pData + offset, sendLen);
//        uint8_t canDlc = 2 + sendLen;

//        ret = CANx_SendExtFrame(extId, txBuf, canDlc);
//        if(ret != 0)
//        {
//            return pktIndex;
//        }
//        offset += sendLen;
//        pktIndex++;
//        if(pktIndex > 0xFFFF)
//        {
//            break;
//        }
//    }
//    return 0;
//}
/**************************END OF FILE************************************/