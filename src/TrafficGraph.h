// TrafficGraph.h
#pragma once
#include <string>
using namespace std;
#define INFINITY 888880	   // 无穷
typedef string VertexType; // 顶点的数据类型

///////////////////////////////////图结构定义///////////////////////////////////

// 带权图边权值的数据类型
struct EdgeType
{
	int distance = INFINITY; // 路线的距离
	double time = INFINITY;	 // 路线所需要的时间
	int cost = INFINITY;	 // 路线的花费
	int len = INFINITY;		 // 路径长
};

// 为了便捷使用，定义一个结构体来输入图
struct GraphInfo
{
	int Vex1;		 // 起点
	int Vex2;		 // 终点
	EdgeType Weight; // 权值
};

//  邻接矩阵储存交通图
class TrafficGraph
{
public:
	TrafficGraph(VertexType V[], GraphInfo GI[], int n, int e);
	~TrafficGraph();
	void EidtEdge(int start, int end, int flag, int weight); // 编辑现有边
	void AddEdge(int start, int end, EdgeType e);			 // 增加新边
	void PrintGraphMat(int flag);							 // 打印邻接矩阵
	void PrintDistMat(int flag);							 // 打印Dist矩阵
	void PrintPathMat(int flag);							 // 打印Path矩阵
	void PrintInfo(int start, int end, int flag);			 // 打印带权路径和
	void PrintCity(int v1, int v2);							 // 打印起点终点城市
	void Floyed();											 // Floyed算法计算多源最短路径
	void InitFind(int end);									 // 初始化查找路径
	void FindPath(int start, int end, int flag);			 // 打印输出最短路径
															 // void Min_Max(GraphInfo GI[]);

private:
	VertexType *Vex; // 顶点表
	EdgeType **Edge; // 邻接矩阵，边表
	EdgeType **Dist; // Floyed算法辅助数组，记录带权路径长度
	EdgeType **Path; // Floyed算法路径数组，记录算法产生的路径（中转点）
	int VexNum;		 // 当前顶点数
	int ArcNum;		 // 当前弧数
};

///////////////////////////////////显示菜单///////////////////////////////////
void ShowGraph();	// 显示交通图菜单
void LowcostMenu(); // 显示选择权重菜单
void MainMenu();	// 主菜单
void AdminMenu();	// 管理员菜单