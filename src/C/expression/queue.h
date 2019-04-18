#ifndef QUEUE_INCLUDE_
#define QUEUE_INCLUDE_
 typedef char DataType;
 #ifndef __cplusplus
 typedef enum{ FALSE , TRUE} bool; #endif
 typedef struct _queue
 {
     int maxsize;
     int rear ;
     int front ;
     DataType *dat;
 }Queue,*PQueue;
 
 void initqueue(Queue *q ,int n);/*n为可以存放数据可数，不包括空节点*/

  /*是否空*/
bool isEmpty(Queue *q);

/*判断是否满*/
bool isFull(Queue *q);

/*入队*/
bool addqueue(Queue *q,DataType d);


/*出队*/
bool outqueue(Queue *q,DataType *d);

/*瞟一眼队头*/
bool peek(Queue *q, DataType *d);

/*清空队列*/
void clearnq(Queue *q);

/*销毁队列*/
void delq(Queue *q);
#endif