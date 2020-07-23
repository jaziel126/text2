#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

#define OK 1
#define ERROR 0;
#define MAXSIZE 100

typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType* base;
	int front;
	int rear;
}QueueNode;

Status InitQueue(QueueNode& S) {/*创建队列*/
	S.base = (ElemType*)malloc(sizeof(ElemType));
	if (!S.base) exit(OVERFLOW);
	S.rear = S.front = 0;
	return OK;
}

Status PushQueue(QueueNode& S, ElemType e) {
	if ((S.rear+1)%MAXSIZE==S.front) exit(OVERFLOW);/*队满*/
	S.base[S.rear] = e;
	S.rear++;
	return OK;
}

Status PopQueue(QueueNode& S) {/*元素出队*/
	int n;
	n = (S.rear - S.front + MAXSIZE) % MAXSIZE;
	for (int j = 0;j < n;j++) {
		cout << S.base[S.front];
		S.front++;
	}
	return OK;
}

int main() {
	QueueNode S;
	InitQueue(S);
	int n;
	cout << "进队元素个数：";
	cin >> n;
	ElemType e,a;
	for (int i = 0;i < n;i++) {
		cout << "请输入数据：";
		cin >> e;
		PushQueue(S, e);
	}
	PopQueue(S);
	return OK;
}
