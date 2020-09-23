#include<iostream>
#include<string.h>
using namespace std;
#define OK 1
#define ORRER -1
typedef int Status;
typedef struct {
	 int weight;
	 int parent, lchild, rchild;
}HTNode,*HuffManTree;
typedef char* * HuffManCude;

Status min(HuffManTree& HT, int k) {//��HT������ѡ����С��parentΪ0��Ԫ��
	int min_weight;//�������weight��С��ֵ
	int min;//�������weightֵ��С�����
	int i = 1;
	//��¼��һ��Ԫ�أ���������Ƚϵı�׼��
	while (HT[i].parent != 0)
		i++;
	min = i;
	min_weight = HT[i].weight;
	//Ѱ����СԪ��
	for (;i < k + 1;i++) {
		if (HT[i].weight < min_weight && HT[i].parent == 0) {
			min = i;
			min_weight = HT[i].weight;
		}
	}
	//ѡ����СԪ�غ󽫸�Ԫ�ص�parentֵ��1��ʹ����һ�αȽϽ����ų����⣻
	HT[min].parent = 1;//�տ�ʼ��д��ʱ������minֱ��д��i��һֱ����
	                   //��ϸ�������ѷ��֣�Ϊiʱ��min=i�����Ǻ���i�������ѭ���ı䣬��min��=i��
	return min;
}

Status min_2(HuffManTree& HT, int k,int &min1,int &min2) {//��HT�����ǰk��Ԫ����ѡ����С����������������Ӧ�����
	min1 = min(HT, k);
	min2 = min(HT, k);
	return OK;
}

Status CreatHuffManTree(HuffManTree& HT, int *w,int n) {//����շ�����
	//��a����Ϊn���Ӽ���
	int m = 2 * n - 1;
	HT = (HuffManTree)malloc((m+1) * sizeof(HTNode));
	HuffManTree p;
	int i;
	for (  i = 1;i < n + 1;++i) {
		w++;
		HT[i] = { *w,0,0,0 };
	}
	for (;i < m + 1;++i) {
		HT[i] = { 0,0,0,0 };
	}
	//�����շ�����
	int s1, s2;//���ڼ�¼��С��Ԫ�ص����
	for (int i = n + 1;i < m + 1;i++) {
		min_2(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	return OK;
}

Status HuffManCoding(HuffManTree HT, HuffManCude& HC,int n) {//��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
	HC = (HuffManCude)malloc((n+1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int start = 0;
	//����ַ���շ�������
	for (int i = 1;i < n + 1;++i) {
		start = n - 1;
		for (int c = i, f = HT[i].parent;f != 0;c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) cd[--start] = '0';//���ﲻ����˫����
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	return OK;
}

int main() {
	int n;
	cout << "������Ҫ���б������ĸ������";
	cin >> n;
	cout << "�������������Ҫ������ĸ���ֵĴ�����";
	int* a = (int*)malloc(n * sizeof(int));
	for (int i = 1;i < n + 1;i++) {
		cin >> a[i];
	}
	HuffManTree HT;
	CreatHuffManTree(HT,a,n);
	HuffManCude HC;
	HuffManCoding(HT, HC, 8);
	for (int i = 1;i < 9;i++) {
		cout<<"��"<<i<<"���ַ�����Ϊ" << HC[i]<<endl;
		
	}
	return OK;
}