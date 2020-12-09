#include<iostream>
#include<stdlib.h>
using namespace std;
#define OK 1
#define ERROR -1
#define INFINITY INT_MAX  //���ֵ
#define MAX_VERTEX_NUM 20  //��󶥵����

typedef int Status;//��������
typedef int VRType;//�����ϵ����
typedef int InfoType;//����Ϣָ��
typedef char VertexType;//����ֵ
typedef enum { DG, DN, UDG, UDN }GraphKind;//{����ͼ��������������ͼ��������}

bool visited[MAX_VERTEX_NUM];//���ʱ�־����
int MAX_QUEUE_SIZE;//ȫ�ֱ��������ڴ洢�������д�С

typedef struct ArcCell {
	VRType adj;//��ʾ�Ƿ�����
	InfoType * info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum, arcsnum;//ͼ��ǰ���㡢����
	GraphKind kind;//ͼ������
}MGraph;

typedef struct {
	int* data;
	int top;
	int base;
	int length;
}List;//���ﲻ����*GList����ָ�룬�������Q->data=(int *)malloc(n*sizeof(int));�ᱨ�������ṹ�岻��˫ָ�룻

Status InitQueue(List &Q,MGraph G) {
	MAX_QUEUE_SIZE = 20;
	Q.data= (int*)malloc(MAX_QUEUE_SIZE * sizeof(int));
	Q.top = Q.base = 0;
	Q.length = G.vexnum;
	return OK;
}

Status EnQueue(List& Q,int v) {
	if ((Q.base + 1) % MAX_QUEUE_SIZE == Q.top) return ERROR;//������
	Q.data[Q.base] = v;
	Q.base = (Q.base + 1) % MAX_QUEUE_SIZE;
	return OK;
}

Status DeQueue(List& Q, int &v) {
	if (Q.base == Q.top) return ERROR;//����Ϊ��
	v = Q.data[Q.top];
	Q.top = (Q.top + 1) % MAX_QUEUE_SIZE;//������⣬��ͷԪ�س�ջ�����ͷָ������һλ
	return OK;
}

Status QueueEmpty(List Q) {
	if (Q.base == Q.top)
		return OK;
}

typedef struct {
	int* base;
	int* top;
	int szie;
}Stack;

Status InitStack(Stack &stack,int size) {
	stack.base = (int*)malloc(size * sizeof(int));
	stack.top = stack.base;
	stack.szie = size;
	return OK;
}

Status Push(Stack& stack, int val) {
	*stack.top = val;
	stack.top += 1;
	return OK;
}

Status Pop(Stack& stack) {
	// int val = *stack.top; ����Ū���ˣ�һ��Ҫ���ƶ�ָ�룬�ٸ�ֵ
	stack.top = stack.top - 1;
	int val = *stack.top;
	return val;
}

Status EmptyStack(Stack stack) {
	if (stack.base == stack.top)
		return OK;
	else return 0;// ���ﲻ�ܷ���-1����Ϊ-1���棬Ҫ����0
}

Status LocateVex(MGraph G,VertexType v) {
	for (int i = 0;i < G.vexnum;++i) {
		if (G.vexs[i] == v) return i;
	}
	return ERROR;
}

Status CreatUDN(MGraph& G) {//����������
	cout << "����ͼ�Ķ��㡢������";
	cin >> G.vexnum >> G.arcsnum;
	cout << "���������������";
	for (int i = 0;i < G.vexnum;++i) {
		cin >> G.vexs[i];
	}
	//��ʼ���ڽӾ���
	for (int i = 0;i < G.vexnum;++i) 
		for (int j = 0;j < G.vexnum;++j) 
			G.arcs[i][j] = { INFINITY,NULL };
	//�����ڽӾ���
	VertexType v1, v2;
	int m,n;
	VRType w;
	for (int i = 0;i < G.arcsnum;++i) {
		cout << "�����μ�����������Ķ��㼰Ȩֵ��";
		cin >> v1 >> v2 >> w;
		m = LocateVex(G, v1);n = LocateVex(G, v2);
		G.arcs[m][n].adj = w;
		G.arcs[n][m].adj = w;
	}
	return OK;
}

Status CreatDN(MGraph& GT) {//����������
	cout << "����ͼ�Ķ��㡢������";
	cin >> GT.vexnum >> GT.arcsnum;
	cout << "���������������";
	for (int i = 0;i < GT.vexnum;++i) {
		cin >> GT.vexs[i];
	}
	//��ʼ���ڽӾ���
	for (int i = 0;i < GT.vexnum;++i)
		for (int j = 0;j < GT.vexnum;++j)
			GT.arcs[i][j] = { INFINITY,NULL };
	//�����ڽӾ���
	VertexType v1, v2;
	int m, n;
	VRType w;
	for (int i = 0;i < GT.arcsnum;++i) {
		cout << "�����μ�����������Ķ��㼰Ȩֵ��";
		cin >> v1 >> v2 >> w;
		m = LocateVex(GT, v1);n = LocateVex(GT, v2);
		GT.arcs[m][n].adj = w;
	}
	return OK;
}

