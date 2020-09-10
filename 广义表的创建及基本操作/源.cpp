#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define OK 1
#define ERROR -1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;
typedef struct {//���Ĵ洢�ṹ
	char* ch;
	int length;
}HString;

typedef enum{ATOM,LIST}ElemTag;//ATOM==0:ԭ�ӣ�LIST==1���ӱ�
typedef struct GLNode {
	ElemTag tag;//��������,����ԭ�ӽ��ͱ���
	union {
		char atom;
		struct { struct GLNode* hp, * tp; }ptr;
	};
}*GList;


Status PushHString(HString& T,char *str) {//����������ֵ��T
	int a = strlen(str);
	T.ch = (char*)malloc(a * sizeof(char));
	for (int i = 0;i < a;i++) {
		T.ch[i] = *(str + i);
	}
	T.length = a;
	return OK;
}

Status CreatHString(HString& T) {//���볣����
	char str[MAXSIZE];
	cout << "�����ִ���";
	cin >> str;
	PushHString(T, str);
	return OK;
}

Status CompareHString(HString T, HString S) {//�Ƚϴ���С
	for (int i = 0;i < T.length && S.length;i++) {
		if (T.ch[i] != S.ch[i]) return T.ch[i] - S.ch[i];
	}
	return T.length - S.length;
}

Status SubHString(HString& S, HString T, int pos, int len) {//����T�д�posλ�𳤶�Ϊlen���Ӵ�
	if (pos<0 || pos>T.length || len<0 || len>T.length) return ERROR;
	S.ch = (char*)malloc(len * sizeof(char));
	for (int i = 0;i < len;i++) {
		S.ch[i] = T.ch[pos + i-1];
	}
	S.length = len;
	return OK;
}

Status PrintHString(HString T) {//���
	for (int i = 0;i < T.length;i++) {
		cout << T.ch[i];
	}
	cout << endl;
	return OK;
}

Status CopyHString(HString& S, HString T) {//���ƴ�T
	S.ch = (char*)malloc(T.length * sizeof(char));
	for (int i = 0;i < T.length;i++) {
		S.ch[i] = T.ch[i];
	}
	S.length = T.length;
	return OK;
}

Status ClearHString(HString &T) {//��մ�
	if (T.ch) {
		free(T.ch);
		T.ch = NULL;
	}
	T.length = 0;
	return OK;
}

Status EmptHString(HString T) {//�жϱ��Ƿ�Ϊ��
	if (T.length == 0) return 1;
	else return 0;
}

Status sever(HString& S, HString& T) {//����T�ָ�Ϊ������ǰ�͡�������������
	int n = T.length;int i = 0;int k = 0;//kΪ��δ��Ե���������
										 //֮����Ҫ��¼������������Ϊ���Ӵ�Ϊԭ�ӱ�û�С���������
	HString ch;
	do {
		i++;
		SubHString(ch, T, i, 1);
		if (ch.ch[0] == '(') ++k;
		else if (ch.ch[0] == ')') --k;
	} while (i < n && (ch.ch[0] != ',' || k != 0));//��kΪ�㣬��˵���Ѿ�������һ�����ŵ�����
												   //Ҳ��˵����ǰ��Ϊԭ�ӱ�û�С�����
	if (i < n) {
		SubHString(S, T, 1, i - 1);
		SubHString(T, T, i + 1, n - i);
	}
	else {
		CopyHString(S, T);
		ClearHString(T);
	}
	return OK;
}

Status CreatGList(GList& L, HString T) {//���������
	HString emp, sub, str;
	GList p, q;
	PushHString(emp, "()");
	//��TΪ�ձ�,�ÿչ����
	if (!CompareHString(T, emp)) L = NULL;//�����ձ�
	else {
		if (!(L = (GList)malloc(sizeof(GLNode)))) return ERROR;
	//��TΪ���ַ���������ԭ�ӽ���ӱ�
		if (T.length == 1) {
			L->tag = ATOM;
			L->atom = T.ch[0];
		}
	//������
		else {
			L->tag = LIST;p = L;
			SubHString(sub, T, 2, T.length - 2);//��ȥ�������
			do {
				sever(str, sub);//��һ�α�дΪsever(str,T)...һֱ�����������ĸ���ͷ������
				CreatGList(p->ptr.hp, str);q = p;//hpΪ�����ӱ��ͷָ��
				if (!EmptHString(sub)) {
					p = (GList)malloc(sizeof(GLNode));//tpָ������֮�����Ľ��
					p->tag = LIST;q->ptr.tp = p;
				}
			} while (!EmptHString(sub));
			q->ptr.tp = NULL;
		}
	}
	return OK;
}

void PrintGList2(GList L) {
	GLNode* p;
	if (!L)
	{
		cout << "()";
	}
	else
	{

		if (L->tag == ATOM)
		{
			cout << L->atom;
		}
		else
		{
			p = NULL;
			cout << '(';
			p = L;
			while (p)
			{
				PrintGList2(p->ptr.hp);
				p = p->ptr.tp;
				if (p)
				{
					cout << ',';
				}
			}
			cout << ')';
		}
	}
}

Status DepthGList(GList L) {//���б����
	if (!L) return 1;//�ձ����Ϊ1
    if (L->tag == 0) return 0;//ԭ�ӱ����Ϊ0
	int dep, max ;GList pp;
	for (max = 0, pp=L;pp;pp = pp->ptr.tp) {//�����б�������Ϊ�б����Ϊ�����ӱ�������ֵ��1
		dep = DepthGList(pp->ptr.hp);
		if (dep > max) max = dep;
	}
	return max + 1;
}

int main() {
	/*HString S, T, R,B;
	CreatHString(T);
	PrintHString(T);
	CreatHString(S);
	PrintHString(S);
	cout << endl;
	int a = CompareHString(T, S);
	cout << a;
	int pos, len;
	cout << "��ʼ��ȡλ�ã�";
	cin >> pos;
	cout << "��ȡ���ȣ�";
	cin >> len;
	SubHString(R, T,pos,len);
	PrintHString(R);
	CopyHString(B, T);
	PrintHString(B);
	ClearHString(B);
	PrintHString(B);*///���Դ��Ĳ���ģ���Ƿ���ȷ
	HString S, T;
	CreatHString(T);
	GList L;
	CreatGList(L, T);
	PrintGList2(L);
	int a = DepthGList(L);
	cout << a;
	return OK;
}