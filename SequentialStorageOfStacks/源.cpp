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
Status ClearStack(SqStack& S);/*清空栈*/
Status LengthStack(SqStack& S);/*返回栈的长度*/

/*算法实现*/
Status InitStack(SqStack& S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));/*分配空间*/
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	return OK;
}
Status Push(SqStack& S) {
	int n;
	cout<< "入栈元素个数";
	cin>> n;
	for (int i = 0;i < n;i++) {
		cin>> *S.top;
		S.top++;
	}
	return OK;
}
Status Pop(SqStack& S){
	int n;
	cout << "出栈元素个数：";
	cin >> n;
	for (int i = 0;i < n;i++) {
		S.top--;/*先下移top指针*/
		cout<< *S.top;
	}
	return OK;
}
Status DestroyStack(SqStack& S) {
	int len = S.stacksize;
	for (int i = 0;i < len;i++) {
		free(S.base);
		S.base++;
	}
	S.base = S.top = NULL;
	S.stacksize = 0;
	return OK;
}
Status ClearStack(SqStack& S) {
	S.base = S.top;
	return OK;
}
Status LengthStack(SqStack& S) {
	
	return (S.top-S.base);
}

int main() {
	SqStack S;
	InitStack(S);
	Push(S);
	int a = LengthStack(S);
	cout << a;
	Pop(S);
}
