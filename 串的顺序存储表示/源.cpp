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
/*这里之所以要用unsigned char是因为char类型能表示的数的范围在-128-127,而unsigned char类型表示
的数的范围在0-256；*/
typedef int Status;

Status ScanfStr(SString& T) {
	char str[MAXSIZELINE];
	cout << "要输入的字串：";
	cin >> str;
	StrPush(T, str);
	return OK;
}

Status StrPush(SString& T,char *str) {/*输入字符串*/
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

Status Concat(SString& T, SString s1, SString s2) {/*连接两个字符串*/
	if (s1[0] + s2[0] < MAXSIZELINE) {/*没有截断*/
		T[0] = s1[0] + s2[0];
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		for (int i = 1;i < s2[0]+1;i++) {
			T[s1[0] + i] = s2[i];
		}
		return TURE;
	}
	else if (s1[0] + s2[0] > MAXSIZELINE) {/*截断*/
		T[0] = MAXSIZELINE;
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		for (int i = 1;i < MAXSIZELINE - s1[0] + 1;i++) {
			T[s1[0] + i] = s2[i];
		}
		return FALSE;
	}
	else {/*只截断s2*/
		T[0] = s1[0];
		for (int i = 1;i < s1[0] + 1;i++) {
			T[i] = s1[i];
		}
		return FALSE;
	}
}

Status StrPop(SString& T) {/*输出字符串*/
	
	for (int i = 1;i <= T[0];i++) {
		cout << T[i];
	}/*这里千万不能直接cout<<T,这样会数组输出越界*/
	cout << endl;
	return OK;
}

Status SbString(SString& T, SString S, int pos, int len) {/*在串T中从指定位置复制长度为len的字串到S*/
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
	cout << "开始拷贝。。。。。。。。。。。。。";
	int pos, len;
	cout << "开始位置：";
	cin >> pos;
	cout << "拷贝长度：";
	cin >> len;
	SbString(sub, a, pos, len);
	StrPop(sub);
	return OK;
}
