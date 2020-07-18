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
typedef struct {/*˳��ջ�Ľṹ����*/
	SElemType* base;/*ָ��ջ��Ԫ��*/
	SElemType* top;/*ָ��ջ��Ԫ��*/
	int stacksize;/*��¼��ǰ�ѷ���ռ�*/
}SqStack;

/*����ԭ��˵��*/
Status InitStack(SqStack& S);/*������ջ*/
Status Push(SqStack &S);/*Ԫ����ջ*/
Status Pop(SqStack& S);/*Ԫ�س�ջ*/
Status DestroyStack(SqStack& S);/*����ջ*/

/*�㷨ʵ��*/
Status InitStack(SqStack& S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));/*����ռ�*/
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	return OK;
}
Status Push(SqStack& S) {
	if (S.top - S.base >= S.stacksize) {/*ջ�������·���ռ�*/
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	int n;
	cout << "��ջԪ�ظ�����";
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> *S.top;
		S.top++;
	}
	return OK;
}
