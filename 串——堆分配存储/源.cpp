#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct {
	char* ch;
	int length;
}HString;

Status StrAssign(HString& T, char* chars) {/*����������ֵ�����մ�T*/
	if (T.ch) free(T.ch);
	int a = strlen(chars);
	if (!a) { T.ch = NULL;T.length = 0; }
	else {
		T.ch = (char*)malloc(a * sizeof(char));
		if (!T.ch) exit(OVERFLOW);
		for (int i = 0;i < a;i++) {
			T.ch[i] = *(chars + i);
		}
		T.length = a;
	}
	return OK;
}
Status StrLength(HString T) {/*���ش�TԪ�ظ�������Ϊ������*/
	return T.length;
}

Status StrCompare(HString T, HString S) {/*�Ƚ���������С*/
	for (int i = 0;i < T.length && i<S.length;i++)
		if (T.ch [i]!= S.ch[i]) return T.ch[i]-S.ch[i];
	return T.length - S.length;
}

Status ClearString(HString& T) {/*��մ�*/
	if (T.ch) {
		free(T.ch);
		T.ch = NULL;
	}
	T.length = 0;
	return OK;
}
Status Concat(HString& T, HString S, HString R) {/*���������ִ�*/
	if (T.ch) free(T.ch);
	int a = S.length + R.length;
	if (!a) { T.ch = NULL;T.length = 0; }
	else {
		if (!(T.ch = (char*)malloc(a * sizeof(char))))
			exit(OVERFLOW);
		for (int i = 0;i < S.length;i++)
			T.ch[i] = S.ch[i];
		for (int i = S.length;i < a;i++)
			T.ch[i] = R.ch[i];
		T.length = a;
	}
	return OK;
}


