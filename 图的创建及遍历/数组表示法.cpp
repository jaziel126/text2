#include<iostream>
#include<stdlib.h>
using namespace std;
#define OK 1
#define ERROR -1
#define INFINITY INT_MAX  //最大值
#define MAX_VERTEX_NUM 20  //最大顶点个数

typedef int Status;//返回类型
typedef int VRType;//顶点关系类型
typedef int InfoType;//弧信息指针
typedef char VertexType;//顶点值
typedef enum { DG, DN, UDG, UDN }GraphKind;//{有向图，有向网，无向图，无向网}

bool visited[MAX_VERTEX_NUM];//访问标志数组
int MAX_QUEUE_SIZE;//全局变量，用于存储辅助队列大小

typedef struct ArcCell {
	VRType adj;//表示是否相邻
	InfoType * info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum, arcsnum;//图当前顶点、弧数
	GraphKind kind;//图的种类
}MGraph;

typedef struct {
	int* data;
	int top;
	int base;
	int length;
}List;//这里不能用*GList这种指针，否则后面Q->data=(int *)malloc(n*sizeof(int));会报错！！！结构体不能双指针；

Status InitQueue(List &Q,MGraph G) {
	MAX_QUEUE_SIZE = 20;
	Q.data= (int*)malloc(MAX_QUEUE_SIZE * sizeof(int));
	Q.top = Q.base = 0;
	Q.length = G.vexnum;
	return OK;
}

Status EnQueue(List& Q,int v) {
	if ((Q.base + 1) % MAX_QUEUE_SIZE == Q.top) return ERROR;//队列满
	Q.data[Q.base] = v;
	Q.base = (Q.base + 1) % MAX_QUEUE_SIZE;
	return OK;
}

Status DeQueue(List& Q, int &v) {
	if (Q.base == Q.top) return ERROR;//队列为空
	v = Q.data[Q.top];
	Q.top = (Q.top + 1) % MAX_QUEUE_SIZE;//不难理解，队头元素出栈，则队头指针升高一位
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
	// int val = *stack.top; 这里弄反了，一定要先移动指针，再赋值
	stack.top = stack.top - 1;
	int val = *stack.top;
	return val;
}

Status EmptyStack(Stack stack) {
	if (stack.base == stack.top)
		return OK;
	else return 0;// 这里不能返回-1，因为-1算真，要返回0
}

Status LocateVex(MGraph G,VertexType v) {
	for (int i = 0;i < G.vexnum;++i) {
		if (G.vexs[i] == v) return i;
	}
	return ERROR;
}

Status CreatUDN(MGraph& G) {//构造无向网
	cout << "键入图的顶点、弧数：";
	cin >> G.vexnum >> G.arcsnum;
	cout << "键入各顶点向量：";
	for (int i = 0;i < G.vexnum;++i) {
		cin >> G.vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0;i < G.vexnum;++i) 
		for (int j = 0;j < G.vexnum;++j) 
			G.arcs[i][j] = { INFINITY,NULL };
	//构造邻接矩阵
	VertexType v1, v2;
	int m,n;
	VRType w;
	for (int i = 0;i < G.arcsnum;++i) {
		cout << "请依次键入各边依附的顶点及权值：";
		cin >> v1 >> v2 >> w;
		m = LocateVex(G, v1);n = LocateVex(G, v2);
		G.arcs[m][n].adj = w;
		G.arcs[n][m].adj = w;
	}
	return OK;
}

