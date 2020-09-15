#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR -1

typedef int Status;
typedef char ElemType;
typedef enum  PointerTag{ Link,Thread };//Link==0:ָ�룻Thread==1:������ö��Ĭ�ϵ�һ��Ϊ����0
typedef struct BiTNode{//�����������Ĵ洢�ṹ
	ElemType data;
	BiTNode* lchild, * rchild;
	PointerTag LTag, RTag;
}BiTNode,*BiTree;

BiTree pre;//ȫ�ֱ�����ʼ��ָ��շ��ʹ���p

Status CreatBiTree(BiTree& L) {//�������Ĺ��죬�õݹ�
	char ch;
	cin >> ch;
	//��ǰ���Ϊ��
	if (ch == '#') L = NULL;
	else {
	//��ǰ��㲻��
		L = (BiTree)malloc(sizeof(BiTNode));
		L->data = ch;
		CreatBiTree(L->lchild);//����������
		CreatBiTree(L->rchild);//����������
	}
	return OK;
}

Status PrintBiTree(BiTree L) {//���鵱ǰ���ֵ
	cout << L->data;
	return OK;
}

Status ErgodicBiTree(BiTree L, Status PrintBiTree(BiTree L)) {//�����������������Ԫ�ص��ú���
	if (L) {
		if (PrintBiTree(L))
			if (ErgodicBiTree(L->lchild,PrintBiTree))//����Ϊ�β�ʱֻҪ���뺯��ԭ��
				if (ErgodicBiTree(L->rchild, PrintBiTree))
		return ERROR;
	}
	return OK;
}

Status ErgodicBiTree2(BiTree L,  Status PrintBiTree(BiTree L)) {//�����������������Ԫ�ص��ú���
	if (L) {
		PrintBiTree(L);
		ErgodicBiTree(L->lchild, PrintBiTree);//����Ϊ�β�ʱֻҪ���뺯��ԭ��
		ErgodicBiTree(L->rchild, PrintBiTree);		
	}
	return OK;
}
Status InTreading(BiTree L) {//������������
	if (L) {
		//������������
		InTreading(L->lchild);
		//��������ǰ���
		if (!L->lchild) { L->LTag = Thread;L->lchild = pre; }//ǰ������
		else L->LTag = Link;//����һ��Ҫ��ס������ᵼ�µ���㲻���ն˽��ʱ������Ϊ��
		if (!pre->rchild) { pre->RTag = Thread;pre->rchild = L; }//��������
		else pre->RTag = Link;
		pre = L;
		//������������
		InTreading(L->rchild);
	}
	return OK;
}

Status InOderTreading(BiTree& Thrt, BiTree L) {
	//����ͷ���
	if (!(Thrt = (BiTree)malloc(sizeof(BiTNode)))) return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;Thrt->rchild = Thrt;//�����ָ
	//BiTree pre;//���ܶ��������Ҫ������ȫ�ֱ���
	if (!L) Thrt->lchild = Thrt;//���LΪ�գ������ָ
	else {
		Thrt->lchild = L;pre = Thrt;
		InTreading(L);
		//�������һ�����
		pre->RTag = Thread;pre->rchild = Thrt;
		Thrt->rchild = pre;
	}
	return OK;
}


Status InOrderTreave(BiTree L, Status PrintBiTree(BiTree L)) {//��������Ķ���������
	BiTree p;
	p = L->lchild;//��pָ��L�ĸ����
	while (p != L) {
		
		//�������ߵ���ͷ
		while (p->LTag == Link) p = p->lchild;
		if (!PrintBiTree(p)) return ERROR;
		
		//��ǰ��������Ϊ����
		while (p->RTag == Thread && p->rchild != L) {
			p = p->rchild;PrintBiTree(p);
			
		}
		//��ǰ��������Ϊ����
		p = p->rchild;
		
	}
	return OK;
}

int main() {
	BiTree L,Thrt;
	cout << "��ǰ�����������������������ֵ(���ý�����������Ϊ��ʱ����#):" << endl;
	CreatBiTree(L);
	ErgodicBiTree(L, PrintBiTree);
	cout << endl;
	ErgodicBiTree2(L, PrintBiTree);
	cout << endl;
	InOderTreading(Thrt, L);
	InOrderTreave(Thrt, PrintBiTree);
	return OK;
}