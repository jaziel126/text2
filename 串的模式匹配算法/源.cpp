#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
using namespace std;

#define OK 1

typedef int Status;
typedef struct {/*���öѷ���洢�ṹ*/
	char* ch;
	int length;
}SString;

Status Init_Str(SString &T,char *chars) {/*����������ֵ���մ�T*/
	//if (T.ch) free(T.ch);
	int a = strlen(chars);
	if (!a) { T.ch = NULL;T.length = 0; }
	else {
		T.ch = (char*)malloc(a * sizeof(char));
		for (int i = 0;i < a;i++) {
			T.ch[i] = *(chars+i);//����T.ch��һ��ָ�����飬�ص������飻��chars��һ������ָ�룬�ص���һ��ָ��
		}
		T.length = a;
	}
	return OK;
}

Status input(SString T) {//�������
	for (int i = 0;i < T.length;i++) {
		cout << T.ch[i];
	}
	return OK;
}

Status ScanfStr(SString &T) {//���뺯��
	char* s;
	s = (char*)malloc(100 * sizeof(char));
	cin >> s;
	Init_Str(T, s);
	return OK;
}

Status ViolentMatch(SString T, SString S) {//����ƥ��
	int i, j;
	i = j = 0;
	while (i < T.length &&j<S.length) {
		if (T.ch[i] == S.ch[j]) {//һ��Ҫע�⣺��ֵ��=�������==��
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

Status KMPSearch(SString T, SString S,int next[]) {//KMPģʽƥ���㷨
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

Status GetNext(SString T, int next[]) {//��next����
	int i = 0;
	int k = 0;
	next[0] = -1;
	while (i < T.length - 1) {//i��ʾǰ׺��k��ʾ��׺��
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
	cout << T.length << S.length << endl;//��ӡģʽ����ƥ�䴮���ȣ�
	int a = ViolentMatch(T, S);
	cout << a << endl;
	cout << "*************����ƥ��****************" << endl;
	SString H, A;
	ScanfStr(H);
	ScanfStr(A);
	cout << H.length << A.length << endl;//��ӡģʽ����ƥ�䴮���ȣ�
	int* next;
	next = (int*)malloc(100 * sizeof(int));
	GetNext(H, next);
	int b=KMPSearch(H, S, next);
	cout << b<<endl;
	cout << "*************KMPģʽƥ��**************" << endl;
	return OK;
}