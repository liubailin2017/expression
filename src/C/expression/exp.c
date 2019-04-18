#include <stdio.h>
#include<stdlib.h>
#include"queue.h"
double factor(Queue *exp);
double term(Queue *exp);
double expression(Queue *exp);

char Peek(Queue *stra) //简化peek函数
{
		char a ;
		peek(stra,&a);
		return a;
}

char Outqueue(Queue *stra) //简化Outqueue函数
{
		char a ;
		outqueue(stra,&a);
		return a;
}

/* （表达式（项（因子（表达式||数字||单目运算符）））） expression term factor*/

double factor(Queue *exp)
{
	double result = 0;
	if(Peek(exp) == '(') //因子
	{
		Outqueue(exp);
		result = expression(exp);
		if(Outqueue(exp) !=')') printf("Error: lack ')' \n");
	}
	else if(Peek(exp) == '+' || Peek(exp) =='-')//单目运算
	{
		switch(Peek(exp))
		{
			case '+':
					Outqueue(exp);
					if(Peek(exp) == '(')
					result = factor(exp);
					else
					result =  term(exp);
					break;
			case '-':
					Outqueue(exp);
					if(Peek(exp) == '(')
					result = -factor(exp);
					else
					result =  -term(exp);
					break;

		}
	}
	else if(Peek(exp) >= '0' && Peek(exp)  <= '9' ||Peek(exp) == '.') //数字
	{
		char nmb[20]={0};
		int i=0;
	
		/*数字 可能有 0~9 和. 组成，可以直接通过C库函数完成字符串转浮点数*/
		while(Peek(exp) >= '0' && Peek(exp)  <= '9' ||Peek(exp) == '.')
		{
			nmb[i++] = Outqueue(exp);
		}
		nmb[i] = '\0';
		result = atof(nmb);
	}

	return result;
}

double term(Queue *exp)
{
	double result = 0;
	result = factor(exp);
	while(Peek(exp) =='*' || Peek(exp) == '/')
	switch(Peek(exp))
	{
		case '*' :
			Outqueue(exp);
			result = result * factor(exp);
			break;
		case '/' :
			Outqueue(exp);
			result = result / factor(exp);
			break;
	}

return result;
}
	
double expression(Queue *exp)
{
	char t;
	double result = 0;
	result = term(exp);
	while(Peek(exp) == '+' || Peek(exp) =='-')
	switch(Peek(exp))
	{
		case '+' : 
			Outqueue(exp);
			result = result + term(exp);
			break;
		case '-' :
			Outqueue(exp);
			result = result - term(exp);
			break;
	}

return result;
}

void readme()
{
	printf("support + - * / () quit :quit \n");
	printf("author:liubailin.");
}

int main(int argc, char *argv[])
{
	Queue stra;
	
	initqueue(&stra,100);
	readme();
	char c;
while(1)
{
	do
	{
		if ((c = getchar()) == 'q' ) exit(1);
		if(isFull(&stra))
		{
			printf("error: full for memery");
			exit(1);
		}
		else
			if(c != ' ')addqueue(&stra,c);
	}
	while(c != '\n' && c != EOF);

	printf("=%lf \n",expression(&stra));
	Outqueue(&stra);
	if(!isEmpty(&stra))printf("Error: don't knew sign\n");
	clearnq(&stra);
}
	delq(&stra);
	return 0;
}