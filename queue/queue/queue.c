#define _CRT_SECURE_NO_WARNINGS
#include"queue.h"
void QueueInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;

}
void QueueDestroy(Queue* pq)
{
	assert(pq);
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

void QueuePush(Queue* pq, QDatatype x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));//ΪʲôҪmalloc
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}


}
void QueuePop(Queue* pq)
{

}
int QueueSize(Queue* pq)
{

}
bool QueueEmpty(Queue* pq)
{

}
QDatatype QueueFront(Queue* pq)
{

}
QDatatype QueueBack(Queue* pq)
{

}