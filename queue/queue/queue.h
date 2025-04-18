#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
//1.ΪʲôҪ����2���ṹ���������һ���ṹ����
//2��
typedef char QDatatype;//ת����

typedef struct QueueNode
{
	struct QueueNode* next;
	QDatatype data;
}QNode;//����һ����ʽ�ṹ

typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;//����һ��ͷָ���βָ��

// 10:40
void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pq, QDatatype x);
void QueuePop(Queue* pq);
int QueueSize(Queue* pq);
bool QueueEmpty(Queue* pq);
QDatatype QueueFront(Queue* pq);
QDatatype QueueBack(Queue* pq);