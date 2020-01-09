/* queue.c -- реализация типа Queue */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* локальные функции */
static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeQueue(Queue * pq)
{
    pq->front = pq->rear = NULL;
    pq->items = 0;
    pq->line_wait=0;       // накопительное значение времени в очереди	
	pq->customers=0;       // количество клиентов присоединившихся к очереди
    pq->served=0;   // количество клиентов, обслуженных за время моделирования
    pq->sum_line=0;        // накопительное значение длины очереди
	pq->turnaways=0; // количество отказов из-за переполненной очереди
}

bool QueueIsFull(const Queue * pq)
{
    return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
    return pq->items == 0;
}

int QueueItemCount(const Queue * pq)
{
    return pq->items;
}

bool EnQueue(Item item, Queue * pq)
{
    Node * pnew;

    if (QueueIsFull(pq))
        return false;
    pnew = (Node *) malloc( sizeof(Node));
    if (pnew == NULL)
    {
        fprintf(stderr, "Не удается выделить память!\n");
        exit(1);
    }
    CopyToNode(item, pnew);
    pnew->next = NULL;
    if (QueueIsEmpty(pq))
        pq->front = pnew;           /* элемент помещается в начало очереди            */
    else
        pq->rear->next = pnew;      /* связывание с концом очереди                    */
    pq->rear = pnew;                /* запись местоположения конца очереди            */
    pq->items++;                    /* увеличение на 1 количества элементов в очереди */

    return true;
}

bool DeQueue(Item * pitem, Queue * pq)
{
    Node * pt;

    if (QueueIsEmpty(pq))
        return false;
    CopyToItem(pq->front, pitem); 
    pt = pq->front;
    pq->front = pq->front->next;
    free(pt);
    pq->items--;
    if (pq->items == 0)
        pq->rear = NULL;

    return true;
}

/* опустошение очереди */
void EmptyTheQueue(Queue * pq)
{
    Item dummy;
    while (!QueueIsEmpty(pq))
        DeQueue(&dummy, pq);
}

/* локальные функции */

static void CopyToNode(Item item, Node * pn)
{
    pn->item = item;
}

static void CopyToItem(Node * pn, Item * pi)
{
    *pi = pn->item; 
}

