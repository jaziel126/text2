#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

#define OK 1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCRETMENT 10

typedef int SElemType;
typedef int Status;

typedef struct {
	SElemType* top;
	SElemType* base;
	int stacksize;
}SqStack;

Status InitStack(SqStack& S){/*������ջ*/
	S.base = (SElemType*)malloc((STACK_INIT_SIZE) * sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack& S, SElemType e) {/*����*/
	
	*S.top = e;
	S.top++;
	return OK;
}

Status Pop(SqStack& S) {/*���*/
	int len = S.top - S.base;
	for (int i = 0;i < len;i++) {
		S.top--;
		cout << *S.top;
	}
	return OK;
}

Status Conversion() {
	SqStack(S);
	InitStack(S);
	int N, n;
	SElemType e;
	cout << "ת�����ݣ�";cin >> N;
	cout << "ת�����ƣ�";cin >> n;
	while (N) {
		e = N % n;
		N = N / n;
		Push(S, e);
	}
	Pop(S);
	return OK;
}



int main() {
	Conversion();
	return OK;
}

