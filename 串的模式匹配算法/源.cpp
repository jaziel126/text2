#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
using namespace std;

#define OK 1

typedef int Status;
typedef struct {/*采用堆分配存储结构*/
	char* ch;
	int length;
}SString;

Status Init_Str(SString &T,char *chars) {/*将常量串赋值给空串T*/
	//if (T.ch) free(T.ch);
	int a = strlen(chars);
	if (!a) { T.ch = NULL;T.length = 0; }
	else {
		T.ch = (char*)malloc(a * sizeof(char));
		for (int i = 0;i < a;i++) {
			T.ch[i] = *(chars+i);//这里T.ch是一个指针数组，重点在数组；而chars是一个数组指针，重点是一个指针
		}
		T.length = a;
	}
	return OK;
}

Status input(SString T) {//输出函数
	for (int i = 0;i < T.length;i++) {
		cout << T.ch[i];
	}
	return OK;
}

Status ScanfStr(SString &T) {//输入函数
	char* s;
	s = (char*)malloc(100 * sizeof(char));
	cin >> s;
	Init_Str(T, s);
	return OK;
}

Status ViolentMatch(SString T, SString S) {//暴力匹配
	int i, j;
	i = j = 0;
	while (i < T.length &&j<S.length) {
		if (T.ch[i] == S.ch[j]) {//一定要注意：赋值用=；相等用==；
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == S.length) 
		return i-j;
	else return -1;
}

Status KMPSearch(SString T, SString S,int next[]) {//KMP模式匹配算法
	int i, j;
	i = j = 0;
	while (i < T.length && j < S.length) {
		if (j == -1 || T.ch[i] == S.ch[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == S.length)
		return i - j;
	else 
		return -1;
}

Status GetNext(SString T, int next[]) {//求next数组
	int i = 0;
	int k = 0;
	next[0] = -1;
	while (i < T.length - 1) {//i表示前缀，k表示后缀；
		if (k == -1 || T.ch[i] == T.ch[k]) {
			i++;
			k++;
			if (T.ch[i] != T.ch[k]) {
				next[i] = k;
			}
			else {
				next[i] = next[k];
			}
		}
		else {
			k = next[k];
		}
	}
	return OK;
}
int main() {
	SString T,S;
	ScanfStr(T);
	ScanfStr(S);
	cout << T.length << S.length << endl;//打印模式串和匹配串长度；
	int a = ViolentMatch(T, S);
	cout << a << endl;
	cout << "*************暴力匹配****************" << endl;
	SString H, A;
	ScanfStr(H);
	ScanfStr(A);
	cout << H.length << A.length << endl;//打印模式串和匹配串长度；
	int* next;
	next = (int*)malloc(100 * sizeof(int));
	GetNext(H, next);
	int b=KMPSearch(H, S, next);
	cout << b<<endl;
	cout << "*************KMP模式匹配**************" << endl;
	return OK;
}