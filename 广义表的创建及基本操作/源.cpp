#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define OK 1
#define ERROR -1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;
typedef struct {//串的存储结构
	char* ch;
	int length;
}HString;

typedef enum{ATOM,LIST}ElemTag;//ATOM==0:原子；LIST==1：子表；
typedef struct GLNode {
	ElemTag tag;//公共部分,区分原子结点和表结点
	union {
		char atom;
		struct { struct GLNode* hp, * tp; }ptr;
	};
}*GList;


Status PushHString(HString& T,char *str) {//将常量串赋值给T
	int a = strlen(str);
	T.ch = (char*)malloc(a * sizeof(char));
	for (int i = 0;i < a;i++) {
		T.ch[i] = *(str + i);
	}
	T.length = a;
	return OK;
}

Status CreatHString(HString& T) {//键入常量串
	char str[MAXSIZE];
	cout << "输入字串：";
	cin >> str;
	PushHString(T, str);
	return OK;
}

Status CompareHString(HString T, HString S) {//比较串大小
	for (int i = 0;i < T.length && S.length;i++) {
		if (T.ch[i] != S.ch[i]) return T.ch[i] - S.ch[i];
	}
	return T.length - S.length;
}

Status SubHString(HString& S, HString T, int pos, int len) {//返回T中从pos位起长度为len的子串
	if (pos<0 || pos>T.length || len<0 || len>T.length) return ERROR;
	S.ch = (char*)malloc(len * sizeof(char));
	for (int i = 0;i < len;i++) {
		S.ch[i] = T.ch[pos + i-1];
	}
	S.length = len;
	return OK;
}

Status PrintHString(HString T) {//输出
	for (int i = 0;i < T.length;i++) {
		cout << T.ch[i];
	}
	cout << endl;
	return OK;
}

Status CopyHString(HString& S, HString T) {//复制串T
	S.ch = (char*)malloc(T.length * sizeof(char));
	for (int i = 0;i < T.length;i++) {
		S.ch[i] = T.ch[i];
	}
	S.length = T.length;
	return OK;
}

Status ClearHString(HString &T) {//清空串
	if (T.ch) {
		free(T.ch);
		T.ch = NULL;
	}
	T.length = 0;
	return OK;
}

Status EmptHString(HString T) {//判断表是否为空
	if (T.length == 0) return 1;
	else return 0;
}

Status sever(HString& S, HString& T) {//将串T分割为‘，’前和‘，’后两部分
	int n = T.length;int i = 0;int k = 0;//k为尚未配对的左括号数
										 //之所以要记录左括号数是因为有子串为原子表，没有‘，’出现
	HString ch;
	do {
		i++;
		SubHString(ch, T, i, 1);
		if (ch.ch[0] == '(') ++k;
		else if (ch.ch[0] == ')') --k;
	} while (i < n && (ch.ch[0] != ',' || k != 0));//当k为零，即说明已经搜索了一队括号的内容
												   //也即说明当前串为原子表，没有‘，’
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

Status CreatGList(GList& L, HString T) {//创建广义表
	HString emp, sub, str;
	GList p, q;
	PushHString(emp, "()");
	//当T为空表串,置空广义表
	if (!CompareHString(T, emp)) L = NULL;//创建空表
	else {
		if (!(L = (GList)malloc(sizeof(GLNode)))) return ERROR;
	//当T为单字符串，建立原子结点子表
		if (T.length == 1) {
			L->tag = ATOM;
			L->atom = T.ch[0];
		}
	//归纳项
		else {
			L->tag = LIST;p = L;
			SubHString(sub, T, 2, T.length - 2);//脱去外层括号
			do {
				sever(str, sub);//第一次编写为sever(str,T)...一直报错，找了三四个钟头！！！
				CreatGList(p->ptr.hp, str);q = p;//hp为建立子表的头指针
				if (!EmptHString(sub)) {
					p = (GList)malloc(sizeof(GLNode));//tp指向在它之后建立的结点
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

Status DepthGList(GList L) {//求列表深度
	if (!L) return 1;//空表深度为1
    if (L->tag == 0) return 0;//原子表深度为0
	int dep, max ;GList pp;
	for (max = 0, pp=L;pp;pp = pp->ptr.tp) {//遍历列表，归纳项为列表深度为各个子表深度最大值加1
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
	cout << "开始截取位置：";
	cin >> pos;
	cout << "截取长度：";
	cin >> len;
	SubHString(R, T,pos,len);
	PrintHString(R);
	CopyHString(B, T);
	PrintHString(B);
	ClearHString(B);
	PrintHString(B);*///测试串的操作模块是否正确
	HString S, T;
	CreatHString(T);
	GList L;
	CreatGList(L, T);
	PrintGList2(L);
	int a = DepthGList(L);
	cout << a;
	return OK;
}