  #include <stdio.h>
 /*Ϊ���з���ռ�*/
 /*�Ƿ��*/
/*�ж��Ƿ���*/
/*���*/
/*����*/
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

/*���ٶ���*/