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
Status Push(SqStack S, SElemType& e);/*元素入栈*/
