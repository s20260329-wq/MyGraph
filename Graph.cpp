//先想清楚创建一个图需要什么属性
//创建一个一维数组去存放节点
//创建一个二维数组去存放边
//还有图的状态即图有几个顶点有几条边
//创建两个结构体一个是存放图的信息,一个存储图里面节点的信息的二维数组
#include<stdlib.h>
#include<stdbool.h>
#include <stdio.h>
#define MAX_VERtEX_NUM 20                   //顶点的最大个数
#define VRType int                          //表示顶点之间关系的类型, 0 表示不相邻，1 表示相邻
#define VertexType int                      //图中顶点的数据类型
#define States int
bool visited[MAX_VERtEX_NUM];               //设置全局数组，标记图中的各个顶点是否被访问过
typedef  struct {
	VRType adj;
}ArcCell, AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];
//这个结构体存放图的宏观信息
typedef struct {
	VRType vex[MAX_VERtEX_NUM];
	int vexnum, arcnum;
	AdjMatrix arcs;
}MGraph;
//创建辅助函数帮助定位对应顶点所对应的顶点
int Location(MGraph*G,VRType data) {
	//遍历一维数组
	for (int i = 0; i < G->vexnum; i++) {
		if (data == G->vex[i]) {
			return i;
		}
	}
	return -1;
}
//找到第一个与顶点相连接的顶点
int FirstAdjVex(MGraph* G, int v){ //这个形参传的是顶点的元素下标
	for (int j = 0; j < G->vexnum; j++) {
		if (G->arcs[v][j].adj == 1) return j;
	}
	 return -1;
}
//找到下一个想=相连接的顶点
int NextAdjVex(MGraph* G, int v,int w) {//多一个参数W他的含义是确定起始位置因为不是从0开始
	for (int j = w + 1; j < G->vexnum;j++) {
		if (G->arcs[v][j].adj == 1) {
			return j;
		}
		return -1;
	}
}
//深度优先搜索
void DFS(MGraph* G,int v) {//形参传递的是下标索引
	//先判断被遍历过没有   其实在上层递归前已经确定过 
	printf("%d", G->vex[v]);
	visited[v]=1;
	//开始寻找下一个节点其实看似是两个函数的嵌套说白了结束双循环这个函数负责找列
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {//G>=0这个判断值是判断值返回值为-1的
		if (!visited[w]) {
			DFS(G, w);
		}
	}


}
void DFStraverse(MGraph* G) {
	//先将判断值表清空
	for (int i = 0; i < G->vexnum; i++) {
		visited[i] = 0;
	}
	//其实是外循环遍历矩阵y轴的顶点
	for (int i = 0; i < G->vexnum; i++) {
		if (visited[i] == 0) {
			DFS(G, i);
		}
	}
}
	//构造无向图
void DN(MGraph* G) {
	//先输入边的信息
	printf("请输入图的顶点数和边数");
	scanf_s("%d%d", &(G->vexnum), &(G->arcnum));
	printf("请输入顶点信息");
	for (int i = 0; i < G->vexnum;i++) {
		scanf_s("%d", &(G->vex[i]));
	}
	//将二维矩阵初始化为0
	for (int i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			G->arcs[i][j].adj = 0;
		}
	}
	printf("请输入那两个顶点有边");
	//记得写一个带边的for循环不是只输入一个
	for (int i = 0; i < G->arcnum; i++) {
		int v1, v2;
		scanf_s("%d%d", &v1, & v2);
		int V1 = Location(G, v1);
		int V2 = Location(G, v2);
		//在二维矩阵里面找到并赋值为一
		G->arcs[V1][V2].adj= 1;
		//无向图关于对角线对称
		G->arcs[V2][V1].adj = 1;
	}
}
