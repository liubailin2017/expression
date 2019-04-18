  #include <stdio.h>  #include <stdlib.h>  #include"queue.h"
 /*Ϊ���з���ռ�*/ void initqueue(Queue *q ,int n)/*nΪ���Դ�����ݿ������������սڵ�*/ {    q->dat = (DataType *) malloc(sizeof(DataType)*(n+1));    q->rear = 0;    q->front = 0;    q->maxsize = n+1; }
 /*�Ƿ��*/bool isEmpty(Queue *q){	if(q->rear == q->front)		return TRUE;	else		return FALSE;}
/*�ж��Ƿ���*/bool isFull(Queue *q){    if((q->rear +1)%q->maxsize ==q->front)        return TRUE;    else        return FALSE;}
/*���*/bool addqueue(Queue *q,DataType d){	if(!isFull(q))	{		*(q->dat + (q->rear + 1)%q->maxsize) = d;		q->rear = (q->rear + 1)%q->maxsize;		return TRUE;	}	else		return FALSE;}
/*����*/bool outqueue(Queue *q,DataType *d){    if(!isEmpty(q))    {		*d = *(q->dat + (q->front+1) % q->maxsize) ;		q->front =(q->front+1) % q->maxsize;		return TRUE;    }    else        return FALSE;}
/*�һ�۶�ͷ*/
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

/*���ٶ���*/void delq(Queue *q){    free(q->dat);}/*��ն���*/void clearnq(Queue *q){	q->rear = q->front;}/*��ӡ��������Ԫ��*/void print(Queue *q){    int i ;    for(i = 0; i<(q->rear +q->maxsize - q->front) %q->maxsize; i++)    printf("(%d %d %d) ",*(q->dat+((q->front+i+1)%q->maxsize)),q->front,q->rear);}