#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <memory.h>
#include<windows.h>
using namespace std;

#define OK 1
#define OVERFLOW -2
#define ERROR -1
#define MAXSIZE 100   //��Ԫ�����󳤶�

typedef int Status;
typedef int ElemType;
typedef struct {
	int i, j;//�洢Ԫ���±�
	ElemType v;
}Triple;
typedef struct {
	Triple data[MAXSIZE+1];//data[0]���ã�
	int mu, nu, tu;//���������������Լ�����Ԫ�ظ�����
	int rpos[MAXSIZE];//��¼ÿ�з���Ԫ�ش洢λ��;
}RLSMatrix;

Status InitMatrix(RLSMatrix& M) {//������Ԫ��
	//��������
	for (int i = 0;i < MAXSIZE + 2;i++) {
		M.data[i].v = 0;
	}
	cout << "������ϡ�����������������Լ�����Ԫ����"<<endl;
	cin >> M.mu >> M.nu >> M.tu;cout ;
	cout << "�밴��������" << M.tu << "��Ԫ�������С����Լ�Ԫ��ֵ��" << endl;
	for (int col = 1;col < M.tu + 1;col++) {
		cin >> M.data[col].i >> M.data[col].j >> M.data[col].v;
	}
	//��rpos[]ֵ
	int num[MAXSIZE];
	for (int col = 0;col < MAXSIZE;col++) num[col] = 0;
	for (int row = 1;row < M.tu + 1;row++) num[M.data[row].i]++;//��ÿ�з���Ԫ�ظ�����
	M.rpos[1] = 1;
	for (int roc = 2;roc < M.mu +1;roc++) M.rpos[roc] = M.rpos[roc - 1] + num[roc - 1];
	if (num[M.mu] == 0) M.rpos[M.mu] = NULL;//�������ж����һ��rposֵ�Ƿ�������
	                                        //�����һ��ȫ����Ԫ�أ����յ��ƹ�ʽ�����һ����rposֵ��ʵ����û�У�
	return OK;
}

Status Check(RLSMatrix M, int a, int b) {//����Ƿ����Ԫ��
	for (int k = 1;k < M.tu + 1;k++) {
		if (M.data[k].i == a && M.data[k].j == b)
			return k;
	}
	return 0;
}

Status PrintMatrix(RLSMatrix M) {//��ӡϡ�����
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

Status TransposeMatrix1(RLSMatrix M, RLSMatrix& N) {//ת�þ��󷽷�1
	N.mu = M.nu;N.nu = M.mu;N.tu = M.tu;
	int q = 1;
	for (int a = 1;a < M.nu + 1;a++) {//��M����N��ÿһ�У���M������洢������ֻҪ��M���ҵ���Ӧ�е��о���N���У�
		for (int b = 1;b < M.tu + 1;b++) {//����M�е�ÿһ�У�����������±��Ƿ�����������
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

Status TransposeMatrix2(RLSMatrix M, RLSMatrix& N) {//����ת�÷�����
	N.mu = M.nu;N.nu = M.mu;N.tu = M.tu;
	//��ÿ�е�һ������Ԫ����N.data�е�λ�ã���ΪM������洢����M��������洢��N�У����൱��ת�ú��M������洢
	int num2[MAXSIZE];//���ڴ洢ÿ�з���Ԫ�ظ���
	for (int col = 0;col <  MAXSIZE;col++) num2[col] = 0;//����Ҫ�ǵó�ʼ����ӦΪ����ֱ�ӿ�ʼ���㡣�ȸ�ֵ�������㣻
	for (int col = 1;col < M.tu + 1;col++) num2[M.data[col].j]++;
	int rpos1[MAXSIZE];//���ڴ洢ÿ�е�һ������Ԫ����N.data�е�λ�ã�
	rpos1[1] = 1; //����ͬ���ȸ�ֵ�����㣡����������õ�������Ȼ��֪����һ�е�һ������Ԫ�ش洢�������һλ��
	for (int row = 2;row < M.nu+1;row++) rpos1[row] = rpos1[row - 1] + num2[row - 1];//һ��Ҫע�⣬����row��2��ʼ
	//ת��
	for (int col = 1;col < M.tu + 1;col++) {
		int q,p;
		q = M.data[col].j;p = rpos1[q];
		N.data[p].i = M.data[col].j;N.data[p].j = M.data[col].i;
		N.data[p].v = M.data[col].v;
		rpos1[q]++;//����ܹؼ������������˸��еڶ�������Ԫ����N.data�е�λ�ã�
	}
	return OK;
}

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix& Q) {//����˷�
	Q.mu = M.mu;Q.nu = N.nu;Q.tu = 0;
	int tp,cp,a=1;
	int temp[MAXSIZE];//��¼Q�������ݵ��ۼ���
	//����Q��ÿһ��
	for (int col = 1;col < M.mu + 1;col++) {
		for (int e = 0;e < MAXSIZE;e++) {
			temp[e] = 0;
		}
		if (col < M.mu) tp = M.rpos[col + 1];//������жϷǳ���Ҫ���ǿ��Ǿ������һ��Ϊ��Ԫ���У�
		else {                               //������һ��Ϊ��Ԫ���У�tpֵӦ��Ϊ�㣻
			if (M.rpos[col] == 0)            //����tp���㣬�����������ὫQ���һ�е�Ԫ�ظ��ģ�Ҳ�п��ܷ����ڴ����Ȩ�޳�ͻ��
				tp = 0;
			else tp = M.tu+1; 
		}
		//����ǰ�е�ÿһ������Ԫ��
		for (int row = M.rpos[col];row < tp ;row++) {
			int brow = M.data[row].j;
			if (brow < N.mu) cp = N.rpos[brow + 1];
			else {
				if (N.rpos[brow] == 0)
					cp = 0;
				else cp = N.tu + 1;
			}
			//�Ե�ǰÿ��Ԫ����N���ҵ���Ӧ��Ԫ�����
			for (int p = N.rpos[brow];p < cp ;p++) {
				int cool = N.data[p].j;
				temp[cool] += M.data[row].v * N.data[p].v;
			}
		}
		//�����Q�ĵ�ǰ�д���Q.data��
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
	cout << "�������Ϊ��" << endl;
	PrintMatrix(M);
	cout << "����һת�ã�" << endl;
	TransposeMatrix1(M, N);
	PrintMatrix(N);
	cout << "������ת�ã�" << endl;
	TransposeMatrix2(M, Q);
	PrintMatrix(Q);
	cout << "����˷�" << endl;
	RLSMatrix T;
	RLSMatrix R;
	InitMatrix(T);
	cout << "�������Ϊ��" << endl;
	PrintMatrix(T);
	MultSMatrix(M, T, R);
	cout << "���Ϊ��" << endl;
	PrintMatrix(R);
	return OK;
}