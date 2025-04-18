#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
//1.为什么要定义2个结构体而不放在一个结构体内
//2。
typedef char QDatatype;//转类型

typedef struct QueueNode
{
	struct QueueNode* next;
	QDatatype data;
}QNode;//创建一个链式结构

typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;//创建一个头指针和尾指针

// 10:40
void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pq, QDatatype x);
void QueuePop(Queue* pq);
int QueueSize(Queue* pq);
bool QueueEmpty(Queue* pq);
QDatatype QueueFront(Queue* pq);
QDatatype QueueBack(Queue* pq);