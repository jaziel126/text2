#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define MAXSIZELINE 255
#define TURE 1
#define FALSE 0
#define OK 1
typedef unsigned char SString[MAXSIZELINE + 1];
/*����֮����Ҫ��unsigned char����Ϊchar�����ܱ�ʾ�����ķ�Χ��-128-127,��unsigned char���ͱ�ʾ
�����ķ�Χ��0-256��*/
typedef int Status;

Status ScanfStr(SString& T) {
	char str[MAXSIZELINE];
	cout << "Ҫ������ִ���";
	cin >> str;
	StrPush(T, str);
	return OK;
}

Status StrPush(SString& T,char *str) {/*�����ַ���*/
	int a = strlen(str);
	if (a > MAXSIZELINE) {
		T[0] = MAXSIZELINE;
		for (int i = 1;i < MAXSIZELINE+1;i++) {
			T[i] = *(str + i - 1);
		}

	}
	else {
		T[0] = a;
		for (int j = 1;j < MAXSIZELINE+1;j++) {
			T[j] = *(str + j - 1);
		}
	}
	return OK;
}

Status Concat(SString& T, SString s1, SString s2) {/*���������ַ���*/
	if (s1[0] + s2[0] < MAXSIZELINE) {/*û�нض�*/
		T[0] = s1[0] + s2[0];
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		for (int i = 1;i < s2[0]+1;i++) {
			T[s1[0] + i] = s2[i];
		}
		return TURE;
	}
	else if (s1[0] + s2[0] > MAXSIZELINE) {/*�ض�*/
		T[0] = MAXSIZELINE;
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		for (int i = 1;i < MAXSIZELINE - s1[0] + 1;i++) {
			T[s1[0] + i] = s2[i];
		}
		return FALSE;
	}
	else {/*ֻ�ض�s2*/
		T[0] = s1[0];
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		return FALSE;
	}
}

Status StrPop(SString& T) {/*����ַ���*/
	
	for (int i = 1;i <= T[0];i++) {
		cout << T[i];
	}/*����ǧ����ֱ��cout<<T,�������������Խ��*/
	cout << endl;
	return OK;
}

Status SbString(SString& T, SString S, int pos, int len) {/*�ڴ�T�д�ָ��λ�ø��Ƴ���Ϊlen���ִ���S*/
	if (pos<1 || pos>S[0] || len<0 || len>MAXSIZELINE - T[0]) return ERROR;
	for (int i = 1;i < len + 1;i++) {
		T[ i] = S[pos + i-1];
	}
	T[0] = len;
	return OK;
}

int main() {
	SString T,sub,a,c;
	ScanfStr(T);
	StrPop(T);
	ScanfStr(sub);
	StrPop(sub);
	Concat(a, T, sub);
	StrPop(a);
	cout << "��ʼ������������������������������";
	int pos, len;
	cout << "��ʼλ�ã�";
	cin >> pos;
	cout << "�������ȣ�";
	cin >> len;
	SbString(sub, a, pos, len);
	StrPop(sub);
	return OK;
}
