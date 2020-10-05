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

Status CreatList1(GList& T) {//β�巨
	T = (GList)malloc(sizeof(ListNode));
	T->length = 0;
	T->next = NULL;
	GList p,q;
	q = T;
	cout << "���������ݣ���#��������";
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
		//ͷ�ڵ㲻��ֵ��
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

Status CreatList2(GList &S) {//ͷ�巨
	char c;
	cout << "���������ݣ���#��������";
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
	S->length--;//ɾ��Ԫ�ؼǵñ��ȼ�һ
	return OK;
}

Status PrintList(GList T) {
	GList p;
	p = T->next;//ͷ�ڵ�û��ֵ
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
	if (i > T->length) {//��i>length�����ǵ������һ��Ԫ��
		PrintList(S);
		cout << endl;
	}
	else {
		GetElem(T, i, a);
		//���Ԫ�ص�Ҫ�벻Ҫ
		//Ҫ��
		CreatList(S, a);		
		GetPower(T, S, i+1 );
		char temp;
		//��Ҫ
		//��Ϊ����S�Ѿ�Ҫ�ˣ��������ڲ�Ҫ������S��ɾ����Ԫ��
		DeleteList(S, temp);
		GetPower(T, S, i+1 );
	} 
	return OK;
}

int main() {
	GList T,S;
	S = NULL;
	T = NULL;
	cout << "***********ͷ�巨*********"<<endl;
	CreatList2(T);
	cout << "�����Ա�Ϊ��";
	PrintList(T);
	cout << endl << "***********���ݼ�************"<<endl;
	GetPower(T, S, 1);
	return OK;
}