Status PrintVex(MGraph G) {
	cout << endl;
	for (int i = 0;i < G.vexnum;i++) {
		for (int j = 0;j < G.vexnum;j++) {
			if (G.arcs[i][j].adj == INFINITY) {
				cout << "��";
				cout << "    ";
			}
			else {
				cout << G.arcs[i][j].adj;
				cout << "    ";
			}
		}
		cout << endl;
	}

	return OK;
}

Status NumVex(MGraph G,int v) {
	cout << G.vexs[v];
	return OK;
}

Status FirstAdjVex(MGraph G, int v) {//��v�ĵ�һ���ڽӵ�
	for (int i = 0;i < G.vexnum;i++) {
		if (G.arcs[v][i].adj != INFINITY)
			return i;
	}
	return ERROR;
}

Status NextAdjVex(MGraph G, int v, int w) {//����v(�����w)����һ���ڽӶ���
	for (int i = w+1;i < G.vexnum;++i) {
		if (G.arcs[v][i].adj != INFINITY)
			return i;
	}
	return ERROR;
}

Status DFS(MGraph G, int v,Status NumVex(MGraph G,int v)) {//�����������
	int w;
	visited[v] = true;
	NumVex(G,v);//�Ե�v��������ú���
	for (w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w)) 
		if(!visited[w])
			DFS(G, w, NumVex);
	return OK;
}
 
Status DFSTraverse(MGraph G) {
	//��ʼ����־����
	for (int i = 0;i < G.vexnum;++i)
		visited[i] = false;
	//��ÿ���������DFS����ֹͼΪ����ͨͼ
	for (int v = 0;v < G.vexnum;++v)
		if (!visited[v])
			DFS(G, v,NumVex);
	return	OK;
}

Status BFSTraverse(MGraph G, Status NumVex(MGraph G, int v)) {//�����������
	List Q;
	InitQueue(Q, G);
	for (int i = 0;i < G.vexnum;i++) visited[i] = false;//���ʱ�־�����ʼ��
	for (int v = 0;v < G.vexnum;v++) {
		//��ͷԪ����ջ
		if (!visited[v]) {
			visited[v] = true;
			NumVex(G, v);
			EnQueue(Q, v);
		//�Զ���ÿ��Ԫ�ر���
			while (!QueueEmpty(Q)) {
				int e;
				DeQueue(Q, e);
				if (!visited[e]) {
					visited[e] = true;
					NumVex(G, e);
					EnQueue(Q, e);
				}
			}
		}
	}
	return OK;
}

typedef struct CSNode {
	VertexType data;
	struct CSNode* firstchild, * nextsibling;
}CSNode, * CSTree;

Status DFSTree(MGraph G, CSTree& T, int v) {
	//�����ڷ��ʵĸö���ı�־Ϊ��Ϊtrue
	visited[v] = true;
	bool first = true;
	CSTree  q=NULL;
	//���α����ö���������ڽӶ���
	for (int w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w)) {
		//����ñ�־Ϊfalse��˵����û����
		if (!visited[w]) {
			CSTree p = (CSTree)malloc(sizeof(CSNode));
			if (!p) return ERROR;
			*p = { G.vexs[w],NULL,NULL };
			//�ý��ĵ�һ���ڽӶ�����Ϊ���ӽ�㣬�����ڽӶ�����Ϊ�ֵܽ��
			if (first) {
				T->firstchild = p;
				first = false;
			}
			else {
				q->nextsibling = p;//T->nextsibling=p;
			}
			q = p;
			//�Ե�ǰ���ʵĶ���Ϊ����������������������
			DFSTree(G, q, w);
		}
		//DFSTree(G,q,w);
	}
	return OK;
}

Status DFSForest(MGraph G, CSTree& T) {//��������ͼG���������������
	T = NULL;
	CSTree  q=NULL;
	for (int i = 0;i < G.vexnum;i++) visited[i] = false;
	for (int v = 0;v < G.vexnum;v++) {
		if (!visited[v]) {
			CSTree p = (CSTree)malloc(sizeof(CSNode));
			if (!p) return ERROR;
			*p = { G.vexs[v],NULL,NULL };
			if (!T)  T= p;
			else q->nextsibling = p;
			//ÿ�ζ�Ҫ��qָ��ָ���µĽ�㣬Ϊ�´���ӽ�����̵�
			q = p;
			DFSTree(G, p, v);//������pΪ����������
		}
	}
	return OK;
}