Status CreatDN(MGraph& GT) {//构造有向网
	cout << "键入图的顶点、弧数：";
	cin >> GT.vexnum >> GT.arcsnum;
	cout << "键入各顶点向量：";
	for (int i = 0;i < GT.vexnum;++i) {
		cin >> GT.vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0;i < GT.vexnum;++i)
		for (int j = 0;j < GT.vexnum;++j)
			GT.arcs[i][j] = { INFINITY,NULL };
	//构造邻接矩阵
	VertexType v1, v2;
	int m, n;
	VRType w;
	for (int i = 0;i < GT.arcsnum;++i) {
		cout << "请依次键入各边依附的顶点及权值：";
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
				cout << "∞";
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

Status FirstAdjVex(MGraph G, int v) {//找v的第一个邻接点
	for (int i = 0;i < G.vexnum;i++) {
		if (G.arcs[v][i].adj != INFINITY)
			return i;
	}
	return ERROR;
}

Status NextAdjVex(MGraph G, int v, int w) {//返回v(相对于w)的下一个邻接顶点
	for (int i = w+1;i < G.vexnum;++i) {
		if (G.arcs[v][i].adj != INFINITY)
			return i;
	}
	return ERROR;
}

Status DFS(MGraph G, int v,Status NumVex(MGraph G,int v)) {//深度优先搜索
	int w;
	visited[v] = true;
	NumVex(G,v);//对第v个顶点调用函数
	for (w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w)) 
		if(!visited[w])
			DFS(G, w, NumVex);
	return OK;
}
 
Status DFSTraverse(MGraph G) {
	//初始化标志数组
	for (int i = 0;i < G.vexnum;++i)
		visited[i] = false;
	//对每个顶点调用DFS，防止图为非连通图
	for (int v = 0;v < G.vexnum;++v)
		if (!visited[v])
			DFS(G, v,NumVex);
	return	OK;
}

Status BFSTraverse(MGraph G, Status NumVex(MGraph G, int v)) {//广度优先搜索
	List Q;
	InitQueue(Q, G);
	for (int i = 0;i < G.vexnum;i++) visited[i] = false;//访问标志数组初始化
	for (int v = 0;v < G.vexnum;v++) {
		//队头元素入栈
		if (!visited[v]) {
			visited[v] = true;
			NumVex(G, v);
			EnQueue(Q, v);
		//对队列每个元素遍历
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
	//将正在访问的该顶点的标志为设为true
	visited[v] = true;
	bool first = true;
	CSTree  q=NULL;
	//依次遍历该顶点的所有邻接顶点
	for (int w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w)) {
		//如果该标志为false，说明还没访问
		if (!visited[w]) {
			CSTree p = (CSTree)malloc(sizeof(CSNode));
			if (!p) return ERROR;
			*p = { G.vexs[w],NULL,NULL };
			//该结点的第一个邻接顶点作为孩子结点，其它邻接顶点设为兄弟结点
			if (first) {
				T->firstchild = p;
				first = false;
			}
			else {
				q->nextsibling = p;//T->nextsibling=p;
			}
			q = p;
			//以当前访问的顶点为树根，继续访问其它顶点
			DFSTree(G, q, w);
		}
		//DFSTree(G,q,w);
	}
	return OK;
}

Status DFSForest(MGraph G, CSTree& T) {//建立无向图G的深度优先生成树
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
			//每次都要把q指针指向新的结点，为下次添加结点做铺垫
			q = p;
			DFSTree(G, p, v);//建立以p为根的生成树
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
	VertexType adj;//改变在U中依附的顶点
	VRType lowcost;//最小代价边
};//辅助记录数组，用于记录从U到U-V各点的最小代价边

Status mininum(student *closedge,MGraph G) {//找记录数组中最小且大于零的边
	int min;
	int j = 0;
	while (closedge[j].lowcost == 0)
		j++;
	if (j == G.vexnum) return -1;
	min = closedge[j].lowcost;
	for (int i = 0;i < G.vexnum;i++) {
		if (closedge[i].lowcost < min && closedge[i].lowcost>0) {//一定要再三记住：||是或，&&是且！！！
			min = closedge[i].lowcost;
			j = i;
		}
	}
	return j;
}

Status MiniSpanTree_Prime(MGraph& G, VertexType u) {//记录从第u个顶点出发构造无向网G的最小生成树
	student closedge[MAX_VERTEX_NUM];//辅助记录数组，用于记录从U到U-V各点的最小代价边
	//初始化记录数组
	int k = LocateVex(G, u);
	for (int i = 0;i < G.vexnum;i++) {
		if (i != k) {
			closedge[i].lowcost = G.arcs[k][i].adj;
			closedge[i].adj = u;
		}
	}
	closedge[k] = { u, 0};
	for (int i = 1;i < G.vexnum;i++) {
		//寻找最小边并输出
		k = mininum(closedge, G);
		if (k == -1) break;
		cout << closedge[k].adj << G.vexs[k]<<"  ";//输出生成树的边
		//更新记录数组
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
	int adjvex;//该弧指向的顶点位置
	struct ArcNode* nextarc;//指向下一条弧指针，它们都指向相同的结点
	int inof;//该弧权值
}ArcNode;
typedef struct VNode{
	VertexType vex;//顶点向量
	struct ArcNode* firstarc;//指向第一条依附该结点的弧的指针，相当于头结点
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	int vexnum, arcnum;//图顶点数和弧数
	AdjList vertices;//顶点数组
}ALGraph;

Status LocateVexDN(ALGraph G, VertexType v) {
	for (int i = 0;i < G.vexnum;++i) {
		if (G.vertices[i].vex == v) return i;
	}
	return ERROR;
}

Status CreatDN(ALGraph& M) {
	cout << "输入图的顶点数、弧数：";
	cin >> M.vexnum >> M.arcnum;
	cout << "输入各顶点向量值：";
	//初始化各顶点数组
	for (int i = 0;i < M.vexnum;i++) {
		char a;cin >> a;
		M.vertices[i] = {a,NULL};
	}
	//输入各弧构造邻接表
	VertexType v1, v2;
	int m, n, w;
	ArcNode* p;
	for (int i = 0;i < M.arcnum;i++) {
		cout << "输入各弧依赖的顶点及权值（弧尾顶点在前）：";
		cin >> v1 >> v2 >> w;
		m = LocateVexDN(M, v1);n = LocateVexDN(M, v2);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = n;
		p->inof = w;
		// 头插法，将弧尾顶点插入弧头
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

Status DFSTreaveDN(ALGraph M) {//深度优先搜索
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

Status TopoLogicalSort(ALGraph& GT) {// 拓扑排序
	// 求各顶点入度及初始化栈
	int* InDegree,count=0;
	InDegree = (int*)malloc(GT.vexnum * sizeof(int));
	findInDegree(GT, InDegree);
	Stack S;
	InitStack(S,GT.vexnum);
	// 建立入度为零的栈
	for (int i = 0;i < GT.vexnum;i++) {
		if (InDegree[i] == 0) {
			Push(S, i);
		}
	}
	// 遍历每个顶点，将栈顶元素出栈，将它的所有邻接点入度减1，当有入度为零的点就入栈
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

int shortPath[MAX_VERTEX_NUM];// 用来记录V0到V的距离
int pathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];// 用来记录从源点到V的路径
Status Dijkstra(MGraph M,int start){
	// 初始化记录数组
	bool final[20];
	for (int v = 0;v < M.vexnum;v++) {
		final[v] = false; // 用来记录该点是否已经求得从V0到V的最短距离
		shortPath[v] = M.arcs[start][v].adj;// 将V0到V的距离初始化
		for (int w = 0;w < M.vexnum;w++) pathMatrix[v][w] = false;// 将点V的路径设空
		if (shortPath[v] < INFINITY) { pathMatrix[v][start] = true;pathMatrix[v][v] = true; }// 如果V0到V连通，将V0和V划入V0到V的路径
	}
	// 将start划入顶点集
	shortPath[start] = 0;final[start] = true;
	// 开始主循环，每次求得V[start]到V顶点得距离，然后将V划入顶点集
	for (int i = 1;i < M.vexnum;i++) {
		// 找最小值
		int min = INFINITY;int v=NULL; // 这里要将V=NULL是因为下面可能没有找到min值，那么V就不会初始化，从而报错！
		for (int i = 0;i < M.vexnum;i++) {
			if (shortPath[i] < min && !final[i]) {
				min = shortPath[i];v = i;
			}
		}
		if (v == NULL) break;  // *  当 v=NULL 即上面没有最小值了，所以算法结束
		final[v] = true;
		// 更新最小值及路径
		for (int w = 0;w < M.vexnum;w++) {
			if (M.arcs[v][w].adj != INFINITY) {// *  这里加这个条件是因为 INFINITY 表示无穷，表示两点不可达，则没有必要加距离
											   //而且INFINITY加正变负，加负变正
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
	cout << "邻接矩阵：";
	PrintVex(G);
	cout << "深度优先遍历：";
	DFSTraverse(G);
	cout << endl;
	Dijkstra(G, 0);
	for (int i = 0;i < G.vexnum;i++) {
		for (int j = 0;j < G.vexnum;j++) {
			if (pathMatrix[i][j])
				cout << j;
		}
		cout << "长度" << shortPath[i]<<endl;
	}
	/*cout << "广度优先遍历：";
	BFSTraverse(G, NumVex);
	cout << endl;
	CSTree T ;
	cout << "深度优先生成树：";
	DFSForest(G, T);
	PrintTree(T);
	cout << endl;
	cout << "Prime算法求得最小生成树各边：";
	char a='a';
	MiniSpanTree_Prime(G, a);*/

	// 邻接矩表，求拓扑排序
	/*ALGraph M;
	CreatDN(M);
	DFSTreaveDN(M);
	cout << endl << "拓扑排序：";
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