#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;
typedef int Status;
typedef struct {/*顺序栈的结构定义*/
	SElemType* base;/*指向栈底元素*/
	SElemType* top;/*指向栈顶元素*/
	int stacksize;/*记录当前已分配空间*/
}SqStack;

/*函数原型说明*/
Status InitStack(SqStack& S);/*构建空栈*/
Status Push(SqStack &S);/*元素入栈*/
Status Pop(SqStack& S);/*元素出栈*/
Status DestroyStack(SqStack& S);/*销毁栈*/

/*算法实现*/
Status InitStack(SqStack& S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));/*分配空间*/
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	return OK;
}
Status Push(SqStack& S) {
	if (S.top - S.base >= S.stacksize) {/*栈满，重新分配空间*/
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	int n;
	cout << "入栈元素个数：";
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> *S.top;
		S.top++;
	}
	return OK;
}