Status PrintTree(CSTree T) {
	if (!T) return ERROR;
	cout << T->data;
	PrintTree(T->firstchild);
	PrintTree(T->nextsibling);
	return OK;
}

struct student{
	VertexType adj;//�ı���U�������Ķ���
	VRType lowcost;//��С���۱�
};//������¼���飬���ڼ�¼��U��U-V�������С���۱�

Status mininum(student *closedge,MGraph G) {//�Ҽ�¼��������С�Ҵ�����ı�
	int min;
	int j = 0;
	while (closedge[j].lowcost == 0)
		j++;
	if (j == G.vexnum) return -1;
	min = closedge[j].lowcost;
	for (int i = 0;i < G.vexnum;i++) {
		if (closedge[i].lowcost < min && closedge[i].lowcost>0) {//һ��Ҫ������ס��||�ǻ�&&���ң�����
			min = closedge[i].lowcost;
			j = i;
		}
	}
	return j;
}

Status MiniSpanTree_Prime(MGraph& G, VertexType u) {//��¼�ӵ�u�������������������G����С������
	student closedge[MAX_VERTEX_NUM];//������¼���飬���ڼ�¼��U��U-V�������С���۱�
	//��ʼ����¼����
	int k = LocateVex(G, u);
	for (int i = 0;i < G.vexnum;i++) {
		if (i != k) {
			closedge[i].lowcost = G.arcs[k][i].adj;
			closedge[i].adj = u;
		}
	}
	closedge[k] = { u, 0};
	for (int i = 1;i < G.vexnum;i++) {
		//Ѱ����С�߲����
		k = mininum(closedge, G);
		if (k == -1) break;
		cout << closedge[k].adj << G.vexs[k]<<"  ";//����������ı�
		//���¼�¼����
		closedge[k].lowcost = 0;
		for (int j = 0;j < G.vexnum;j++) {
			if (G.arcs[k][j].adj < closedge[j].lowcost) {
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
			}
		}	
	}
	return OK;
}

typedef struct ArcNode {
	int adjvex;//�û�ָ��Ķ���λ��
	struct ArcNode* nextarc;//ָ����һ����ָ�룬���Ƕ�ָ����ͬ�Ľ��
	int inof;//�û�Ȩֵ
}ArcNode;
typedef struct VNode{
	VertexType vex;//��������
	struct ArcNode* firstarc;//ָ���һ�������ý��Ļ���ָ�룬�൱��ͷ���
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	int vexnum, arcnum;//ͼ�������ͻ���
	AdjList vertices;//��������
}ALGraph;

Status LocateVexDN(ALGraph G, VertexType v) {
	for (int i = 0;i < G.vexnum;++i) {
		if (G.vertices[i].vex == v) return i;
	}
	return ERROR;
}

Status CreatDN(ALGraph& M) {
	cout << "����ͼ�Ķ�������������";
	cin >> M.vexnum >> M.arcnum;
	cout << "�������������ֵ��";
	//��ʼ������������
	for (int i = 0;i < M.vexnum;i++) {
		char a;cin >> a;
		M.vertices[i] = {a,NULL};
	}
	//������������ڽӱ�
	VertexType v1, v2;
	int m, n, w;
	ArcNode* p;
	for (int i = 0;i < M.arcnum;i++) {
		cout << "������������Ķ��㼰Ȩֵ����β������ǰ����";
		cin >> v1 >> v2 >> w;
		m = LocateVexDN(M, v1);n = LocateVexDN(M, v2);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = n;
		p->inof = w;
		// ͷ�巨������β������뻡ͷ
		p->nextarc = M.vertices[m].firstarc;
		M.vertices[m].firstarc = p;
	}
	return OK;
}

Status DFSDN(ALGraph M, int v) {
	visited[v] = true;
	cout << M.vertices[v].vex;
	ArcNode* p;
	p = M.vertices[v].firstarc;
	while (p) {
		int m = p->adjvex;
		if (!visited[m]) {
			DFSDN(M, m);
		}
		p = p->nextarc;
	}
	return OK;
}

Status DFSTreaveDN(ALGraph M) {//�����������
	for (int i = 0;i < M.vexnum;i++) {
		visited[i] = false;
	}
	for (int v = 0;v < M.vexnum;v++) {
		if (!visited[v]) {
			DFSDN(M, v);
		}
	}
	return OK;
}

Status findInDegree(ALGraph G, int* a) {
	for (int i = 0;i < G.vexnum;i++) {
		a[i] = 0;
	}
	for (int i = 0;i < G.vexnum;i++) {
		ArcNode* p = G.vertices[i].firstarc;
		while (p) {
			a[p->adjvex] += 1;
			p = p->nextarc;
		}
	}
	return OK;
}

