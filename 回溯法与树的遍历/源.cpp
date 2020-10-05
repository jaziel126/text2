#include<iostream>
using namespace std;
#define OK 1
#define ERROR -1
typedef int Status;
typedef struct ListNode{
	char ch;
	int length;
	struct ListNode* next;
}ListNode,*GList;

Status CreatList1(GList& T) {//尾插法
	T = (GList)malloc(sizeof(ListNode));
	T->length = 0;
	T->next = NULL;
	GList p,q;
	q = T;
	cout << "请输入数据（按#结束）：";
	char c;
	do {
		p = (GList)malloc(sizeof(ListNode));
		cin >> c;
		if (c == '#') break;
		p->ch = c;
		q->next = p;
		q = p;
		T->length++;
	} while (1);
	q->next = NULL;
	return OK;
}

Status CreatList(GList& S, char a) {
	if (S == NULL) {
		S = (GList)malloc(sizeof(ListNode));
		S->ch = NULL;
		S->next = NULL;
		S->length = 0;
		//头节点不赋值；
		GList p;
		p = (GList)malloc(sizeof(ListNode));
		p->ch = a;
		p->next = S->next;
		S->next = p;
		S->length++;
	}
	else {
		GList p;
		p = (GList)malloc(sizeof(ListNode));
		p->ch = a;
		p->next = S->next;
		S->next = p;
		S->length++;
	}
	return OK;
}

Status CreatList2(GList &S) {//头插法
	char c;
	cout << "请输入数据（按#结束）：";
	do {
		cin >> c;
		if (c == '#') break;
		CreatList(S, c);
	} while (1);
	return OK;
}

Status DeleteList(GList& S, char& a) {
	GList p;
	p = S->next;
	a = p->ch;
	S->next = p->next;
	S->length--;//删除元素记得表长度减一
	return OK;
}

Status PrintList(GList T) {
	GList p;
	p = T->next;//头节点没有值
	while (p) {
		cout << p->ch;
		p = p->next;
	}
	return OK;
}

Status GetElem(GList T, int n,char &a) {
	GList p;
	p = T->next;
	if (n > T->length) return ERROR;
	for (int i = 1;i < n;i++) {
		p = p->next;
	}
	a = p->ch;
	return OK;
}

Status GetPower(GList T, GList &S, int i) {
	char a;
	if (i > T->length) {//当i>length，就是到了最后一个元素
		PrintList(S);
		cout << endl;
	}
	else {
		GetElem(T, i, a);
		//这个元素的要与不要
		//要了
		CreatList(S, a);		
		GetPower(T, S, i+1 );
		char temp;
		//不要
		//因为上面S已经要了，所以现在不要就是在S中删除该元素
		DeleteList(S, temp);
		GetPower(T, S, i+1 );
	} 
	return OK;
}

int main() {
	GList T,S;
	S = NULL;
	T = NULL;
	cout << "***********头插法*********"<<endl;
	CreatList2(T);
	cout << "输线性表为：";
	PrintList(T);
	cout << endl << "***********求幂集************"<<endl;
	GetPower(T, S, 1);
	return OK;
}