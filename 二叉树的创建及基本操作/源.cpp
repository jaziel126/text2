#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define OK 1
#define ERROR -1

typedef int Status;
typedef char ElemType;
typedef enum  PointerTag{ Link,Thread };//Link==0:指针；Thread==1:线索；枚举默认第一个为整型0
typedef struct BiTNode{//线索二叉树的存储结构
	ElemType data;
	BiTNode* lchild, * rchild;
	PointerTag LTag, RTag;
}BiTNode,*BiTree;

BiTree pre;//全局变量，始终指向刚访问过的p

Status CreatBiTree(BiTree& L) {//二叉树的构造，用递归
	char ch;
	cin >> ch;
	//当前结点为空
	if (ch == '#') L = NULL;
	else {
	//当前结点不空
		L = (BiTree)malloc(sizeof(BiTNode));
		L->data = ch;
		CreatBiTree(L->lchild);//构造左子树
		CreatBiTree(L->rchild);//构造右子树
	}
	return OK;
}

Status PrintBiTree(BiTree L) {//数组当前结点值
	cout << L->data;
	return OK;
}

Status ErgodicBiTree(BiTree L, Status PrintBiTree(BiTree L)) {//先序遍历，并对数据元素调用函数
	if (L) {
		if (PrintBiTree(L))
			if (ErgodicBiTree(L->lchild,PrintBiTree))//函数为形参时只要输入函数原型
				if (ErgodicBiTree(L->rchild, PrintBiTree))
		return ERROR;
	}
	return OK;
}

Status ErgodicBiTree2(BiTree L,  Status PrintBiTree(BiTree L)) {//先序遍历，并对数据元素调用函数
	if (L) {
		PrintBiTree(L);
		ErgodicBiTree(L->lchild, PrintBiTree);//函数为形参时只要输入函数原型
		ErgodicBiTree(L->rchild, PrintBiTree);		
	}
	return OK;
}
Status InTreading(BiTree L) {//二叉树线索化
	if (L) {
		//左子树线索化
		InTreading(L->lchild);
		//线索化当前结点
		if (!L->lchild) { L->LTag = Thread;L->lchild = pre; }//前驱线索
		else L->LTag = Link;//这里一定要记住，否则会导致当结点不是终端结点时其左域为空
		if (!pre->rchild) { pre->RTag = Thread;pre->rchild = L; }//后驱线索
		else pre->RTag = Link;
		pre = L;
		//右子树线索化
		InTreading(L->rchild);
	}
	return OK;
}

Status InOderTreading(BiTree& Thrt, BiTree L) {
	//建立头结点
	if (!(Thrt = (BiTree)malloc(sizeof(BiTNode)))) return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;Thrt->rchild = Thrt;//右域回指
	//BiTree pre;//不能定义在这里，要定义在全局变量
	if (!L) Thrt->lchild = Thrt;//如果L为空，左域回指
	else {
		Thrt->lchild = L;pre = Thrt;
		InTreading(L);
		//处理最后一个结点
		pre->RTag = Thread;pre->rchild = Thrt;
		Thrt->rchild = pre;
	}
	return OK;
}


Status InOrderTreave(BiTree L, Status PrintBiTree(BiTree L)) {//线索化后的二叉树遍历
	BiTree p;
	p = L->lchild;//让p指向L的根结点
	while (p != L) {
		
		//左子树走到尽头
		while (p->LTag == Link) p = p->lchild;
		if (!PrintBiTree(p)) return ERROR;
		
		//当前子树右域为线索
		while (p->RTag == Thread && p->rchild != L) {
			p = p->rchild;PrintBiTree(p);
			
		}
		//当前子树右域不为线索
		p = p->rchild;
		
	}
	return OK;
}

int main() {
	BiTree L,Thrt;
	cout << "按前序次序依次输入二叉树各结点值(当该结点的左右子树为空时输入#):" << endl;
	CreatBiTree(L);
	ErgodicBiTree(L, PrintBiTree);
	cout << endl;
	ErgodicBiTree2(L, PrintBiTree);
	cout << endl;
	InOderTreading(Thrt, L);
	InOrderTreave(Thrt, PrintBiTree);
	return OK;
}