  #include <stdio.h>  #include <stdlib.h>  #include"queue.h"
 /*为队列分配空间*/ void initqueue(Queue *q ,int n)/*n为可以存放数据可数，不包括空节点*/ {    q->dat = (DataType *) malloc(sizeof(DataType)*(n+1));    q->rear = 0;    q->front = 0;    q->maxsize = n+1; }
 /*是否空*/bool isEmpty(Queue *q){	if(q->rear == q->front)		return TRUE;	else		return FALSE;}
/*判断是否满*/bool isFull(Queue *q){    if((q->rear +1)%q->maxsize ==q->front)        return TRUE;    else        return FALSE;}
/*入队*/bool addqueue(Queue *q,DataType d){	if(!isFull(q))	{		*(q->dat + (q->rear + 1)%q->maxsize) = d;		q->rear = (q->rear + 1)%q->maxsize;		return TRUE;	}	else		return FALSE;}
/*出队*/bool outqueue(Queue *q,DataType *d){    if(!isEmpty(q))    {		*d = *(q->dat + (q->front+1) % q->maxsize) ;		q->front =(q->front+1) % q->maxsize;		return TRUE;    }    else        return FALSE;}
/*瞟一眼队头*/
bool peek(Queue *q, DataType *d)
{
    if(!isEmpty(q))
    {
        *d = *(q->dat + (q->front + 1) % q->maxsize);
        return TRUE;
    }
    else
        return FALSE;
}

/*销毁队列*/void delq(Queue *q){    free(q->dat);}/*清空队列*/void clearnq(Queue *q){	q->rear = q->front;}/*打印出队列中元素*/void print(Queue *q){    int i ;    for(i = 0; i<(q->rear +q->maxsize - q->front) %q->maxsize; i++)    printf("(%d %d %d) ",*(q->dat+((q->front+i+1)%q->maxsize)),q->front,q->rear);}