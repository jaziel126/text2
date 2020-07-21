#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

#define OK 1
#define OVERLLOW -2

typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

Status InitStack(LinkList& head) {/*创建空的头节点*/
	head = (LinkList)malloc(sizeof(LNode));
	head->next = NULL;
	return OK;
}

Status Push(LinkList& head, ElemType e) {/*元素入栈*/
	LNode* p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;
	p->next = head->next;
	head->next = p;
	return OK;
}
Status Pop(LinkList& head) {
	LNode* p;
	p = head;
	p = p->next;/*这句非常重要********************************************/
	while (p) {
		cout << p->data;
		p = p->next;
	}
	return OK;
}

int main() {
	LNode* head;
	InitStack(head);
	ElemType e;
	int n;
	cout << "入栈元素个数：";
	cin >> n;
	for (int i = 0;i < n;i++) {
		cout << "请输入数据：";
		cin >> e;
		Push(head, e);
	}
	Pop(head);
	return OK;
}