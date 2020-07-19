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
Status ClearStack(SqStack& S);/*���ջ*/
Status LengthStack(SqStack& S);/*����ջ�ĳ���*/

/*�㷨ʵ��*/
Status InitStack(SqStack& S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));/*����ռ�*/
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	return OK;
}
Status Push(SqStack& S) {
	int n;
	cout<< "��ջԪ�ظ���";
	cin>> n;
	for (int i = 0;i < n;i++) {
		cin>> *S.top;
		S.top++;
	}
	return OK;
}
Status Pop(SqStack& S){
	int n;
	cout << "��ջԪ�ظ�����";
	cin >> n;
	for (int i = 0;i < n;i++) {
		S.top--;/*������topָ��*/
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
