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

Status InitStack(LinkList& head) {/*�����յ�ͷ�ڵ�*/
	head = (LinkList)malloc(sizeof(LNode));
	head->next = NULL;
	return OK;
}

Status Push(LinkList& head, ElemType e) {/*Ԫ����ջ*/
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
	p = p->next;/*���ǳ���Ҫ********************************************/
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
	cout << "��ջԪ�ظ�����";
	cin >> n;
	for (int i = 0;i < n;i++) {
		cout << "���������ݣ�";
		cin >> e;
		Push(head, e);
	}
	Pop(head);
	return OK;
}