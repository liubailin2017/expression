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
 
 void initqueue(Queue *q ,int n);/*nΪ���Դ�����ݿ������������սڵ�*/

  /*�Ƿ��*/
bool isEmpty(Queue *q);

/*�ж��Ƿ���*/
bool isFull(Queue *q);

/*���*/
bool addqueue(Queue *q,DataType d);


/*����*/
bool outqueue(Queue *q,DataType *d);

/*�һ�۶�ͷ*/
bool peek(Queue *q, DataType *d);

/*��ն���*/
void clearnq(Queue *q);

/*���ٶ���*/
void delq(Queue *q);
#endif