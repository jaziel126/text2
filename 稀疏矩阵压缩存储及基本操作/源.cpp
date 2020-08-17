#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <memory.h>
#include<windows.h>
using namespace std;

#define OK 1
#define OVERFLOW -2
#define ERROR -1
#define MAXSIZE 100   //三元组表最大长度

typedef int Status;
typedef int ElemType;
typedef struct {
	int i, j;//存储元素下标
	ElemType v;
}Triple;
typedef struct {
	Triple data[MAXSIZE+1];//data[0]闲置；
	int mu, nu, tu;//矩阵行数，列数以及非零元素个数；
	int rpos[MAXSIZE];//记录每行非零元素存储位置;
}RLSMatrix;

Status InitMatrix(RLSMatrix& M) {//创建三元表
	//输入数据
	for (int i = 0;i < MAXSIZE + 2;i++) {
		M.data[i].v = 0;
	}
	cout << "请输入稀疏矩阵的行数、列数以及非零元个数"<<endl;
	cin >> M.mu >> M.nu >> M.tu;cout ;
	cout << "请按行序输入" << M.tu << "个元素所在行、列以及元素值；" << endl;
	for (int col = 1;col < M.tu + 1;col++) {
		cin >> M.data[col].i >> M.data[col].j >> M.data[col].v;
	}
	//求rpos[]值
	int num[MAXSIZE];
	for (int col = 0;col < MAXSIZE;col++) num[col] = 0;
	for (int row = 1;row < M.tu + 1;row++) num[M.data[row].i]++;//求每行非零元素个数；
	M.rpos[1] = 1;
	for (int roc = 2;roc < M.mu +1;roc++) M.rpos[roc] = M.rpos[roc - 1] + num[roc - 1];
	if (num[M.mu] == 0) M.rpos[M.mu] = NULL;//这里是判断最后一个rpos值是否正常；
	                                        //当最后一行全是零元素，按照递推公式，最后一行有rpos值，实际上没有；
	return OK;
}

Status Check(RLSMatrix M, int a, int b) {//检查是否非零元素
	for (int k = 1;k < M.tu + 1;k++) {
		if (M.data[k].i == a && M.data[k].j == b)
			return k;
	}
	return 0;
}

Status PrintMatrix(RLSMatrix M) {//打印稀疏矩阵
	int t = 0;
	for (int a = 1;a < M.mu + 1;a++) {
		for (int b = 1;b < M.nu + 1;b++) {
			if(t=Check(M,a,b)) 
				cout << M.data[t].v; 
			/*for(int k=1;k<M.tu+1;k++){
				if (M.data[k].i == a && M.data[k].j == b) cout << M.data[k].v;
				else cout << "0";
			}//for k*/
			else cout << "0";
			cout << "   ";
		}//for b
		cout << endl;
	}//for a
	return OK;
}

Status TransposeMatrix1(RLSMatrix M, RLSMatrix& N) {//转置矩阵方法1
	N.mu = M.nu;N.nu = M.mu;N.tu = M.tu;
	int q = 1;
	for (int a = 1;a < M.nu + 1;a++) {//在M中找N的每一行，而M按行序存储，所以只要在M中找到对应行的列就是N的行；
		for (int b = 1;b < M.tu + 1;b++) {//搜索M中的每一行，检查它的列下标是否满足条件；
			if (M.data[b].j == a) {
				N.data[q].i = M.data[b].j;
				N.data[q].j = M.data[b].i;
				N.data[q].v = M.data[b].v;
				q++;
			}
		}//for b
	}//for a
	return OK;
}

Status TransposeMatrix2(RLSMatrix M, RLSMatrix& N) {//矩阵转置方法二
	N.mu = M.nu;N.nu = M.mu;N.tu = M.tu;
	//求每列第一个非零元素在N.data中的位置；因为M按行序存储，把M按照列序存储在N中，就相当于转置后的M按行序存储
	int num2[MAXSIZE];//用于存储每列非零元素个数
	for (int col = 0;col <  MAXSIZE;col++) num2[col] = 0;//这里要记得初始化，应为下面直接开始运算。先赋值，再运算；
	for (int col = 1;col < M.tu + 1;col++) num2[M.data[col].j]++;
	int rpos1[MAXSIZE];//用于存储每列第一个非零元素在N.data中的位置；
	rpos1[1] = 1; //这里同理，先赋值再运算！下面运算会用到，而显然易知，第一行第一个非零元素存储在数组第一位；
	for (int row = 2;row < M.nu+1;row++) rpos1[row] = rpos1[row - 1] + num2[row - 1];//一定要注意，这里row从2开始
	//转置
	for (int col = 1;col < M.tu + 1;col++) {
		int q,p;
		q = M.data[col].j;p = rpos1[q];
		N.data[p].i = M.data[col].j;N.data[p].j = M.data[col].i;
		N.data[p].v = M.data[col].v;
		rpos1[q]++;//这里很关键，这就是求出了该列第二个非零元素在N.data中的位置；
	}
	return OK;
}

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix& Q) {//矩阵乘法
	Q.mu = M.mu;Q.nu = N.nu;Q.tu = 0;
	int tp,cp,a=1;
	int temp[MAXSIZE];//记录Q各行数据的累加器
	//处理Q的每一行
	for (int col = 1;col < M.mu + 1;col++) {
		for (int e = 0;e < MAXSIZE;e++) {
			temp[e] = 0;
		}
		if (col < M.mu) tp = M.rpos[col + 1];//这里的判断非常重要，是考虑矩阵最后一行为零元素行；
		else {                               //如果最后一行为零元素行，tp值应该为零；
			if (M.rpos[col] == 0)            //不将tp归零，后面继续计算会将Q最后一行的元素更改；也有可能发生内存访问权限冲突；
				tp = 0;
			else tp = M.tu+1; 
		}
		//处理当前行的每一个非零元素
		for (int row = M.rpos[col];row < tp ;row++) {
			int brow = M.data[row].j;
			if (brow < N.mu) cp = N.rpos[brow + 1];
			else {
				if (N.rpos[brow] == 0)
					cp = 0;
				else cp = N.tu + 1;
			}
			//对当前每个元素在N中找到相应的元素相乘
			for (int p = N.rpos[brow];p < cp ;p++) {
				int cool = N.data[p].j;
				temp[cool] += M.data[row].v * N.data[p].v;
			}
		}
		//将求的Q的当前行存入Q.data中
		for (int n = 1;n < N.nu+1;n++) {
			if (temp[n]) {
				Q.tu++;
				Q.data[Q.tu] = { col,n,temp[n] };
			}
		}
	}
	return OK;
}

int main() {
	RLSMatrix M;
	RLSMatrix N;
	RLSMatrix Q;
	InitMatrix(M);
	cout << "输入矩阵为：" << endl;
	PrintMatrix(M);
	cout << "方法一转置：" << endl;
	TransposeMatrix1(M, N);
	PrintMatrix(N);
	cout << "方法二转置：" << endl;
	TransposeMatrix2(M, Q);
	PrintMatrix(Q);
	cout << "矩阵乘法" << endl;
	RLSMatrix T;
	RLSMatrix R;
	InitMatrix(T);
	cout << "输入矩阵为：" << endl;
	PrintMatrix(T);
	MultSMatrix(M, T, R);
	cout << "结果为：" << endl;
	PrintMatrix(R);
	return OK;
}