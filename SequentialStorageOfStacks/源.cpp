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
Status Push(SqStack S, SElemType& e);/*Ԫ����ջ*/