Status TopoLogicalSort(ALGraph& GT) {// ��������
	// ���������ȼ���ʼ��ջ
	int* InDegree,count=0;
	InDegree = (int*)malloc(GT.vexnum * sizeof(int));
	findInDegree(GT, InDegree);
	Stack S;
	InitStack(S,GT.vexnum);
	// �������Ϊ���ջ
	for (int i = 0;i < GT.vexnum;i++) {
		if (InDegree[i] == 0) {
			Push(S, i);
		}
	}
	// ����ÿ�����㣬��ջ��Ԫ�س�ջ�������������ڽӵ���ȼ�1���������Ϊ��ĵ����ջ
	while (!EmptyStack(S)) {
		int val = Pop(S);cout << GT.vertices[val].vex;count++;
		for (ArcNode* p = GT.vertices[val].firstarc;p;p = p->nextarc) {
			InDegree[p->adjvex] = InDegree[p->adjvex] - 1;
			if (InDegree[p->adjvex] == 0) {
				Push(S, p->adjvex);
			}
		}
	}
	if (count < GT.vexnum) return ERROR;
	else return OK;
}

int shortPath[MAX_VERTEX_NUM];// ������¼V0��V�ľ���
int pathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];// ������¼��Դ�㵽V��·��
Status Dijkstra(MGraph M,int start){
	// ��ʼ����¼����
	bool final[20];
	for (int v = 0;v < M.vexnum;v++) {
		final[v] = false; // ������¼�õ��Ƿ��Ѿ���ô�V0��V����̾���
		shortPath[v] = M.arcs[start][v].adj;// ��V0��V�ľ����ʼ��
		for (int w = 0;w < M.vexnum;w++) pathMatrix[v][w] = false;// ����V��·�����
		if (shortPath[v] < INFINITY) { pathMatrix[v][start] = true;pathMatrix[v][v] = true; }// ���V0��V��ͨ����V0��V����V0��V��·��
	}
	// ��start���붥�㼯
	shortPath[start] = 0;final[start] = true;
	// ��ʼ��ѭ����ÿ�����V[start]��V����þ��룬Ȼ��V���붥�㼯
	for (int i = 1;i < M.vexnum;i++) {
		// ����Сֵ
		int min = INFINITY;int v=NULL; // ����Ҫ��V=NULL����Ϊ�������û���ҵ�minֵ����ôV�Ͳ����ʼ�����Ӷ�����
		for (int i = 0;i < M.vexnum;i++) {
			if (shortPath[i] < min && !final[i]) {
				min = shortPath[i];v = i;
			}
		}
		if (v == NULL) break;  // *  �� v=NULL ������û����Сֵ�ˣ������㷨����
		final[v] = true;
		// ������Сֵ��·��
		for (int w = 0;w < M.vexnum;w++) {
			if (M.arcs[v][w].adj != INFINITY) {// *  ����������������Ϊ INFINITY ��ʾ�����ʾ���㲻�ɴ��û�б�Ҫ�Ӿ���
											   //����INFINITY�����为���Ӹ�����
				if (!final[w] && ((min + M.arcs[v][w].adj) < shortPath[w])) {
					shortPath[w] = min + M.arcs[v][w].adj;
					for (int i = 0;i < M.vexnum;i++) {
						pathMatrix[w][i] = pathMatrix[v][i];
					}
					pathMatrix[w][w] = true;
				}
			}
		}
	}
	return OK;
}

int main() {
	MGraph G;
	//CreatUDN(G);
	CreatDN(G);
	cout << "�ڽӾ���";
	PrintVex(G);
	cout << "������ȱ�����";
	DFSTraverse(G);
	cout << endl;
	Dijkstra(G, 0);
	for (int i = 0;i < G.vexnum;i++) {
		for (int j = 0;j < G.vexnum;j++) {
			if (pathMatrix[i][j])
				cout << j;
		}
		cout << "����" << shortPath[i]<<endl;
	}
	/*cout << "������ȱ�����";
	BFSTraverse(G, NumVex);
	cout << endl;
	CSTree T ;
	cout << "���������������";
	DFSForest(G, T);
	PrintTree(T);
	cout << endl;
	cout << "Prime�㷨�����С���������ߣ�";
	char a='a';
	MiniSpanTree_Prime(G, a);*/

	// �ڽӾر�����������
	/*ALGraph M;
	CreatDN(M);
	DFSTreaveDN(M);
	cout << endl << "��������";
	TopoLogicalSort(M);
	/*Stack S;
	InitStack(S, 6);
	for (int i = 0;i <= 5;i++) {
		Push(S, i);
	}
	while (!EmptyStack(S)) {
		int val = Pop(S);
		cout << val<<endl;
	}
	/*for (int i = 0;i <= 5;i++) {
		int val = Pop(S);
		cout << val<<endl;
	}*/
	/*int a = INFINITY;
	int b = -10;
	int c = a + b;
	cout << c;*/
	return OK;
}