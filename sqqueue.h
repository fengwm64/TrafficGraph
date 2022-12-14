//  sqqueue.hpp
//////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////以下为队列实现//////////////////////////////////

#include "StatusCode.h"
#include <iostream>
using namespace std;

#define MaxSize 10		// 队列最大长度
#define ElemType int	// 队列元素的数据类型

// 循环队列的定义
typedef struct
{
	ElemType* base;	// 动态数组指针
	int front;				// 头指针，指向队头
	int rear;				// 尾指针，指向队尾
}SqQueue;

Status InitQueue(SqQueue& Q);							// 初始化队列
Status DestroyQueue(SqQueue& Q);					// 销毁队列
Status QueueEmpty(SqQueue Q);						// 队列判空
Status EnQueue(SqQueue& Q, ElemType e);		// 入队
Status DeQueue(SqQueue& Q, ElemType& e);	// 出队