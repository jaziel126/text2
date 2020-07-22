#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

#define OK 1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct QNode {
	ElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}QueueNode;

Status InitQueue(QueueNode& head) {/*����ͷ�ڵ�*/
	head.front =head.rear = (QueuePtr)malloc(sizeof(ElemType));
	if (!head.front) exit(OVERFLOW);
	head.front->next = NULL;
}

Status PushQueue(QueueNode& head, ElemType e) {/*���г�ʼ��*/
	QNode *p;

	p = (QueuePtr)malloc(sizeof(ElemType));
	p->data = e;
	p->next = NULL;/*����һ��Ҫ��ֵNULL*/
	head.rear->next = p;
	head.rear = p;
	return OK;
}
Status PopQueue(QueueNode& head) {
	QNode* p;
	p = head.front;
	p = p->next;
	while (p) {
		cout << p->data;
		p = p->next;
	}
	return OK;
}

int main() {
	QueueNode head;
	InitQueue(head);
	ElemType e;
	int n;
	cout << "����Ԫ�ظ�����";
	cin >> n;
	for (int i = 0;i < n;i++) {
		cout << "���������ݣ�";
		cin >> e;
		PushQueue(head, e);
	}
	PopQueue(head);
	return OK;
}
