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

Status min(HuffManTree& HT, int k) {//从HT数组中选出最小且parent为0的元素
	int min_weight;//用来存放weight最小的值
	int min;//用来存放weight值最小的序号
	int i = 1;
	//记录第一个元素，用作后面比较的标准；
	while (HT[i].parent != 0)
		i++;
	min = i;
	min_weight = HT[i].weight;
	//寻找最小元素
	for (;i < k + 1;i++) {
		if (HT[i].weight < min_weight && HT[i].parent == 0) {
			min = i;
			min_weight = HT[i].weight;
		}
	}
	//选出最小元素后将该元素的parent值赋1，使得下一次比较将其排除在外；
	HT[min].parent = 1;//刚开始编写的时候这里min直接写成i，一直报错
	                   //仔细分析不难发现，为i时，min=i，但是后面i还会继续循环改变，则min！=i；
	return min;
}

Status min_2(HuffManTree& HT, int k,int &min1,int &min2) {//从HT数组的前k个元素中选出最小的两个，并返回相应的序号
	min1 = min(HT, k);
	min2 = min(HT, k);
	return OK;
}

Status CreatHuffManTree(HuffManTree& HT, int *w,int n) {//构造赫夫曼树
	//将a划分为n个子集；
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
	//构建赫夫曼树
	int s1, s2;//用于记录最小两元素的序号
	for (int i = n + 1;i < m + 1;i++) {
		min_2(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	return OK;
}

Status HuffManCoding(HuffManTree HT, HuffManCude& HC,int n) {//从叶子到根逆向求每个字符的赫夫曼编码
	HC = (HuffManCude)malloc((n+1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int start = 0;
	//逐个字符求赫夫曼编码
	for (int i = 1;i < n + 1;++i) {
		start = n - 1;
		for (int c = i, f = HT[i].parent;f != 0;c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) cd[--start] = '0';//这里不能用双引号
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
	cout << "请输入要进行编码的字母数量：";
	cin >> n;
	cout << "请依次输入各个要编码字母出现的次数：";
	int* a = (int*)malloc(n * sizeof(int));
	for (int i = 1;i < n + 1;i++) {
		cin >> a[i];
	}
	HuffManTree HT;
	CreatHuffManTree(HT,a,n);
	HuffManCude HC;
	HuffManCoding(HT, HC, 8);
	for (int i = 1;i < 9;i++) {
		cout<<"第"<<i<<"个字符编码为" << HC[i]<<endl;
		
	}
	return OK;
}