#ifndef __GUI_QUEUE_H
#define __GUI_QUEUE_H

#include "GUI_Config.h"
#include "GUI_Typedef.h"

typedef u_32 GUI_PARAM;

/* 消息结构体定义 */
typedef struct {
    int MsgId;       /* 消息编号 */
    GUI_HWIN hWin;    /* 目标窗口句柄 */
    GUI_HWIN hWinSrc; /* 源窗口句柄  */
    GUI_PARAM Param;  /* 参数 */
} GUI_MESSAGE;

/* 队列结构定义 */
typedef struct {
    GUI_MESSAGE *pArray; /* 队列指针 */
    int Capacity;       /* 队列数组容量 */
    int size;           /* 队列目前数据单元数量 */
    int front;          /* 队头 */
    int rear;           /* 队尾 */
} GUI_QUEUE;

GUI_QUEUE * GUI_QueueInit(int Capacity);
void GUI_QueueDelete(GUI_QUEUE *pQue);
GUI_RESULT GUI_GetMessageQueue(GUI_QUEUE *pQue, GUI_MESSAGE *pMsg);
GUI_RESULT GUI_PostMessageQueue(GUI_QUEUE *pQue, GUI_MESSAGE *pMsg);
GUI_RESULT GUI_MessageQueueInit(void);
void GUI_MessageQueueDelete(void);
GUI_RESULT GUI_GetMessage(GUI_MESSAGE *pMsg);
GUI_RESULT GUI_PostMessage(GUI_MESSAGE *pMsg);

#endif /* __GUI_QUEUE_H */
